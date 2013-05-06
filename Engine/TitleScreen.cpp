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
    m_position(0),
    m_rotation(0)
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
    m_blur = true;

    // Set lighting
    LightManager::GetRef()->SetAmbient(0.05f,0.05f,0.05f);
    LightManager::GetRef()->SetDiffuseColor(0.0f,0.0f,0.0f);
    LightManager::GetRef()->SetDiffuseDirection(1.0f,-0.5f,0.0f);
    
    // Set up camera
    m_camera = new MouseLookCamera;
    m_camera->SetPosition(Coord(0.0f, 0.0f, -10.0f));

    // Set up sun
    planet = new Planet;
    planet->Initialize();
    // Add graphic to game object
    graphic = new Graphic;
    graphic->SetTint(1.0f,1.0f,0.8f,1.0f);
    graphic->SetRenderTarget(m_renderTexture);
    graphic->SetShader("Texture");
    graphic->Initialize();
    planet->SetGraphic(graphic);
    // Set up game object as planet
    planet->SetOrbitRadius(0);
    planet->SetOrbitSpeed(0.1f);
    // Add planet to list
    m_gameObjects.push_back(planet);

    // Sun Light
    pLight.SetPosition(Coord(0.0f,0.0f,0.0f));
    pLight.SetColor(1.0f,1.0f,1.0f,1.0f);
    pLight.SetBrightness(3.0f);
    LightManager::GetRef()->AddLight(pLight);

    // Set up planet
    planet = new Planet;
    planet->Initialize();
    // Add graphic to game object
    graphic = new Graphic;
    graphic->SetTint(1.0f,0.0f,0.0f,1.0f);
    graphic->SetRenderTarget(m_renderTexture);
    graphic->SetShader("Light");
    graphic->Initialize();
    planet->SetGraphic(graphic);
    // Set up transforms
    graphic->SetScale(Coord(0.2f,0.2f,0.2f));
    // Set up game object as planet
    planet->SetOrbitRadius(2.0);
    planet->SetOrbitSpeed(1.0f);
    // Add planet to list
    m_gameObjects.push_back(planet);

    // Set up planet "health bar"
    planet = new Planet;
    planet->Initialize();
    graphic = new Billboard;
    graphic->SetTint(0.0f,1.0f,0.0f,1.0f);
    //graphic->SetRenderTarget(m_renderTexture);
    graphic->SetShader("Texture");
    graphic->SetRenderToBackBuffer(true);
    graphic->SetZBuffer(false);
    graphic->Initialize();
    // Set up transforms
    graphic->SetScale(Coord(0.3f,0.05f,0.2f));
    // Add graphic to game object
    planet->SetGraphic(graphic);
    // Set up game object as planet
    planet->SetOrbitRadius(2.0);
    planet->SetOrbitSpeed(1.0f);
    planet->SetOrbitCenter(Coord(0.0f,0.3f,0.0f));
    // Add planet to array
    m_overlayObjects.push_back(planet);
 

    // Set up floor
    gameObject = new GameObject;
    gameObject->Initialize();
    graphic = new Graphic;
    graphic->SetTint(0.5f,0.5f,0.3f,1.0f);
    graphic->SetShader("Light");
    graphic->SetRenderTarget(m_renderTexture);
    // Create mesh
    Mesh* mesh = new Mesh;
    mesh->Initialize(1000,1000,10.0f);
    graphic->SetModel(mesh);
    graphic->Initialize();
    // Set up transforms
    //graphic->SetScale(Coord(20.0f,20.0f,20.0f));
    // Add graphic to game object
    gameObject->SetGraphic(graphic);
    gameObject->SetPosition(Coord(0.0f,-5.0f,0.0f));
    // Add planet to array
    m_gameObjects.push_back(gameObject);
    
    // Set up particle system
    particleSystem = new ParticleSystem;
    particleSystem->Initialize();
    graphic = new Billboard;
    graphic->SetTint(01.0f,0.4f,0.0f,1.0f);
    graphic->SetShader("Texture");
    graphic->SetRenderTarget(m_renderTexture);
    graphic->SetAlphaBlend(true);
    graphic->SetTexture("particle_point");
    graphic->Initialize();
    // Set up transforms
    graphic->SetScale(Coord(0.005f,0.005f,0.005f));
    // Add graphic to game object
    particleSystem->SetGraphic(graphic);
    particleSystem->SetParticleVelocity(Coord(0.0f,0.0f,0.0f));
    particleSystem->SetParticleVelocityVariation(Coord(1.0f,0.5f,1.0f));
    particleSystem->SetParticleSpawnFrequency(0.1f);
    particleSystem->SetParticleLifetime(100.0f);
    particleSystem->SetParticleFadeout(5.0f);
    particleSystem->SetMaxParticles(100);
    particleSystem->SetTint(1.0f,1.0f,1.0f);
    particleSystem->SetTintVar(0.5f,0.5f,0.5f);
    // Add to list
    m_gameObjects.push_back(particleSystem);


    // Coordinate display
    m_position = new Text;
    m_position->SetFont("manaspace_regular_20");
    m_position->Initialize();
    m_position->SetRenderToBackBuffer(true);
	m_position->SetText(("pos: "+m_camera->GetPosition().ToString()).c_str());
    // Set up game object
    gameObject = new GameObject;
    gameObject->Initialize();
    gameObject->SetGraphic(m_position);
    m_overlayObjects.push_back(gameObject);

    // Rotation display
    m_rotation = new Text;
    m_rotation->SetFont("manaspace_regular_20");
    m_rotation->Initialize();
    m_rotation->SetRenderToBackBuffer(true);
	m_rotation->SetText(("rot: "+m_camera->GetOrientation().ToString()).c_str());
    // Set up game object
    gameObject = new GameObject;
    gameObject->Initialize();
    gameObject->SetGraphic(m_rotation);
	gameObject->SetPosition(Coord(0.0f,30.0f,0.0f));
    m_overlayObjects.push_back(gameObject);

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

    // Update position / rotation readout
	m_position->SetText(("pos: "+m_camera->GetPosition().ToString()).c_str());
	m_rotation->SetText(("rot: "+m_camera->GetOrientation().ToString()).c_str());

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