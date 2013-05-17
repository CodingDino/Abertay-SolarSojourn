// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Player
//      Managers graphics and functionality for the player ship


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Player.h"


// |----------------------------------------------------------------------------|
// |							   Constructor									|
// |----------------------------------------------------------------------------|
Player::Player() :
    GameObject(),
	m_ship(0),
	m_leftThruster(0),
	m_rightThruster(0),
	m_direction(0.0f,0.0f,1.0f),
	m_speed(25.0f),
	m_crashed(false)
{
	DebugLog ("Player: object instantiated.");
}
     

// |----------------------------------------------------------------------------|
// |							  Copy Constructor								|
// |----------------------------------------------------------------------------|
Player::Player(const Player&) {
	DebugLog ("Player: object copied.");
}


// |----------------------------------------------------------------------------|
// |							   Destructor									|
// |----------------------------------------------------------------------------|
Player::~Player() {
	DebugLog ("Player: object destroyed.");
}


// |----------------------------------------------------------------------------|
// |							   Initialize									|
// |----------------------------------------------------------------------------|
bool Player::Initialize() {
    GameObject::Initialize();

	// Set up ship
	Graphic* graphic = new Graphic;
    graphic->SetTint(1.0f,1.0f,1.0f,1.0f);
    graphic->SetShader("Texture");
    graphic->SetShader("Light");
	graphic->SetTexture("shiptexture");
    graphic->SetModel("ship");
    graphic->SetScale(Coord(0.01f,0.01f,0.01f));
	graphic->SetReflectiveness(0.95f);
    graphic->Initialize();
    m_ship = new GameObject;
    m_ship->Initialize();
	m_ship->SetGraphic(graphic);
    m_ship->SetPosition(Coord(0.0f,0.0f,0.0f));
    m_ship->SetOrientation(Coord(0.0f,0.0f,0.0f));

    // Set up left thruster
    m_leftThruster = new ParticleSystem;
    m_leftThruster->Initialize();
    graphic = new Billboard;
    graphic->SetShader("Texture");
    graphic->SetTexture("fireball");
    graphic->SetAlphaBlend(true);
    graphic->SetScale(Coord(0.003f,0.003f,0.003f));
    graphic->Initialize();
    m_leftThruster->SetGraphic(graphic);
    m_leftThruster->SetPosition(Coord(-0.6f,0.0f,-0.7f));
    m_leftThruster->SetParticleVelocity(Coord(0.0f,0.0f,-2.0f));
    m_leftThruster->SetParticleVelocityVariation(Coord(0.5f,0.5f,0.5f));
    m_leftThruster->SetParticleSpawnFrequency(0.01f);
    m_leftThruster->SetParticleDeviation(Coord(0.0f,0.0f,0.0f));
    m_leftThruster->SetParticleLifetime(0.5f);
    m_leftThruster->SetParticleFadeout(0.2f);
    m_leftThruster->SetMaxParticles(100);
    m_leftThruster->SetTint(0.8f,0.9f,1.0f);
    m_leftThruster->SetTintVar(0.2f,0.2f,0.2f);

    // Set up right thruster
    m_rightThruster = new ParticleSystem;
    m_rightThruster->Initialize();
    graphic = new Billboard;
    graphic->SetShader("Texture");
    graphic->SetTexture("fireball");
    graphic->SetAlphaBlend(true);
    graphic->SetScale(Coord(0.003f,0.003f,0.003f));
    graphic->Initialize();
    m_rightThruster->SetGraphic(graphic);
    m_rightThruster->SetPosition(Coord(0.6f,0.0f,-0.7f));
    m_rightThruster->SetParticleVelocity(Coord(0.0f,0.0f,-2.0f));
    m_rightThruster->SetParticleVelocityVariation(Coord(0.5f,0.5f,0.5f));
    m_rightThruster->SetParticleSpawnFrequency(0.001f);
    m_rightThruster->SetParticleDeviation(Coord(0.0f,0.0f,0.0f));
    m_rightThruster->SetParticleLifetime(0.5f);
    m_rightThruster->SetParticleFadeout(0.2f);
    m_rightThruster->SetMaxParticles(100);
    m_rightThruster->SetTint(0.8f,0.9f,1.0f);
    m_rightThruster->SetTintVar(0.2f,0.2f,0.2f);



	DebugLog ("Player: object initialized.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							    Shutdown									|
// |----------------------------------------------------------------------------|
bool Player::Shutdown() {
    GameObject::Shutdown();
	DebugLog ("Player: object shutdown.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							     Logic()									|
// |----------------------------------------------------------------------------|
bool Player::Logic() {
	DebugLog ("Player: Logic() called.", DB_LOGIC, 10);

	// If crashed, don't process
	if (m_crashed) return true;

    // Get time for this frame
    float time = TimerManager::GetRef()->GetTime() / 1000;

	// TODO: Get player input (Update direction, speed), set camera based on this
	// For now, keep using mouselookcamera and get it from the camera
    Camera* camera = GraphicsManager::GetRef()->GetCamera();
	Coord cameraOrientation = camera->GetOrientation();

	SetOrientation(Coord(
		0.0f+cameraOrientation.y*3.14/180,
		-1*(3.14f/6.0f)+cameraOrientation.x*3.14/180,
		0.0f+cameraOrientation.z*3.14/180));

	// Ship just stays with the camera
	Coord localPos(
		10.0f*sin(3.14/2-cameraOrientation.x*3.14/180-1*(3.14f/16.0f))*sin(cameraOrientation.y*3.14/180),
		-10.0f*cos(3.14/2-cameraOrientation.x*3.14/180-1*(3.14f/16.0f)),
		10.0f*sin(3.14/2-cameraOrientation.x*3.14/180-1*(3.14f/16.0f))*cos(cameraOrientation.y*3.14/180) );
	Coord unbounded = localPos + camera->GetPosition();
	m_linearVelocity = unbounded - m_position;
	SetPosition(unbounded);
	localPos = Coord(
		9.3f*sin(3.14/2-cameraOrientation.x*3.14/180-1.25*(3.14f/16.0f))*sin(cameraOrientation.y*3.14/180-0.6*(3.14f/32.0f)),
		-9.3f*cos(3.14/2-cameraOrientation.x*3.14/180-1.25*(3.14f/16.0f)),
		9.3f*sin(3.14/2-cameraOrientation.x*3.14/180-1.25*(3.14f/16.0f))*cos(cameraOrientation.y*3.14/180-0.6*(3.14f/32.0f)) );
    m_leftThruster->SetPosition(localPos+camera->GetPosition());
	localPos = Coord(
		9.3f*sin(3.14/2-cameraOrientation.x*3.14/180-1.25*(3.14f/16.0f))*sin(cameraOrientation.y*3.14/180+0.6*(3.14f/32.0f)),
		-9.3f*cos(3.14/2-cameraOrientation.x*3.14/180-1.25*(3.14f/16.0f)),
		9.3f*sin(3.14/2-cameraOrientation.x*3.14/180-1.25*(3.14f/16.0f))*cos(cameraOrientation.y*3.14/180+0.6*(3.14f/32.0f)) );
    m_rightThruster->SetPosition(localPos+camera->GetPosition());
	
	// Alternate controlling method:
	//Coord unbounded(camera->GetPosition()+Coord(0.0f,-2.0f,10.0f));
	// If the position gets too far from the camera direction vector, move it to that point.
	// Need bounding points to left, right, up, and down.
	// Need to keep ship a certain distance from camera...

	// TODO: Update velocity of thrusters to shoot backwards
	Coord thrusterVel = Coord(
		sin(3.14/2-camera->GetOrientation().x*3.14/180+1.25*(3.14f/16.0f))*sin(camera->GetOrientation().y*3.14/180),
		-1*cos(3.14/2-camera->GetOrientation().x*3.14/180+1.25*(3.14f/16.0f)),
		sin(3.14/2-camera->GetOrientation().x*3.14/180+1.25*(3.14f/16.0f))*cos(camera->GetOrientation().y*3.14/180) );
	thrusterVel *= -2.0f;
    m_leftThruster->SetParticleVelocity(thrusterVel);
    m_rightThruster->SetParticleVelocity(thrusterVel);

	// Call logic functions for child objects
	m_ship->Logic();
	m_leftThruster->Logic();
	m_rightThruster->Logic();

	return true;
}


// |----------------------------------------------------------------------------|
// |							      Draw()									|
// |----------------------------------------------------------------------------|
bool Player::Draw() {
	DebugLog ("Player: Draw() called.", DB_LOGIC, 10);
	
	// If crashed, don't process
	if (m_crashed) return true;

	// Call draw functions for child objects
	m_ship->Draw();
	m_leftThruster->Draw();
	m_rightThruster->Draw();

	return true;
}


// |----------------------------------------------------------------------------|
// |							   SetPosition()								|
// |----------------------------------------------------------------------------|
void Player::SetPosition(Coord position) 
{
	m_position = position;

    m_ship->SetPosition(position);
}


// |----------------------------------------------------------------------------|
// |							  SetOrientation()								|
// |----------------------------------------------------------------------------|
void Player::SetOrientation(Coord orientation) 
{
	m_orientation = orientation;

    m_ship->SetOrientation(orientation);
}

