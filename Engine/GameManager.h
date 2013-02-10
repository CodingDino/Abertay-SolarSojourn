// Solar Exploration Sim
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


// |----------------------------------------------------------------------------|
// |                            Class: GameManager                              |
// |----------------------------------------------------------------------------|
class GameManager
{
public:

    //|-------------------------------Public Functions--------------------------|
    
    // Returns instance
    static GameManager* GetInstance();

    // Initializes the DirectX interface
    bool Initialize();

    // Performs shutdown, deallocation, and cleanup
    void Shutdown();

    // Processes game logic each frame
    bool Frame();
    
private:

    //|-------------------------------Private Functions-------------------------|
    
    // Constructors and Destructors
    GameManager();
    
    // Sets the current screen to the supplied screen index.
    int ChangeScreen(SCREEN nextScreen);

private:

    //|-----------------------------Private Data Members------------------------|
    
    // Singleton instance
    static GameManager* s_instance;

    // Screens
    Screen* m_currentScreen;
    Screen** m_screens;

};