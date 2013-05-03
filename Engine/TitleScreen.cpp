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

    // Set next screen to SCREEN_QUIT
	SetNextScreen(SCREEN_QUIT);

    m_numGameObjects = 5;
    m_gameObjects = new GameObject*[m_numGameObjects];
	

    // Set up sun
    Planet* gameObject = new Planet;
    Texture* sun_tex = new Texture;
    sun_tex->Initialize(D3DManager::GetRef()->GetDevice(),
		L"../Engine/data/textures/default.png");
    gameObject->Initialize();
    Material* material = new Material;
    material->SetTint(1.0f,0.5f,0.0f,1.0f);
    material->shader = GraphicsManager::GetRef()->GetShader("Light");
    Model* model = new Model;
    model->Initialize("../Engine/data/models/sphere.txt");
    Graphic* graphic = new Graphic;
    graphic->SetMaterial(material);
    graphic->SetModel(model);
    graphic->SetTexture(sun_tex);
    graphic->Initialize();
    // Set up transforms
    //image->SetScale(Coord(100.0f,100.0f,0.01f));
    //image->SetOrientation(Coord(0.0f, 0.0f, 45.0f));
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
    material = new Material;
    material->SetTint(1.0f,0.0f,0.0f,1.0f);
    material->shader = GraphicsManager::GetRef()->GetShader("Color");
    graphic = new Graphic;
    graphic->SetMaterial(material);
    graphic->SetModel(model);
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
    material = new Material;
    material->SetTint(0.7f,0.6f,0.5f,1.0f);
    material->shader = GraphicsManager::GetRef()->GetShader("Color");
    graphic = new Graphic;
    graphic->SetMaterial(material);
    Quad* quad = new Quad;
    quad->Initialize();
    graphic->SetModel(quad);
    graphic->Initialize();
    // Set up transforms
    graphic->SetScale(Coord(20.0f,20.0f,20.0f));
    // Add graphic to game object
    floor->SetGraphic(graphic);
    floor->SetPosition(Coord(0.0f,-5.0f,0.0f));
    floor->SetOrientation(Coord(0.0f,90.0f * PI / 180,0.0f));
    // Add planet to array
    m_gameObjects[3] = floor;
    
    // Set up particle system
    ParticleSystem* spark = new ParticleSystem;
    spark->Initialize();
    Texture* texture = new Texture;
    texture->Initialize(D3DManager::GetRef()->GetDevice(),
		L"../Engine/data/textures/particle_point.png");
    material = new Material;
    material->SetTint(01.0f,0.4f,0.0f,1.0f);
    material->shader = GraphicsManager::GetRef()->GetShader("Texture");
    material->alphaBlend = true;
    graphic = new Billboard;
    graphic->SetMaterial(material);
    graphic->SetModel(quad);
    graphic->SetTexture(texture);
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
    spark->SetTint(1.0f,1.0f,0.8f);
    spark->SetTintVar(0.5f,0.5f,0.5f);
    //spark->SetOrientation(Coord(0.0f,90.0f * PI / 180,0.0f));
    // Add planet to array
    m_gameObjects[4] = spark;



    // Set up text for coord display
    m_numOverlayObjects = 2;
    m_overlayObjects = new GameObject*[m_numOverlayObjects];

    Font* font = new Font;
    font->Initialize(D3DManager::GetRef()->GetDevice(),
		"../Engine/data/fonts/manaspace_regular_20.xml",
		L"../Engine/data/fonts/manaspace_regular_20.png");
    Text* text = new Text;
	text->SetTexture(font);
    text->Initialize();
    m_overlayObjects[0] = new GameObject;
	m_overlayObjects[0]->SetGraphic(text);
    // Set up text for rotation display
    Text* rotation = new Text;
	rotation->SetTexture(font);
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