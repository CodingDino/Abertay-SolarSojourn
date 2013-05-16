// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Explosion
//      Manages a set of particles, emitted and handled based on set parameters


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Explosion.h"


// |----------------------------------------------------------------------------|
// |							   Constructor									|
// |----------------------------------------------------------------------------|
Explosion::Explosion() :
    GameObject(),
    m_tintR(1.0f),
    m_tintG(1.0f),
    m_tintB(1.0f),
    m_alpha(1.0f),
    m_tintRVar(0.0f),
    m_tintGVar(0.0f),
    m_tintBVar(0.0f),
    m_alphaVar(0.0f),
    m_particleDeviation(0.0f,0.0f,0.0f),
    m_particleVelocity(0.0f,0.0f,0.0f),
    m_particleVelocityVariation(0.0f,0.0f,0.0f),
    m_particleSize(0),
    m_particleSpawnFrequency(0),
    m_particleFadeout(0),
    m_particleLifetime(0),
    m_maxParticles(0),
    m_accumulatedTime(0),
    m_particles(0),
	m_fireball(0),
	m_numFireballs(5)
{
	DebugLog ("ParticleSystem: object instantiated.");
}
     

// |----------------------------------------------------------------------------|
// |							  Copy Constructor								|
// |----------------------------------------------------------------------------|
Explosion::Explosion(const Explosion&) {
	DebugLog ("Explosion: object copied.");
}


// |----------------------------------------------------------------------------|
// |							   Destructor									|
// |----------------------------------------------------------------------------|
Explosion::~Explosion() {
	DebugLog ("Explosion: object destroyed.");
}


