// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// TitleScreen
//      Splash screen shown at the start of the game


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "TitleScreen.h"


// |----------------------------------------------------------------------------|
// |							   Constructor									|
// |----------------------------------------------------------------------------|
TitleScreen::TitleScreen() :
    Screen(),
    m_particles(0)
{
	DebugLog ("TitleScreen: object instantiated.");
}
     

// |----------------------------------------------------------------------------|
// |							  Copy Constructor								|
// |----------------------------------------------------------------------------|
TitleScreen::TitleScreen(const TitleScreen&) {
	DebugLog ("TitleScreen: object copied.");
}


// |----------------------------------------------------------------------------|
// |							   Destructor									|
// |----------------------------------------------------------------------------|
TitleScreen::~TitleScreen() {
	DebugLog ("TitleScreen: object destroyed.");
}


// |----------------------------------------------------------------------------|
// |							   Initialize									|
// |----------------------------------------------------------------------------|
bool TitleScreen::Initialize() {

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
    LightManager::GetRef()->SetAmbient(0.05f,0.05f,0.05f);
    
    // Set up camera
    m_camera = new MouseLookCamera;
    m_camera->SetPosition(Coord(0.0f, 0.0f, -10.0f));
	((MouseLookCamera*)m_camera)->SetSpeed(0.0f);

    // Set up skybox
    m_skybox->SetTexture("skybox_starfield");

    // Set up sun
	graphic = new Graphic;
    graphic->SetTint(1.0f,1.0f,0.8f,1.0f);
    graphic->SetShader("Texture");
    graphic->SetModel("sphere");
    graphic->Initialize();
    planet = new Planet;
    planet->Initialize();
	planet->SetGraphic(graphic);
    planet->SetOrbitCenter(Coord(-5.0f,-2.0f,2.0f));
    m_gameObjects.push_back(planet);
	GameObject* sun = planet;

    // Sun Light
    pLight.SetPosition(planet->GetOrbitCenter());
    pLight.SetColor(graphic->GetTintR(),graphic->GetTintG(),graphic->GetTintB(),1.0f);
    pLight.SetBrightness(10.0f);
    LightManager::GetRef()->AddLight(pLight);

    // Set up planet
    graphic = new Graphic;
    graphic->SetShader("Light");
	graphic->SetTexture("planet_02_venus");
    graphic->SetReflectiveness(0.98f);
    graphic->SetScale(Coord(0.2f,0.2f,0.2f));
    graphic->Initialize();
    planet = new Planet;
    planet->Initialize();
    planet->SetGraphic(graphic);
    planet->SetOrbitRadius(1.5);
    planet->SetOrbitSpeed(1.0f);
	planet->SetOrbitCenter(sun);
    m_gameObjects.push_back(planet);
    
    // Set up particle system
    particleSystem = new ParticleSystem;
    particleSystem->Initialize();
    graphic = new Billboard;
    graphic->SetShader("Texture");
    graphic->SetTexture("particle_point");
    graphic->SetTint(01.0f,0.4f,0.0f,1.0f);
    graphic->SetAlphaBlend(true);
    graphic->SetScale(Coord(0.005f,0.005f,0.005f));
    graphic->Initialize();
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
    m_particles = particleSystem;
    m_gameObjects.push_back(particleSystem);

	// Temporarily Disable Post-Processing
	DisablePostProcessing();
	//EnablePostProcessing();

	DebugLog ("TitleScreen: object initialized.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							    Shutdown									|
// |----------------------------------------------------------------------------|
bool TitleScreen::Shutdown() {

	DebugLog ("TitleScreen: object shutdown.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							     Logic()									|
// |----------------------------------------------------------------------------|
// The logic function, which will be called by the main game loop.
bool TitleScreen::Logic() {
	DebugLog ("TitleScreen: Logic() called.", DB_LOGIC, 10);

    Screen::Logic();

    // Update particle location
    if (m_particles && m_camera) m_particles->SetPosition(m_camera->GetPosition());

	return true;
}

// |----------------------------------------------------------------------------|
// |							     Draw()										|
// |----------------------------------------------------------------------------|
// The draw function, which will be called by the main game loop.
bool TitleScreen::Draw() {
	DebugLog ("TitleScreen: Draw() called.", DB_GRAPHICS, 10);

    Screen::Draw();

	return true;
}

// |----------------------------------------------------------------------------|
// |							    OnLoad()									|
// |----------------------------------------------------------------------------|
// Called when the screen is loaded.
bool TitleScreen::OnLoad() {
	DebugLog("TitleScreen: OnLoad called");

	m_done = false;

	return true;
}

// |----------------------------------------------------------------------------|
// |							    OnExit()									|
// |----------------------------------------------------------------------------|
// Called when switching to a different screen
bool TitleScreen::OnExit() {

	DebugLog ("TitleScreen: OnExit called.");

	return true;
}