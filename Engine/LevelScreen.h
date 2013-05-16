// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// LevelScreen
//      Main game screen. properties can be customized to change level appearance.
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
#include "Mesh.h"
#include "Player.h"
#include "Bullet.h"




// |----------------------------------------------------------------------------|
// |						  Class Definition: LevelScreen						|
// |----------------------------------------------------------------------------|
class LevelScreen : public Screen {

public:
    
    //|-------------------------------Public Functions--------------------------|

	// Constructors and Destructors
	LevelScreen();
	LevelScreen(const LevelScreen&);
	virtual ~LevelScreen();

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
    
    // Special game objects
    GameObject* m_particles;
	ParticleSystem* m_fireball;
	ParticleSystem* m_flash;
	Player* m_player;
	Mesh* m_terrain;
	Planet* m_objective1;
	Planet* m_objective2;
	Planet* m_objective3;
    std::list<Bullet*> m_bullets;
	Graphic* m_dialogue;
	Text* m_loss;
	Text* m_win;

	// Gameplay parameters
	
};