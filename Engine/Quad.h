// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Quad
//      Contains model information for a quad
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Model.h"


// |----------------------------------------------------------------------------|
// |                               Class: Quad                                  |
// |----------------------------------------------------------------------------|
class Quad : public Model
{

public:

    //|-------------------------------Public Functions--------------------------|
    
    // Constructors and Destructors
	Quad();
	Quad(const Quad&);
	virtual ~Quad();
	
    // Initialization and shutdown
	virtual bool Initialize();
	
protected:

    //|------------------------------Protected Functions------------------------|

    // Populates buffers with data
    virtual bool PopulateBuffers(VertexType*&, unsigned long*&);
	
protected:

    //|----------------------------Protected Data Members-----------------------|


};