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
#include "SkyBox.h"
#include "Text.h"

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

	// Enable / Disable post processing
	void EnablePostProcessing();
	void DisablePostProcessing();
	
protected:
    
    //|------------------------------Protected Functions------------------------|

    // PostProcessing
    bool ApplyGlowMask();
    bool BlurDownsampledTexture(int numTimes=1);
	bool DownSampleTexture();
	bool UpSampleTexture();
	bool CombineGlowTexture();
	
protected:
    
    //|----------------------------Protected Data Members-----------------------|

	bool m_done;
	SCREEN m_nextScreen;

    // Render texture for post-processing
    Texture* m_renderTexture;
    Texture* m_glowMapTexture;
    Texture* m_glowTexture;
    Texture* m_downSampleTexture;
    Texture* m_intermediate;
    Texture* m_upSampleTexture;
    Graphic* m_postProcessing;
    Graphic* m_downSampleImage;

    // Post processing options
	bool m_postProcessingEnabled;
    bool m_blur;
    bool m_glow;
    int m_downSampleFactor;

    // GameObject Array
    std::list<GameObject*> m_backgroundObjects;
    std::list<GameObject*> m_gameObjects;
    std::list<GameObject*> m_overlayObjects;

    // Special game objects
    GameObject* m_camera;
    SkyBox* m_skybox;
    SkyBox* m_sun;
    Text* m_position;
    Text* m_rotation;
    Text* m_fpsDisplay;
    Text* m_cpuDisplay;

};