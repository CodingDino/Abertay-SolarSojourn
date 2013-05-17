// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Planet
//      GameObject class that handles planet orbiting.
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"
#include "GameObject.h"
#include <cmath>
#define PI 3.14159265


// |----------------------------------------------------------------------------|
// |                        Class Definition: Planet                            |
// |----------------------------------------------------------------------------|
class Planet : public GameObject {

public:
    
    //|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
	Planet();
	Planet(const Planet&);
	virtual ~Planet();

    // Initialization and shutdown
	virtual bool  Initialize();
	virtual bool  Shutdown();
    
    // Performs logic functions for the object
    virtual bool  Logic();

    // Getter functions
    virtual Coord  GetOrbitCenter() {return m_orbitCenter;}
    virtual GameObject* GetOrbitCenterObject() {return m_orbitCenterObject;}
    virtual float  GetOrbitRadius() {return m_orbitRadius;}
    virtual float  GetOrbitSpeed() {return m_orbitSpeed;}
    virtual float  GetOrbitTilt() {return m_orbitTilt;}
    virtual float  GetOrbitAngle() {return m_orbitAngle;}

    // Setter functions
    virtual void  SetOrbitCenter(Coord orbitCenter) {m_orbitCenter = orbitCenter;}
    virtual void  SetOrbitCenter(GameObject* orbitCenter) {m_orbitCenterObject = orbitCenter;}
    virtual void  SetOrbitRadius(float orbitRadius) {m_orbitRadius = orbitRadius;}
    virtual void  SetOrbitSpeed(float orbitSpeed) {m_orbitSpeed = orbitSpeed;}
    virtual void  SetOrbitTilt(float orbitTilt) {m_orbitTilt = orbitTilt;}
    virtual void  SetOrbitAngle(float orbitAngle) {m_orbitAngle = orbitAngle;}

	// Enable or disable post processing
	void virtual EnablePostProcessing(Texture* renderTexture) 
	{
		if(!m_graphic) return;
    	m_graphic->SetRenderTarget(renderTexture);
		m_graphic->SetRenderToBackBuffer(false);
	}
	void virtual DisablePostProcessing() 
	{ 
		if(!m_graphic) return;
    	m_graphic->SetRenderTarget(0);
		m_graphic->SetRenderToBackBuffer(true);
	}

protected:
    
    //|---------------------------Protected Data Members-----------------------|
    Coord m_orbitCenter;                // Orbit center coordinate
    GameObject* m_orbitCenterObject;    // Orbit can be centered on an object
    float m_orbitRadius;                // Radius of orbit
    float m_orbitSpeed;                 // Speed of orbit in radians / second
    float m_orbitTilt;                  // Tilt orientation of orbit plane, from horizontal around center
    float m_orbitAngle;                 // Current position in orbit, in radians
};