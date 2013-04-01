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

	return true;
}

// |----------------------------------------------------------------------------|
// |							     Draw()										|
// |----------------------------------------------------------------------------|
// The draw function, which will be called by the main game loop.
bool TitleScreen::Draw() {
	DebugLog ("TitleScreen: Draw() called.", DB_GRAPHICS, 10);

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