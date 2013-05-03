// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Image
//      Contains data for a single 2D image, including texture and rendering method.
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Graphic.h"
#include "Quad.h"

// |----------------------------------------------------------------------------|
// |                               Class: Image                                 |
// |----------------------------------------------------------------------------|
class Image : public Graphic
{

public:

    //|-------------------------------Public Functions--------------------------|
    
    // Constructors and Destructors
    Image();
    Image(const Image&);
    virtual ~Image();
    
    // Initialization and shutdown
    virtual bool Initialize();
    virtual void Shutdown();

protected:

    //|------------------------------Protected Functions------------------------|
    
    // Performs the transforms on the graphic
    virtual D3DXMATRIX PerformTransforms(Coord position);

protected:

    //|----------------------------Protected Data Members-----------------------|

};