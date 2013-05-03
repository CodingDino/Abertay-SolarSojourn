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

    Shader* shader;
    float tintR, tintG, tintB;
    float alpha;
    bool alphaBlend;
    bool particleBlend;
    bool backfaceCull;
    bool zBuffer;

    Material() : 
        shader(0),
        tintR(1.0),
        tintG(1.0),
        tintB(1.0),
        alpha(1.0),
        alphaBlend(false),
        particleBlend(false),
        backfaceCull(true),
        zBuffer(true)
    {}

    void SetTint(float r, float g, float b, float a = 1.0f) {
        tintR = r;
        tintG = g;
        tintB = b;
        alpha = a;
    }

};