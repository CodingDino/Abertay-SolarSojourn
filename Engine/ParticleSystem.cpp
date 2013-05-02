// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// ParticleSystem
//      Manages a set of particles, emitted and handled based on set parameters


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "ParticleSystem.h"


// |----------------------------------------------------------------------------|
// |							   Constructor									|
// |----------------------------------------------------------------------------|
ParticleSystem::ParticleSystem() :
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
    GameObject()
{
	DebugLog ("ParticleSystem: object instantiated.");
}
     

// |----------------------------------------------------------------------------|
// |							  Copy Constructor								|
// |----------------------------------------------------------------------------|
ParticleSystem::ParticleSystem(const ParticleSystem&) {
	DebugLog ("ParticleSystem: object copied.");
}


// |----------------------------------------------------------------------------|
// |							   Destructor									|
// |----------------------------------------------------------------------------|
ParticleSystem::~ParticleSystem() {
	DebugLog ("ParticleSystem: object destroyed.");
}


// |----------------------------------------------------------------------------|
// |							   Initialize									|
// |----------------------------------------------------------------------------|
bool ParticleSystem::Initialize() {
    GameObject::Initialize();

	// Clear the initial accumulated time for the particle per second emission rate.
	m_accumulatedTime = 0.0f;

    // Clear any elements in the list
    m_particles.clear();

	DebugLog ("ParticleSystem: object initialized.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							    Shutdown									|
// |----------------------------------------------------------------------------|
bool ParticleSystem::Shutdown() {
    GameObject::Shutdown();

    // Clear any elements in the list
    m_particles.clear();
	m_accumulatedTime = 0.0f;

	DebugLog ("ParticleSystem: object shutdown.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							     Logic()									|
// |----------------------------------------------------------------------------|
bool ParticleSystem::Logic() {
	DebugLog ("ParticleSystem: Logic() called.", DB_LOGIC, 10);
    
	// Emit new particles.
	EmitParticles();
	
	// Update the position of the particles.
	UpdateParticles();

	// Release old particles.
	KillParticles();

	return true;
}


// |----------------------------------------------------------------------------|
// |							     Draw()										|
// |----------------------------------------------------------------------------|
bool ParticleSystem::Draw() {
	DebugLog ("ParticleSystem: Draw() called.", DB_GRAPHICS, 10);
    
    std::list<ParticleType>::iterator it;
    for (it=m_particles.begin(); it!=m_particles.end(); ++it)
    {
        m_graphic->GetMaterial()->SetTint(it->red,it->green,it->blue,it->alpha);
        m_graphic->Render(it->position);
    }

	return true;
}


// |----------------------------------------------------------------------------|
// |						   EmitParticles()			    					|
// |----------------------------------------------------------------------------|
void ParticleSystem::EmitParticles() {
	DebugLog ("ParticleSystem: EmitParticles() called.", DB_LOGIC, 10);
    
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
	    DebugLog ("ParticleSystem: Emitting Particle.", DB_LOGIC, 9);

		// Now generate the randomized particle properties.
        ParticleType newParticle;
		newParticle.position.x = m_position.x + (((float)rand()-(float)rand())/RAND_MAX) * m_particleDeviation.x;
		newParticle.position.y = m_position.y + (((float)rand()-(float)rand())/RAND_MAX) * m_particleDeviation.y;
		newParticle.position.z = m_position.z + (((float)rand()-(float)rand())/RAND_MAX) * m_particleDeviation.z;

		newParticle.velocity.x = m_particleVelocity.x + (((float)rand()-(float)rand())/RAND_MAX) * m_particleVelocityVariation.x;
        newParticle.velocity.y = m_particleVelocity.y + (((float)rand()-(float)rand())/RAND_MAX) * m_particleVelocityVariation.y;
		newParticle.velocity.z = m_particleVelocity.z + (((float)rand()-(float)rand())/RAND_MAX) * m_particleVelocityVariation.z;
        
		//newParticle.red   = (((float)rand()-(float)rand())/RAND_MAX);
		//newParticle.green = (((float)rand()-(float)rand())/RAND_MAX);
		//newParticle.blue  = (((float)rand()-(float)rand())/RAND_MAX);
		newParticle.red   = 1.0f;
		newParticle.green = 1.0f;
		newParticle.blue  = 1.0f;
		newParticle.alpha = 0.1f;

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
void ParticleSystem::UpdateParticles() {
	DebugLog ("ParticleSystem: UpdateParticles() called.", DB_LOGIC, 10);

    // Get frame time
    float time = TimerManager::GetRef()->GetTime() / 1000;
    
    std::list<ParticleType>::iterator it;
    for (it=m_particles.begin(); it!=m_particles.end(); ++it)
    {
        // Move particle based on velocity
        it->position += it->velocity * time;

        // Update particle lifetime
        it->lifetime += time;

        // Update particle alpha
        if (it->lifetime > m_particleFadeout)
            it->alpha = (m_particleLifetime - it->lifetime) / (m_particleLifetime - m_particleFadeout);
    }

    // Sort particles based on distance from camera
    m_particles.sort();

	return;
}


// |----------------------------------------------------------------------------|
// |						   KillParticles()			    					|
// |----------------------------------------------------------------------------|
void ParticleSystem::KillParticles() {
	DebugLog ("ParticleSystem: KillParticles() called.", DB_LOGIC, 10);
    
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
bool ParticleSystem::ParticleType::operator<(const ParticleType& rhs) {
	
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

