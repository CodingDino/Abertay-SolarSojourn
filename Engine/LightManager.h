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
#include "Coord.h"

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
    D3DXVECTOR4 GetDiffuseColor() {return m_diffuseColor;}
    D3DXVECTOR3 GetDiffuseDirection() {return m_diffuseDirection;}

    // Setters
    void SetAmbient(float r, float g, float b) {m_ambient = D3DXVECTOR4(r,g,b,1.0f);}
    void SetDiffuseColor(float r, float g, float b) {m_diffuseColor = D3DXVECTOR4(r,g,b,1.0f);}
    void SetDiffuseDirection(float x, float y, float z) {m_diffuseDirection = D3DXVECTOR3(x,y,z);}
    void SetDiffuseDirection(Coord coord) {m_diffuseDirection = D3DXVECTOR3(coord.x,coord.y,coord.z);}

private:

    //|-------------------------------Private Functions-------------------------|

private:

    //|-----------------------------Private Data Members------------------------|
    D3DXVECTOR4 m_ambient;
    D3DXVECTOR4 m_diffuseColor;
    D3DXVECTOR3 m_diffuseDirection;
    

};