// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// SkyBox
//      Contains a skybox which automatically renders at the player location. MUST be rendered first.
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Graphic.h"
#include "Quad.h"

// |----------------------------------------------------------------------------|
// |                              Class: SkyBox                                 |
// |----------------------------------------------------------------------------|
class SkyBox : public Graphic
{

public:

    //|-------------------------------Public Functions--------------------------|
    
    // Constructors and Destructors
    SkyBox();
    SkyBox(const SkyBox&);
    virtual ~SkyBox();
    
    // Initialization and shutdown
    virtual bool Initialize();
    virtual void Shutdown();

protected:

    //|------------------------------Protected Functions------------------------|

    virtual D3DXMATRIX TransformWorldMatrix(Coord position);

protected:

    //|----------------------------Protected Data Members-----------------------|

};