// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// LevelScreen
//      Main game screen. properties can be customized to change level appearance.


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "LevelScreen.h"


// |----------------------------------------------------------------------------|
// |							   Constructor									|
// |----------------------------------------------------------------------------|
LevelScreen::LevelScreen() :
    Screen(),
    m_particles(0)
{
	DebugLog ("LevelScreen: object instantiated.");
}
     

// |----------------------------------------------------------------------------|
// |							  Copy Constructor								|
// |----------------------------------------------------------------------------|
LevelScreen::LevelScreen(const LevelScreen&) {
	DebugLog ("LevelScreen: object copied.");
}


// |----------------------------------------------------------------------------|
// |							   Destructor									|
// |----------------------------------------------------------------------------|
LevelScreen::~LevelScreen() {
	DebugLog ("LevelScreen: object destroyed.");
}


// |----------------------------------------------------------------------------|
// |							   Initialize									|
// |----------------------------------------------------------------------------|
bool LevelScreen::Initialize() {

    // Initialize parent class
    Screen::Initialize();

    // Define Variables
    Planet* planet;
    GameObject* gameObject;
    PointLight pLight;
    Graphic* graphic;
    ParticleSystem* particleSystem;
    Text* text;

    // Set next screen to SCREEN_QUIT
	SetNextScreen(SCREEN_QUIT);

    // Set Post-Processing Effects
    m_glow = true;

    // Set lighting
    LightManager::GetRef()->SetAmbient(0.15f,0.15f,0.15f);

    // Set fog
    LightManager::GetRef()->SetFogColor(0.8f,0.6f,0.6f);
    LightManager::GetRef()->SetFogDensity(0.07f);
    
    // Set up camera
    m_camera = new MouseLookCamera;
    m_camera->SetPosition(Coord(0.0f, 0.0f, -10.0f));

    // Set up skybox
    m_skybox->SetTexture("default");
    m_skybox->SetTint(0.8f,0.6f,0.6f);

    // Set up sun
	m_sun = new SkyBox;
    m_sun->SetTint(1.0f,1.0f,0.8f,1.0f);
    m_sun->SetRenderTarget(m_renderTexture);
    m_sun->SetShader("Texture");
    m_sun->SetModel("sphere");
    m_sun->Initialize();
    m_sun->SetPosition(Coord(10.0f,5.0f,10.0f));

    // Sun Light
    float intensity = 0.07;
    LightManager::GetRef()->SetDiffuseColor(m_sun->GetTintR(),m_sun->GetTintG(),m_sun->GetTintB());
    LightManager::GetRef()->SetDiffuseDirection(-1*intensity*m_sun->GetPosition().x,-1*intensity*m_sun->GetPosition().y,-1*intensity*m_sun->GetPosition().z);

    // Set up floor
    gameObject = new GameObject;
    gameObject->Initialize();
    graphic = new Graphic;
    graphic->SetTint(0.8f,0.6f,0.4f,1.0f);
    graphic->SetShader("Light");
    Mesh* mesh = new Mesh;
    mesh->Initialize(100,100,10.0f);
    graphic->SetModel(mesh);
    graphic->Initialize();
    gameObject->SetGraphic(graphic);
    gameObject->SetPosition(Coord(0.0f,-5.0f,0.0f));
    m_gameObjects.push_back(gameObject);
    
    // Set up particle system
    particleSystem = new ParticleSystem;
    particleSystem->Initialize();
    graphic = new Billboard;
    graphic->SetTint(01.0f,0.4f,0.0f,1.0f);
    graphic->SetShader("Texture");
    graphic->SetAlphaBlend(true);
    graphic->SetTexture("particle_point");
    graphic->Initialize();
    graphic->SetRenderTarget(m_renderTexture);
    graphic->SetScale(Coord(0.005f,0.005f,0.005f));
    particleSystem->SetGraphic(graphic);
    particleSystem->SetParticleVelocity(Coord(0.0f,0.0f,0.0f));
    particleSystem->SetParticleVelocityVariation(Coord(1.0f,1.0f,1.0f));
    particleSystem->SetParticleSpawnFrequency(0.1f);
    particleSystem->SetParticleDeviation(Coord(10.0f,10.0f,10.0f));
    particleSystem->SetParticleLifetime(10.0f);
    particleSystem->SetParticleFadeout(5.0f);
    particleSystem->SetMaxParticles(100);
    particleSystem->SetTint(1.0f,1.0f,1.0f);
    particleSystem->SetTintVar(0.5f,0.5f,0.5f);
    //m_particles = particleSystem;
    //m_gameObjects.push_back(particleSystem);

	// Temporarily Disable Post-Processing
	DisablePostProcessing();

	DebugLog ("LevelScreen: object initialized.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							    Shutdown									|
// |----------------------------------------------------------------------------|
bool LevelScreen::Shutdown() {

	DebugLog ("LevelScreen: object shutdown.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							     Logic()									|
// |----------------------------------------------------------------------------|
// The logic function, which will be called by the main game loop.
bool LevelScreen::Logic() {
	DebugLog ("LevelScreen: Logic() called.", DB_LOGIC, 10);

    Screen::Logic();

    // Update coord location
    if (m_particles)
		m_particles->SetPosition(m_camera->GetPosition());

	return true;
}

// |----------------------------------------------------------------------------|
// |							     Draw()										|
// |----------------------------------------------------------------------------|
// The draw function, which will be called by the main game loop.
bool LevelScreen::Draw() {
	DebugLog ("LevelScreen: Draw() called.", DB_GRAPHICS, 10);

    Screen::Draw();

	return true;
}

// |----------------------------------------------------------------------------|
// |							    OnLoad()									|
// |----------------------------------------------------------------------------|
// Called when the screen is loaded.
bool LevelScreen::OnLoad() {
	DebugLog("LevelScreen: OnLoad called");

	m_done = false;

	return true;
}

// |----------------------------------------------------------------------------|
// |							    OnExit()									|
// |----------------------------------------------------------------------------|
// Called when switching to a different screen
bool LevelScreen::OnExit() {

	DebugLog ("LevelScreen: OnExit called.");

	return true;
}