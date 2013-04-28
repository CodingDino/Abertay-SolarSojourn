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

    m_numGameObjects = 2;
    m_gameObjects = new GameObject*[m_numGameObjects];
    Planet* gameObject = new Planet;
    gameObject->Initialize();

    // Set up material
    Material* material = new Material;
    material->SetTint(D3DXVECTOR4(0.5f,0.5f,1.0f,1.0f));
    material->SetShader(GraphicsManager::GetRef()->GetShader("Color"));

    // Set up texture
    //Font* texture = new Font;
    //texture->Initialize(D3DManager::GetRef()->GetDevice(),
	//	"../Engine/data/fonts/manaspace_regular_20.xml",
	//	L"../Engine/data/fonts/manaspace_regular_20.png");

    // Set up model
    Model* model = new Model;
    model->Initialize("../Engine/data/models/sphere.txt");

    // Set up graphic
    Graphic* graphic = new Graphic;
    graphic->SetMaterial(material);
    graphic->SetModel(model);
    graphic->Initialize();

    // Set up transforms
    //image->SetScale(Coord(100.0f,100.0f,0.01f));
    //image->SetOrientation(Coord(0.0f, 0.0f, 45.0f));

    // Add graphic to game object
    gameObject->SetGraphic(graphic);

    // Set up game object as planet
    gameObject->SetOrbitRadius(2);
    gameObject->SetOrbitSpeed(0.1);

    // Add gameObject to array
    m_gameObjects[0] = gameObject;

    // Set up camera
    m_gameObjects[1] = new MouseLookCamera;


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