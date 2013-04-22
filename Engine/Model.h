// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Model
//      Contains model data.
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
#include "Util.h"
#include "D3DManager.h"
#include "VertexType.h"
using namespace std;


// |----------------------------------------------------------------------------|
// |                              Class: Model                                  |
// |----------------------------------------------------------------------------|
class Model
{
private:

    //|-----------------------------Private Data Types--------------------------|

    // Holds vertex information, to be passed to shaders
    struct ModelType
    {
        float x, y, z;          // Vertex position in 3d space
        float tu, tv;           // Texture coordinate for 2D texture
        float nx, ny, nz;       // Normal vector for this vertex
    };

public:

    //|-------------------------------Public Functions--------------------------|
    
    // Constructors and Destructors
    Model();

    // Initialize the model, reads in a vertex and texture file
	virtual bool Initialize() {return true;}
    virtual bool Initialize(char* modelFilename);

    // Releases data associated with the model
    virtual void Shutdown();

    // Renders the model to the supplied context
    virtual void Render();

    // Getter functions
    virtual int GetIndexCount();

protected:

    //|------------------------------Protected Functions------------------------|

    // Sets up the buffers associated with this model
    virtual bool InitializeBuffers();

    // Populates buffers with data
    virtual bool PopulateBuffers(VertexType*&, unsigned long*&);

    // Releases buffers associated with this model
    virtual void ShutdownBuffers();

    // Renders the buffers
    virtual void RenderBuffers();

    // Loads the given model from file
    virtual bool LoadModel(char*);

    // Releases the model data
    virtual void ReleaseModel();

protected:

    //|----------------------------Protected Data Members-----------------------|

    // Buffers
    ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;

    // Number of vertices and indices
    int m_vertexCount, m_indexCount;

    // Model
    ModelType* m_model;

	// Buffer flags
	D3D11_USAGE m_bufferUsage;
	UINT m_bufferCPUAccess;
};