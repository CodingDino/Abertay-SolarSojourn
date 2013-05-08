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

    // Set next screen to SCREEN_LEVEL
	SetNextScreen(SCREEN_LEVEL);

    // Set Post-Processing Effects
    m_glow = true;

    // Set lighting
    LightManager::GetRef()->SetAmbient(0.05f,0.05f,0.05f);
    
    // Set up camera
    m_camera = new MouseLookCamera;
    m_camera->SetPosition(Coord(0.0f, 0.0f, -10.0f));
	((MouseLookCamera*)m_camera)->SetSpeed(0.0f);
	((MouseLookCamera*)m_camera)->SetSensitivity(0.0f);

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
    planet->SetOrbitCenter(Coord(-5.5f,-2.5f,0.0f));
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

	

    // Title display
    text = new Text;
    text->SetFont("space_age_regular_128");
    text->Initialize();
    text->SetRenderToBackBuffer(true);
	text->SetText("SOLAR");
    gameObject = new GameObject;
    gameObject->Initialize();
    gameObject->SetGraphic(text);
	gameObject->SetPosition(Coord(100.0f,120.0f,0.0f));
    m_overlayObjects.push_back(gameObject);
	//
    text = new Text;
    text->SetFont("space_age_regular_128");
    text->Initialize();
    text->SetRenderToBackBuffer(true);
	text->SetText("SOJOURN");
    gameObject = new GameObject;
    gameObject->Initialize();
    gameObject->SetGraphic(text);
	gameObject->SetPosition(Coord(100.0f,240.0f,0.0f));
    m_overlayObjects.push_back(gameObject);
	//
    text = new Text;
    text->SetFont("radio_space_regular_20");
    text->Initialize();
    text->SetRenderToBackBuffer(true);
	text->SetText("created by Sarah Herzog");
    gameObject = new GameObject;
    gameObject->Initialize();
    gameObject->SetGraphic(text);
	gameObject->SetPosition(Coord(100.0f,400.0f,0.0f));
    m_overlayObjects.push_back(gameObject);

	// Instructions display
    text = new Text;
    text->SetFont("radio_space_regular_20");
    text->Initialize();
    text->SetRenderToBackBuffer(true);
	text->SetText("Use the mouse to look around");
    gameObject = new GameObject;
    gameObject->Initialize();
    gameObject->SetGraphic(text);
	gameObject->SetPosition(Coord(300.0f,500.0f,0.0f));
    m_overlayObjects.push_back(gameObject);
	//
    text = new Text;
    text->SetFont("radio_space_regular_20");
    text->Initialize();
    text->SetRenderToBackBuffer(true);
	text->SetText("Use WASD to move and space/alt to change altitude");
    gameObject = new GameObject;
    gameObject->Initialize();
    gameObject->SetGraphic(text);
	gameObject->SetPosition(Coord(300.0f,530.0f,0.0f));
    m_overlayObjects.push_back(gameObject);
	//
    text = new Text;
    text->SetFont("radio_space_regular_20");
    text->Initialize();
    text->SetRenderToBackBuffer(true);
	text->SetText("Left mouse button to shoot");
    gameObject = new GameObject;
    gameObject->Initialize();
    gameObject->SetGraphic(text);
	gameObject->SetPosition(Coord(300.0f,560.0f,0.0f));
    m_overlayObjects.push_back(gameObject);
	//
    text = new Text;
    text->SetFont("radio_space_regular_20");
    text->Initialize();
    text->SetRenderToBackBuffer(true);
	text->SetText("Shoot all the objectives before time runs out");
    gameObject = new GameObject;
    gameObject->Initialize();
    gameObject->SetGraphic(text);
	gameObject->SetPosition(Coord(300.0f,590.0f,0.0f));
    m_overlayObjects.push_back(gameObject);
	//
    text = new Text;
    text->SetFont("radio_space_regular_20");
    text->Initialize();
    text->SetRenderToBackBuffer(true);
	text->SetText("Click to start");
    gameObject = new GameObject;
    gameObject->Initialize();
    gameObject->SetGraphic(text);
	gameObject->SetPosition(Coord(600.0f,800.0f,0.0f));
    m_overlayObjects.push_back(gameObject);

	// Temporarily Disable Post-Processing
	DisablePostProcessing();

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

	// Check for mouse click, move to next screen
	if(InputManager::GetRef()->IsMouseButtonDown(1))
	{
		m_done = true;
	}
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