// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Player
//      Managers graphics and functionality for the player ship
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"
#include "GameObject.h"
#include "ParticleSystem.h"
#include "Billboard.h"
#include "Camera.h"


// |----------------------------------------------------------------------------|
// |                         Class Definition: Player		                    |
// |----------------------------------------------------------------------------|
class Player : public GameObject {

public:
    
    //|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
	Player();
	Player(const Player&);
	virtual ~Player();

    // Initialization and shutdown
	virtual bool  Initialize();
	virtual bool  Shutdown();
    
    // Performs logic functions for the object
    virtual bool  Logic();
    
    // Renders camera
    bool virtual Draw();
	// Enable or disable post processing
	void virtual EnablePostProcessing(Texture* renderTexture) 
	{
		if(m_ship) m_ship->EnablePostProcessing(renderTexture);
		if(m_leftThruster) m_ship->EnablePostProcessing(renderTexture);
		if(m_rightThruster) m_ship->EnablePostProcessing(renderTexture);
	}
	void virtual DisablePostProcessing() 
	{ 
		if(m_ship) m_ship->DisablePostProcessing();
		if(m_leftThruster) m_ship->DisablePostProcessing();
		if(m_rightThruster) m_ship->DisablePostProcessing();
	}

	// Player functions
	void virtual Crash() {m_crashed = true;}

	// Getter functions
	bool virtual HasCrashed() { return m_crashed; }
	
    // Setter functions
    void virtual SetPosition(Coord position);
    void virtual SetOrientation(Coord orientation);
	void virtual Reset() {m_crashed = false; }

protected:
   
    //|----------------------------Protected Functions-------------------------|


protected:
    
    //|---------------------------Protected Data Members-----------------------|
	GameObject* m_ship;
	ParticleSystem* m_leftThruster;
	ParticleSystem* m_rightThruster;

	// Player parameters
	Coord m_direction;
	float m_speed;
	bool m_crashed;
};