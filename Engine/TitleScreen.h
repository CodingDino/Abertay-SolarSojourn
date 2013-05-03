// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// TitleScreen
//      Splash screen shown at the start of the game
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Screen.h"
#include "Util.h"
#include "Image.h"
#include "Text.h"
#include "Planet.h"
#include "MouseLookCamera.h"
#include "Billboard.h"
#include "ParticleSystem.h"
#include "LightManager.h"


// |----------------------------------------------------------------------------|
// |						  Class Definition: MenuScreen						|
// |----------------------------------------------------------------------------|
class TitleScreen : public Screen {

public:
    
    //|-------------------------------Public Functions--------------------------|

	// Constructors and Destructors
	TitleScreen();
	TitleScreen(const TitleScreen&);
	virtual ~TitleScreen();

    // Initialization and shutdown
	bool virtual Initialize();
	bool virtual Shutdown();
    
	// The logic function, which will be called by the main game loop.
	bool virtual Logic();
    
	// The draw function, which will be called by the main game loop.
	bool virtual Draw();
    
	// Called when the screen is loaded.
	bool virtual OnLoad();
    
	// Called when switching to a different screen
	bool virtual OnExit();
	
protected:
    
    //|----------------------------Protected Data Members-----------------------|
};