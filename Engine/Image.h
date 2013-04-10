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


// |----------------------------------------------------------------------------|
// |                              Class: Graphic                                |
// |----------------------------------------------------------------------------|
class Image : public Graphic
{
protected:
    
    //|----------------------------Protected Data Types-------------------------|

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:

    //|-------------------------------Public Functions--------------------------|
    
    // Constructors and Destructors
    Image();
    Image(const Image&);
    virtual ~Image();
    
    // Initialization and shutdown
    virtual bool Initialize();
    virtual void Shutdown();

    // Renders the graphic to the supplied context
    virtual void Render();

protected:

    //|------------------------------Protected Functions------------------------|
	
	// Sets up the buffers associated with this bitmap
	bool InitializeBuffers(ID3D11Device*);

	// Releases buffers associated with this model
	void ShutdownBuffers();

	// Updates buffers associated with this model
	bool UpdateBuffers(ID3D11DeviceContext*);

	// Renders the buffers
	void RenderBuffers(ID3D11DeviceContext*);

protected:

    //|----------------------------Protected Data Members-----------------------|

	// Model and texture data members
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;

	// Screen location information
	Coord m_previousPosition;

};