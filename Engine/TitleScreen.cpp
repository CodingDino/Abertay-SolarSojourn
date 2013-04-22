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

    m_numGameObjects = 1;
    m_gameObjects = new GameObject*[1];
    m_gameObjects[0] = new GameObject;
    m_gameObjects[0]->Initialize();

    // Set up material
    Material* material = new Material;
    //material->SetTint(D3DXVECTOR4(0.5f,0.5f,1.0f,1.0f));
    material->SetShader(GraphicsManager::GetRef()->GetShader("Texture"));

    // Set up texture
    Font* texture = new Font;
    texture->Initialize(D3DManager::GetRef()->GetDevice(),
		"../Engine/data/fonts/manaspace_regular_20.xml",
		L"../Engine/data/fonts/manaspace_regular_20.png");

    // Set up graphic
    Text* graphic = new Text;
    graphic->SetMaterial(material);
    graphic->SetTexture(texture);
    graphic->Initialize();

	// Set the text
	graphic->SetText("Hello World!");

    // Set up transforms
    //image->SetScale(Coord(100.0f,100.0f,0.01f));
    //image->SetOrientation(Coord(0.0f, 0.0f, 45.0f));

    // Add graphic to game object
    m_gameObjects[0]->SetGraphic(graphic);

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