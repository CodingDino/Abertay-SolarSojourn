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
#include "Coord.h"
#include <stdlib.h>
#include <time.h>


// |----------------------------------------------------------------------------|
// |                               Class: Mesh                                  |
// |----------------------------------------------------------------------------|
class Mesh : public Model
{

private:
    
    //|-------------------------------Private Typedefs--------------------------|

    struct HeightMapType 
	{ 
		float x, y, z;
		float nx, ny, nz;
	};

public:

    //|-------------------------------Public Functions--------------------------|
    
    // Constructors and Destructors
	Mesh();
	Mesh(const Mesh&);
	virtual ~Mesh();
	
    // Initialization and shutdown
	virtual bool Initialize();
    virtual bool Initialize(int width, int length, float height = 1.0f) {
	    m_meshWidth = width;
	    m_meshLength = length;
	    m_meshHeight = height;
        return Initialize(); 
    }
    virtual void Shutdown();
	
protected:

    //|------------------------------Protected Functions------------------------|

    // Populates buffers with data
    virtual bool PopulateBuffers(VertexType*&, unsigned long*&);
    bool CalculateNormals();

    // Renders the buffers
    virtual void RenderBuffers();

    // Height map
    void GenerateHeightMap();
    void InitializeHeightMap();
    void RandomizeHeightMap();
    //void SmoothHeightMap();
    void NormalizeHeightMap();
    void ShutdownHeightMap();
	
protected:

    //|----------------------------Protected Data Members-----------------------|
    int m_meshWidth;
    int m_meshLength;
    float m_meshHeight;
    HeightMapType* m_heightMap;
};