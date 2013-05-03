// Solar Sojourn
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
#include "GameObject.h"
#include "AssetManager.h"

// |----------------------------------------------------------------------------|
// |						  Class Definition: Screen							|
// |----------------------------------------------------------------------------|
class Screen {

public:
    
    //|-------------------------------Public Functions--------------------------|

	// Constructors and Destructors
    Screen() : 
      m_done(0), 
      m_nextScreen(SCREEN_QUIT),
      m_backgroundObjects(0),
      m_gameObjects(0),
      m_overlayObjects(0) {}
    Screen(const Screen&) {}
    virtual ~Screen() {}

    // Initialization and shutdown
	bool virtual Initialize() {return true;}
	bool virtual Shutdown() {return true;}
    
	// The logic function, which will be called by the main game loop.
    bool virtual Logic() 
    { 
        bool result = true;
        if (m_backgroundObjects)
            for (int i = 0; i < m_numBackgroundObjects; ++ i) 
                if (m_backgroundObjects[i])
                    result = result && m_backgroundObjects[i]->Logic();
        if (m_gameObjects)
            for (int i = 0; i < m_numGameObjects; ++ i) 
                if (m_gameObjects[i])
                    result = result && m_gameObjects[i]->Logic();
        if (m_overlayObjects)
            for (int i = 0; i < m_numOverlayObjects; ++ i) 
                if (m_overlayObjects[i])
                    result = result && m_overlayObjects[i]->Logic();
        return result;
    }
    
	// The draw function, which will be called by the main game loop.
	bool virtual Draw()
    { 
	    DebugLog ("Screen: Draw() called.", DB_GRAPHICS, 10);
        bool result = true;
        if (m_backgroundObjects)
            for (int i = 0; i < m_numBackgroundObjects; ++ i) 
                if (m_backgroundObjects[i])
                    result = result && m_backgroundObjects[i]->Draw();
        if (m_gameObjects)
            for (int i = 0; i < m_numGameObjects; ++ i) 
                if (m_gameObjects[i])
                    result = result && m_gameObjects[i]->Draw();
        if (m_overlayObjects)
            for (int i = 0; i < m_numOverlayObjects; ++ i) 
                if (m_overlayObjects[i])
                    result = result && m_overlayObjects[i]->Draw();
        return result;
    }
    
	// Called when the screen is loaded.
	bool virtual OnLoad() = 0;
    
	// Called when switching to a different screen
	bool virtual OnExit() = 0;
    
	// Getter Functions
	SCREEN virtual GetNextScreen()  { return m_nextScreen; }
	bool virtual IsDone() { return m_done; }
    
	// Setetter Functions
	void virtual SetNextScreen(SCREEN new_next) { m_nextScreen= new_next; }
	void virtual SetDone(bool new_done) { m_done = new_done; }
	
protected:
    
    //|----------------------------Protected Data Members-----------------------|

	bool m_done;
	SCREEN m_nextScreen;

    // GameObject Array
    int m_numBackgroundObjects;
    int m_numGameObjects;
    int m_numOverlayObjects;
    GameObject** m_backgroundObjects;
    GameObject** m_gameObjects;
    GameObject** m_overlayObjects;

    // TODO
    // Array of models, materials, and textures
    // Loaded when Screen is initialized, removed when screen is shutdown
    // Pointed to by the GameObjects in this screen

};