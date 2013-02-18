// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Material
//      Wraps information about what shader and shader settings to use.
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"


// |----------------------------------------------------------------------------|
// |                              Class: Shader                                 |
// |----------------------------------------------------------------------------|
class Material
{

public:

    //|-------------------------------Public Functions--------------------------|
    
    // Constructors and Destructors
    Material();
    
    // Initializes the material
    bool Initialize();

    // Performs shutdown, deallocation, and cleanup
    void Shutdown();

    // Getter Functions
    D3DXVECTOR4 GetTint() {return m_tint;}
    
protected:

    //|-----------------------------Protected Functions------------------------|

protected:

    //|---------------------------Protected Data Members-----------------------|
    D3DXVECTOR4 m_tint;

};