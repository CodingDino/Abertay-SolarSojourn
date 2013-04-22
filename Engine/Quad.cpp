// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Quad
//      Contains model information for a quad


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "Quad.h"


// |----------------------------------------------------------------------------|
// |						   Default Constructor								|
// |----------------------------------------------------------------------------|
Quad::Quad() : Model()
{
}

// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
Quad::Quad(const Quad& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
Quad::~Quad()
{
}


// |----------------------------------------------------------------------------|
// |						      Initialize									|
// |----------------------------------------------------------------------------|
bool Quad::Initialize()
{
	DebugLog ("Quad::Initialize() called.", DB_GRAPHICS, 1);
	bool result;

	// Set the number of vertices and indices.
	m_vertexCount = 6;
	m_indexCount = m_vertexCount;

	// Set buffer flags
	m_bufferUsage = D3D11_USAGE_DEFAULT;
	m_bufferCPUAccess = 0;
	
	// Initialize the vertex and index buffers.
	result = InitializeBuffers();
	if(!result)
	{
		return false;
	}

	return true;
}


// |----------------------------------------------------------------------------|
// |						  PopulateBuffers									|
// |----------------------------------------------------------------------------|
bool Quad::PopulateBuffers(VertexType*& vertices, unsigned long*& indices)
{
	DebugLog ("Quad::PopulateBuffers() called.", DB_GRAPHICS, 10);

	// Load the vertex array and index array with data.
	for(int i=0; i<m_indexCount; i++)
	{
		indices[i] = i;
	}

	// First triangle.
	vertices[0].position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f); // Top Left
	vertices[0].texture = D3DXVECTOR2(0.0f, 0.0f);

	vertices[1].position = D3DXVECTOR3(0.5f, 0.5f, 0.0f); // Top Right
	vertices[1].texture = D3DXVECTOR2(1.0f, 0.0f);

	vertices[2].position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f); // Bottom Left
	vertices[2].texture = D3DXVECTOR2(0.0f, 1.0f);

	// Second triangle.
	vertices[3].position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f); // Bottom Left
	vertices[3].texture = D3DXVECTOR2(0.0f, 1.0f);

	vertices[4].position = D3DXVECTOR3(0.5f, 0.5f, 0.0f); // Top Right
	vertices[4].texture = D3DXVECTOR2(1.0f, 0.0f);

	vertices[5].position = D3DXVECTOR3(0.5f, -0.5f, 0.0f); // Bottom Right
	vertices[5].texture = D3DXVECTOR2(1.0f, 1.0f);

	return true;
}