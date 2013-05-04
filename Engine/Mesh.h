// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Mesh
//      Contains model information for a mesh
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Model.h"


// |----------------------------------------------------------------------------|
// |                               Class: Mesh                                  |
// |----------------------------------------------------------------------------|
class Mesh : public Model
{

public:

    //|-------------------------------Public Functions--------------------------|
    
    // Constructors and Destructors
	Mesh();
	Mesh(const Mesh&);
	virtual ~Mesh();
	
    // Initialization and shutdown
	virtual bool Initialize();
    virtual void Shutdown();
	
protected:

    //|------------------------------Protected Functions------------------------|

    // Populates buffers with data
    virtual bool PopulateBuffers(VertexType*&, unsigned long*&);

    // Renders the buffers
    virtual void RenderBuffers();
	
protected:

    //|----------------------------Protected Data Members-----------------------|
    int m_meshWidth;
    int m_meshLength;

};