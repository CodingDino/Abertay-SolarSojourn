// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Material
//      Wraps information about what shader and shader settings to use.
#pragma once

// TODO: Material settings for alpha blending, back face culling, and z buffer


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include "Util.h"


// |----------------------------------------------------------------------------|
// |                            Forward Declarations                            |
// |----------------------------------------------------------------------------|
class Shader;


// |----------------------------------------------------------------------------|
// |                              Class: Material                               |
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

    // Setter Functions
    void SetShader(Shader* shader) {m_shader = shader;}
    void SetTint(float r, float g, float b, float a) 
        {m_tint = D3DXVECTOR4(r,g,b,a);}

    // Getter Functions
    Shader* GetShader() {return m_shader;}
    D3DXVECTOR4 GetTint() {return m_tint;}
    
protected:

    //|-----------------------------Protected Functions------------------------|

protected:

    //|---------------------------Protected Data Members-----------------------|
    Shader* m_shader;
    D3DXVECTOR4 m_tint;

};