// |----------------------------------------------------------------------------|
// |							   Initialize									|
// |----------------------------------------------------------------------------|
bool Explosion::Initialize() {
    GameObject::Initialize();

	// Clear the initial accumulated time for the particle per second emission rate.
	m_accumulatedTime = 0.0f;

    // Clear any elements in the list
    m_particles.clear();

	// Set up fireball
	m_fireball = new Billboard;								// Fireball uses a billboard style graphic (facing camera)
	m_fireball->SetTexture("fireball");
	m_numFireballs = 6;
	m_fireball->SetScale(Coord(1.0f,1.0f,1.0f));			// Fireball is fairly large sized
	m_fireballVelocity = Coord(0.0f,0.0f,0.0f);				// Slow upward velocity
	m_fireballVelocityVariation = Coord(0.0f,0.0f,0.0f);	// Small random velocity variation
	//m_fireballVelocity = Coord(0.0f,1.0f,0.0f);				// Slow upward velocity
	//m_fireballVelocityVariation = Coord(0.5f,0.5f,0.5f);	// Small random velocity variation
	m_fireballFadeout = 5.0f;								// Starts to fade out after half a second
	m_fireballLifetime = 10.0f;								// Complete fade out after one second
	m_fireballRotationVariation = 2.0f*3.24f;				// Complete variation in rotation allowed
    m_fireballTintR = 1.0f; m_fireballTintG = 0.8f; m_fireballTintB = 0.6f; m_fireballAlpha = 1.0f;
															// White-Yellow tint
	m_fireballTintRVar = 0.1f; m_fireballTintGVar = 0.1f; m_fireballTintBVar = 0.1f; m_fireballAlphaVar = 0.0f;
															// Very small tint variation
	m_fireballDarken = 0.1f;

	DebugLog ("Explosion: object initialized.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							    Shutdown									|
// |----------------------------------------------------------------------------|
bool Explosion::Shutdown() {
    GameObject::Shutdown();

    // Clear any elements in the list
    m_particles.clear();
	m_accumulatedTime = 0.0f;

	DebugLog ("Explosion: object shutdown.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							     Logic()									|
// |----------------------------------------------------------------------------|
bool Explosion::Logic() {
	DebugLog ("Explosion: Logic() called.", DB_LOGIC, 10);
    
	// Emit new particles.
	//EmitParticles();
	
	// Update the position of the particles.
	UpdateParticles();

	// Release old particles.
	KillParticles();

	return true;
}


// |----------------------------------------------------------------------------|
// |							     Draw()										|
// |----------------------------------------------------------------------------|
bool Explosion::Draw() {
	DebugLog ("Explosion: Draw() called.", DB_GRAPHICS, 10);
    
    std::list<ParticleType>::iterator it;
    for (it=m_particles.begin(); it!=m_particles.end(); ++it)
    {
		if (it->type == EXPLOSION_FIREBALL)
		{
			m_fireball->SetTint(it->red,it->green,it->blue,it->alpha);
			m_fireball->Render(it->position);
		}
    }

	return true;
}


// |----------------------------------------------------------------------------|
// |						   EmitParticles()			    					|
// |----------------------------------------------------------------------------|
void Explosion::EmitParticles() {
	DebugLog ("Explosion: EmitParticles() called.", DB_LOGIC, 10);
    
	// Increment the frame time.
    float time = TimerManager::GetRef()->GetTime() / 1000;
	m_accumulatedTime += time;

	// Set emit particle to false for now.
	bool emitParticle = false;
    
	// Check if it is time to emit a new particle or not.
	if(m_accumulatedTime > (m_particleSpawnFrequency))
	{
		m_accumulatedTime = 0.0f;
		emitParticle = true;
	}
    else return;
    
	if((emitParticle == true) && (m_particles.size() < (m_maxParticles - 1)))
    {
	    DebugLog ("Explosion: Emitting Particle.", DB_LOGIC, 9);

		// Now generate the randomized particle properties.
        ParticleType newParticle;
		newParticle.position.x = m_position.x + (((float)rand()-(float)rand())/RAND_MAX) * m_particleDeviation.x;
		newParticle.position.y = m_position.y + (((float)rand()-(float)rand())/RAND_MAX) * m_particleDeviation.y;
		newParticle.position.z = m_position.z + (((float)rand()-(float)rand())/RAND_MAX) * m_particleDeviation.z;

		newParticle.velocity.x = m_particleVelocity.x + (((float)rand()-(float)rand())/RAND_MAX) * m_particleVelocityVariation.x;
        newParticle.velocity.y = m_particleVelocity.y + (((float)rand()-(float)rand())/RAND_MAX) * m_particleVelocityVariation.y;
		newParticle.velocity.z = m_particleVelocity.z + (((float)rand()-(float)rand())/RAND_MAX) * m_particleVelocityVariation.z;
        
		newParticle.red   = Clamp(m_tintR + (((float)rand()-(float)rand())/RAND_MAX) * m_tintRVar,0.0f,1.0f);
		newParticle.green = Clamp(m_tintG + (((float)rand()-(float)rand())/RAND_MAX) * m_tintGVar,0.0f,1.0f);
		newParticle.blue  = Clamp(m_tintB + (((float)rand()-(float)rand())/RAND_MAX) * m_tintBVar,0.0f,1.0f);
		newParticle.alpha = Clamp(m_alpha + (((float)rand()-(float)rand())/RAND_MAX) * m_alphaVar,0.0f,1.0f);

		newParticle.lifetime = 0.0f;
        newParticle.maxLife = m_particleLifetime;

        // Update to current camera
        newParticle.camera = GraphicsManager::GetRef()->GetCamera();

        // Add the new particle to the list
        m_particles.push_back(newParticle);
    }

	return;
}


// |----------------------------------------------------------------------------|
// |						   UpdateParticles()			    				|
// |----------------------------------------------------------------------------|
void Explosion::UpdateParticles() {
	DebugLog ("Explosion: UpdateParticles() called.", DB_LOGIC, 10);

    // Get frame time
    float time = TimerManager::GetRef()->GetTime() / 1000;
    
    std::list<ParticleType>::iterator it;
    for (it=m_particles.begin(); it!=m_particles.end(); ++it)
    {
        // Move and rotate particle based on velocity
        it->position += it->velocity * time;
		it->rotation += it->angularVelocity * time;

        // Update particle lifetime
        it->lifetime += time;

		if (it->type == EXPLOSION_FIREBALL)
		{
			// Update particle alpha
			if (it->lifetime > m_fireballFadeout)
				it->alpha = m_alpha * (m_fireballLifetime - it->lifetime) / (m_fireballLifetime - m_fireballFadeout);
		}

		// Darken particle over time
		it->red = Clamp(it->red - it->darken * time,0.0f,1.0f);

    }

    // Sort particles based on distance from camera
    m_particles.sort();

	return;
}


// |----------------------------------------------------------------------------|
// |						   KillParticles()			    					|
// |----------------------------------------------------------------------------|
void Explosion::KillParticles() {
	DebugLog ("Explosion: KillParticles() called.", DB_LOGIC, 10);
    
    // is_dead check for particles
    struct is_dead {
        bool operator() (const ParticleType& value) { return value.lifetime>value.maxLife; }
    };
    
    m_particles.remove_if (is_dead());

	return;
}


// |----------------------------------------------------------------------------|
// |					    ParticleType::operator<()							|
// |----------------------------------------------------------------------------|
bool Explosion::ParticleType::operator<(const ParticleType& rhs) {
	
    Coord cameraPosition = camera->GetPosition();
    Coord direction = cameraPosition - position;
    float distanceSqrThis = direction.x*direction.x 
        + direction.y*direction.y 
        + direction.z*direction.z;
    direction = cameraPosition - rhs.position;
    float distanceSqrRHS = direction.x*direction.x 
        + direction.y*direction.y 
        + direction.z*direction.z;

	return distanceSqrThis > distanceSqrRHS;
}


// |----------------------------------------------------------------------------|
// |						      Explode()			         					|
// |----------------------------------------------------------------------------|
void Explosion::Explode() {
	DebugLog ("Explosion: Explode() called.", DB_LOGIC, 2);
    
	// Emit fireball effect
	while (m_particles.size() < m_numFireballs )
    {
	    DebugLog ("Explosion: Emitting Fireball.", DB_LOGIC, 9);

		// Now generate the randomized particle properties.
        ParticleType newParticle;

		newParticle.type = EXPLOSION_FIREBALL;

		// Position
		newParticle.position.x = m_position.x + (((float)rand()-(float)rand())/RAND_MAX) * m_particleDeviation.x;
		newParticle.position.y = m_position.y + (((float)rand()-(float)rand())/RAND_MAX) * m_particleDeviation.y;
		newParticle.position.z = m_position.z + (((float)rand()-(float)rand())/RAND_MAX) * m_particleDeviation.z;

		// Velocity
		newParticle.velocity.x = m_fireballVelocity.x + (((float)rand()-(float)rand())/RAND_MAX) * m_fireballVelocityVariation.x;
        newParticle.velocity.y = m_fireballVelocity.y + (((float)rand()-(float)rand())/RAND_MAX) * m_fireballVelocityVariation.y;
		newParticle.velocity.z = m_fireballVelocity.z + (((float)rand()-(float)rand())/RAND_MAX) * m_fireballVelocityVariation.z;

		// Rotation
		newParticle.rotation = 0.0f + (((float)rand()-(float)rand())/RAND_MAX) * m_fireballRotationVariation;
		newParticle.rotation = 0.0f + (((float)rand()-(float)rand())/RAND_MAX) * m_fireballRotationVariation;
        
		newParticle.red   = Clamp(m_fireballTintR + (((float)rand()-(float)rand())/RAND_MAX) * m_fireballTintRVar,0.0f,1.0f);
		newParticle.green = Clamp(m_fireballTintG + (((float)rand()-(float)rand())/RAND_MAX) * m_fireballTintGVar,0.0f,1.0f);
		newParticle.blue  = Clamp(m_fireballTintB + (((float)rand()-(float)rand())/RAND_MAX) * m_fireballTintBVar,0.0f,1.0f);
		newParticle.alpha = Clamp(m_fireballAlpha + (((float)rand()-(float)rand())/RAND_MAX) * m_fireballAlphaVar,0.0f,1.0f);
		newParticle.darken = m_fireballDarken;

		newParticle.lifetime = 0.0f;
        newParticle.maxLife = m_fireballLifetime;


        // Update to current camera
        newParticle.camera = GraphicsManager::GetRef()->GetCamera();

        // Add the new particle to the list
        m_particles.push_back(newParticle);
    }


	return;
}