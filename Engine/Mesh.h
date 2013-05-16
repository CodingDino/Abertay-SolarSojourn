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
#include "noise/noise.h"


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
		float tu, tv;
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

	// Getters
	virtual float GetHeight(float realX, float realZ)
	{
		int mapX = m_meshWidth / 2 // 0 point
			+ realX / m_quadSize;  // scaling factor
		mapX = Clamp(mapX,0,m_meshWidth);
		int mapZ = m_meshLength / 2 // 0 point
			+ realZ / m_quadSize;  // scaling factor
		mapZ = Clamp(mapZ,0,m_meshLength);

		int index = (m_meshWidth * mapZ) + mapX;

		return m_heightMap[index].y;
	}
	
protected:

    //|------------------------------Protected Functions------------------------|

    // Populates buffers with data
    virtual bool PopulateBuffers(VertexType*&, unsigned long*&);
    bool CalculateNormals();
    void CalculateTextureCoordinates();

    // Renders the buffers
    virtual void RenderBuffers();

    // Height map
    void GenerateHeightMap();
    void InitializeHeightMap();
    void RandomizeHeightMap();
    void PerlinNoiseHeightMap();
    //void SmoothHeightMap();
    void NormalizeHeightMap();
    void SmoothHeightMap(int smoothFactor);
    void ShutdownHeightMap();
	
protected:

    //|----------------------------Protected Data Members-----------------------|
    int m_meshWidth;
    int m_meshLength;
    float m_meshHeight;
    float m_quadSize;
    HeightMapType* m_heightMap;

    int m_textureRepeat;
};