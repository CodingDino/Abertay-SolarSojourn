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
    m_position(0),
    m_rotation(0),
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
    LightManager::GetRef()->SetFogDensity(0.05f);
    
    // Set up camera
    m_camera = new MouseLookCamera;
    m_camera->SetPosition(Coord(0.0f, 0.0f, -10.0f));

    // Set up skybox
    m_skybox->SetTexture("default");
    m_skybox->SetTint(0.8f,0.6f,0.6f);

    // Set up sun
    m_sun->SetTint(1.0f,1.0f,0.8f,1.0f);
    m_sun->SetRenderTarget(m_renderTexture);
    m_sun->SetShader("Texture");
    m_sun->SetModel("sphere");
    m_sun->Initialize();
    m_sun->SetPosition(Coord(10.0f,5.0f,10.0f));
    float intensity = 0.07;
    LightManager::GetRef()->SetDiffuseColor(m_sun->GetTintR(),m_sun->GetTintG(),m_sun->GetTintB());
    LightManager::GetRef()->SetDiffuseDirection(-1*intensity*m_sun->GetPosition().x,-1*intensity*m_sun->GetPosition().y,-1*intensity*m_sun->GetPosition().z);
    
    planet = new Planet;
    planet->Initialize();
    m_gameObjects.push_back(planet);

    // Sun Light
    pLight.SetPosition(Coord(0.0f,0.0f,0.0f));
    pLight.SetColor(1.0f,1.0f,1.0f,1.0f);
    pLight.SetBrightness(3.0f);
    //LightManager::GetRef()->AddLight(pLight);

    // Set up planet
    planet = new Planet;
    planet->Initialize();
    // Add graphic to game object
    graphic = new Graphic;
    graphic->SetTint(1.0f,0.0f,0.0f,1.0f);
    graphic->SetRenderTarget(m_renderTexture);
    graphic->SetShader("Light");
    graphic->Initialize();
    graphic->SetReflectiveness(0.98f);
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
    //m_overlayObjects.push_back(planet);
 

    // Set up floor
    gameObject = new GameObject;
    gameObject->Initialize();
    graphic = new Graphic;
    graphic->SetTint(0.8f,0.6f,0.4f,1.0f);
    graphic->SetShader("Light");
    graphic->SetRenderTarget(m_renderTexture);
    graphic->SetReflectiveness(0.0f);
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
    graphic->SetAlphaBlend(true);
    graphic->SetTexture("particle_point");
    graphic->Initialize();
    //graphic->SetRenderTarget(m_renderTexture);
    graphic->SetRenderToBackBuffer(false);
    graphic->SetRenderTarget(m_renderTexture);
    // Set up transforms
    graphic->SetScale(Coord(0.005f,0.005f,0.005f));
    // Add graphic to game object
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
    // Add to list
    m_particles = particleSystem;
    m_gameObjects.push_back(particleSystem);
    //m_overlayObjects.push_back(particleSystem);


    // Coordinate display
    m_position = new Text;
    m_position->SetFont("default");
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
    m_rotation->SetFont("default");
    m_rotation->Initialize();
    m_rotation->SetRenderToBackBuffer(true);
	m_rotation->SetText(("rot: "+m_camera->GetOrientation().ToString()).c_str());
    // Set up game object
    gameObject = new GameObject;
    gameObject->Initialize();
    gameObject->SetGraphic(m_rotation);
	gameObject->SetPosition(Coord(0.0f,30.0f,0.0f));
    m_overlayObjects.push_back(gameObject);

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

    // Update position / rotation readout
	m_position->SetText(("pos: "+m_camera->GetPosition().ToString()).c_str());
	m_rotation->SetText(("rot: "+m_camera->GetOrientation().ToString()).c_str());

    // Update coord location
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