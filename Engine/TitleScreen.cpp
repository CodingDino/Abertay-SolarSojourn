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
TitleScreen::TitleScreen()
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

    // Set lighting
    LightManager::GetRef()->SetAmbient(0.05f,0.05f,0.05f);
    LightManager::GetRef()->SetDiffuseColor(0.7f,0.7f,0.7f);
    LightManager::GetRef()->SetDiffuseDirection(0.0f,-1.0f,0.0f);
    PointLight pLight;
    pLight.SetPosition(Coord(0.0f,-4.0f,0.0f));
    pLight.SetColor(0.0f,1.0f,0.0f,1.0f);
    pLight.SetBrightness(1.0f);
    //LightManager::GetRef()->AddLight(pLight); // Green Light
    pLight.SetPosition(Coord(1.5f,0.0f,0.0f));
    pLight.SetColor(0.0f,0.0f,1.0f,1.0f);
    pLight.SetBrightness(1.0f);
    LightManager::GetRef()->AddLight(pLight); // Blue Light

    // Set next screen to SCREEN_QUIT
	SetNextScreen(SCREEN_QUIT);

    m_numGameObjects = 5;
    m_gameObjects = new GameObject*[m_numGameObjects];

    // Set up sun
    Planet* gameObject = new Planet;
    gameObject->Initialize();
    Graphic* graphic = new Graphic;
    graphic->SetTint(1.0f,1.0f,1.0f,1.0f);
    graphic->SetShader("Light");
    graphic->Initialize();
    graphic->SetReflectiveness(0.9f);
    // Add graphic to game object
    gameObject->SetGraphic(graphic);
    // Set up game object as planet
    gameObject->SetOrbitRadius(0);
    gameObject->SetOrbitSpeed(0.1f);
    // Add planet to array
    m_gameObjects[0] = gameObject;


    // Set up camera
    m_gameObjects[1] = new MouseLookCamera;
    m_gameObjects[1]->SetPosition(Coord(0.0f, 0.0f, -10.0f));
    
    // Set up planet
    Planet* planet = new Planet;
    planet->Initialize();
    graphic = new Graphic;
    //graphic->SetTint(1.0f,0.0f,0.0f,1.0f);
    graphic->SetShader("Light");
    graphic->Initialize();
    // Set up transforms
    graphic->SetScale(Coord(0.2f,0.2f,0.2f));
    // Add graphic to game object
    planet->SetGraphic(graphic);
    // Set up game object as planet
    planet->SetOrbitRadius(2.0);
    planet->SetOrbitSpeed(1.0f);
    // Add planet to array
    m_gameObjects[2] = planet;
    
    // Set up floor
    GameObject* floor = new GameObject;
    floor->Initialize();
    graphic = new Graphic;
    graphic->SetTint(1.0f,1.0f,1.0f,1.0f);
    graphic->SetTexture("seafloor");
    graphic->SetShader("Light");
    // Create mesh
    Mesh* mesh = new Mesh;
    mesh->Initialize(10,20,3.0f);
    graphic->SetModel(mesh);
    graphic->Initialize();
    // Set up transforms
    //graphic->SetScale(Coord(20.0f,20.0f,20.0f));
    // Add graphic to game object
    floor->SetGraphic(graphic);
    floor->SetPosition(Coord(0.0f,-5.0f,0.0f));
    // Add planet to array
    m_gameObjects[3] = floor;
    
    // Set up particle system
    ParticleSystem* spark = new ParticleSystem;
    spark->Initialize();
    graphic = new Billboard;
    graphic->SetTint(01.0f,0.4f,0.0f,1.0f);
    graphic->SetShader("Texture");
    graphic->SetAlphaBlend(true);
    graphic->SetTexture("particle_point");
    graphic->Initialize();
    // Set up transforms
    graphic->SetScale(Coord(0.005f,0.005f,0.005f));
    // Add graphic to game object
    spark->SetGraphic(graphic);
    spark->SetParticleVelocity(Coord(0.0f,0.0f,0.0f));
    spark->SetParticleVelocityVariation(Coord(1.0f,0.5f,1.0f));
    spark->SetParticleSpawnFrequency(0.000001f);
    spark->SetParticleLifetime(10.0f);
    spark->SetParticleFadeout(5.0f);
    spark->SetMaxParticles(100000);
    spark->SetTint(1.0f,1.0f,1.0f);
    spark->SetTintVar(0.0f,0.0f,0.0f);
    //spark->SetTintVar(0.5f,0.5f,0.5f);
    // Add planet to array
    m_gameObjects[4] = spark;



    // Set up text for coord display
    m_numOverlayObjects = 2;
    m_overlayObjects = new GameObject*[m_numOverlayObjects];

    Text* text = new Text;
    text->SetFont("manaspace_regular_20");
    text->Initialize();
    m_overlayObjects[0] = new GameObject;
	m_overlayObjects[0]->SetGraphic(text);
    // Set up text for rotation display
    Text* rotation = new Text;
    rotation->SetFont("manaspace_regular_20");
    rotation->Initialize();
    m_overlayObjects[1] = new GameObject;
	m_overlayObjects[1]->SetGraphic(rotation);
	m_overlayObjects[1]->SetPosition(Coord(0.0f,30.0f,0.0f));

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
	((Text*)(m_overlayObjects[0]->GetGraphic()))->SetText(("pos: "+m_gameObjects[1]->GetPosition().ToString()).c_str());
	((Text*)(m_overlayObjects[1]->GetGraphic()))->SetText(("rot: "+m_gameObjects[1]->GetOrientation().ToString()).c_str());
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