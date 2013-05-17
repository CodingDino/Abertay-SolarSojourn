// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Billboard
//      Contains data for a single 2D billboard, rendered on a quad and 
//      automatically turned to face the camera
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Graphic.h"
#include "Quad.h"

// |----------------------------------------------------------------------------|
// |                             Class: Billboard                               |
// |----------------------------------------------------------------------------|
class Billboard : public Graphic
{

public:

    //|-------------------------------Public Functions--------------------------|
    
    // Constructors and Destructors
    Billboard();
    Billboard(const Billboard&);
    virtual ~Billboard();
    
    // Initialization and shutdown
    virtual bool Initialize();
    virtual void Shutdown();

protected:

    //|------------------------------Protected Functions------------------------|

    virtual D3DXMATRIX TransformWorldMatrix(Coord position);

protected:

    //|----------------------------Protected Data Members-----------------------|

};