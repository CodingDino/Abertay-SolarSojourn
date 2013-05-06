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
#include <list>
#include "Image.h"
#include "MouseLookCamera.h"

// |----------------------------------------------------------------------------|
// |						  Class Definition: Screen							|
// |----------------------------------------------------------------------------|
class Screen {

public:
    
    //|-------------------------------Public Functions--------------------------|

	// Constructors and Destructors
    Screen();
    Screen(const Screen&) {}
    virtual ~Screen() {}

    // Initialization and shutdown
	bool virtual Initialize();
	bool virtual Shutdown();
    
	// The logic function, which will be called by the main game loop.
    bool virtual Logic();
    
	// The draw function, which will be called by the main game loop.
	bool virtual Draw();
    
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
    
    //|------------------------------Protected Functions------------------------|

    // PostProcessing
    bool Blur();
	
protected:
    
    //|----------------------------Protected Data Members-----------------------|

	bool m_done;
	SCREEN m_nextScreen;

    // Render texture for post-processing
    Texture* m_renderTexture;
    Texture* m_intermediate;
    Graphic* m_postProcessing;

    // Post processing options
    bool m_blur;

    // GameObject Array
    std::list<GameObject*> m_backgroundObjects;
    std::list<GameObject*> m_gameObjects;
    std::list<GameObject*> m_overlayObjects;

    // Special game objects
    GameObject* m_camera; // TODO: Make a game object camera base class

};