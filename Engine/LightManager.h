// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// LightManager
//      Holds light information that can be accessed by shaders
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"
#include "Singleton.h"
#include <d3dx10math.h>

// |----------------------------------------------------------------------------|
// |                             Class: LightManager                            |
// |----------------------------------------------------------------------------|
class LightManager : public Singleton<LightManager>
{
public:

    //|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
    LightManager() : m_ambient(0.0f,0.0f,0.0f,1.0f) 
        {}
	LightManager(const LightManager&) {}
	~LightManager() {}
    
    // Initialization and shutdown
    bool Initialize() {return true;}
    void Shutdown() {}

    // Getters
    D3DXVECTOR4 GetAmbient() {return m_ambient;}

    // Setters
    void SetAmbient(float r, float g, float b) {m_ambient = D3DXVECTOR4(r,g,b,1.0f);}

private:

    //|-------------------------------Private Functions-------------------------|

private:

    //|-----------------------------Private Data Members------------------------|
    D3DXVECTOR4 m_ambient;
    

};