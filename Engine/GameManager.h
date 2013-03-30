// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// GameManager
//      Manages game screens and game logic within those screens.
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"
#include "Screen.h"
#include "Singleton.h"


// |----------------------------------------------------------------------------|
// |                            Class: GameManager                              |
// |----------------------------------------------------------------------------|
class GameManager : public Singleton<GameManager>
{
public:

    //|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
	GameManager();
	GameManager(const GameManager&);
	~GameManager();
    
    // Initialization and shutdown
    bool Initialize();
    void Shutdown();

    // Processes game logic each frame
    bool Frame();
    
private:

    //|-------------------------------Private Functions-------------------------|
    
    // Sets the current screen to the supplied screen index.
    int ChangeScreen(SCREEN nextScreen);

private:

    //|-----------------------------Private Data Members------------------------|
    
    // Screens
    Screen* m_currentScreen;
    Screen** m_screens;

};