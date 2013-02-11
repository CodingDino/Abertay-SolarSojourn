// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Screen
//      Abstract class for screens. Contains game objects, executes their game
//      logic.
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"


// |----------------------------------------------------------------------------|
// |                              Class: Screen                                 |
// |----------------------------------------------------------------------------|
class Screen
{

public:

    //|-------------------------------Public Functions--------------------------|
    
    // Constructors and Destructors
    Screen();
    
    // Initializes the screen
    virtual bool Initialize();

    // Performs shutdown, deallocation, and cleanup
    virtual void Shutdown();
    
    // The logic function, which will be called by the main game loop.
    // TO BE IMPLEMENTED BY SUB CLASS
    virtual bool Frame() = 0;
    
    // Called when the screen is loaded.
    // TO BE IMPLEMENTED BY SUB CLASS
    virtual bool OnLoad() = 0;
    
    // Called when switching to a different screen
    // TO BE IMPLEMENTED BY SUB CLASS
    virtual bool OnExit() = 0;
    
    // Returns whether the screen is done (ready to close) or not.
    virtual bool IsDone() { return m_done; }
    
    // Tells the game class what screen to load after this one
    virtual SCREEN GetNextScreen()  { return m_nextScreen; }
    
    // Sets the screen that will be loaded after this one
    virtual void SetNextScreen(SCREEN nextScreen) { m_nextScreen = nextScreen; }
    
    // Sets whether the screen will quit or not
    virtual void SetDone(bool done) { m_done = done; }

protected:

    //|-----------------------------Protected Functions------------------------|


protected:

    //|---------------------------Protected Data Members-----------------------|

    bool m_done;
    SCREEN m_nextScreen;

};