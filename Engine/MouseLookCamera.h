// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// MouseLookCamera
//      GameObject class that mouse look, and adjusts the main camera if set to active.
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"
#include "GameObject.h"
#include "InputManager.h"
#define PI 3.14159265


// |----------------------------------------------------------------------------|
// |                    Class Definition: MouseLookCamera                       |
// |----------------------------------------------------------------------------|
class MouseLookCamera : public GameObject {

public:
    
    //|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
	MouseLookCamera();
	MouseLookCamera(const MouseLookCamera&);
	virtual ~MouseLookCamera();

    // Initialization and shutdown
	virtual bool  Initialize();
	virtual bool  Shutdown();
    
    // Performs logic functions for the object
    virtual bool  Logic();
    
    // Renders camera
    bool virtual Draw();

protected:
    
    //|---------------------------Protected Data Members-----------------------|
    bool m_active;
    float m_mouseSensitivity;
	float m_speed;
};