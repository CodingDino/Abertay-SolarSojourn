// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Mesh
//      Contains model information for a mesh


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "Mesh.h"


// |----------------------------------------------------------------------------|
// |						   Default Constructor								|
// |----------------------------------------------------------------------------|
Mesh::Mesh() : Model()
{
}

// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
Mesh::Mesh(const Mesh& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
Mesh::~Mesh()
{
}


// |----------------------------------------------------------------------------|
// |						      Initialize									|
// |----------------------------------------------------------------------------|
bool Mesh::Initialize()
{
	DebugLog ("Mesh::Initialize() called.", DB_GRAPHICS, 1);
	bool result;

    
	// Manually set the width and height of the terrain.
    // TODO: Make this a parameter!
	m_meshWidth = 100;
	m_meshLength = 100;

	// Set the number of vertices and indices.
	m_vertexCount = (m_meshWidth - 1) * (m_meshLength - 1) * 8;
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
// |						      Shutdown		    							|
// |----------------------------------------------------------------------------|
void Mesh::Shutdown()
{
	DebugLog ("Mesh::Shutdown() called.", DB_GRAPHICS, 1);
	
	return;
}


// |----------------------------------------------------------------------------|
// |						  PopulateBuffers									|
// |----------------------------------------------------------------------------|
bool Mesh::PopulateBuffers(VertexType*& vertices, unsigned long*& indices)
{
	DebugLog ("Mesh::PopulateBuffers() called.", DB_GRAPHICS, 10);
    
    // Define Variables
	float positionX, positionZ;
	int index, i, j;
    float startX, startZ;

    // Initialize the index to the vertex array.
	index = 0;

    // Initialize starting position
    startX = 0.0f - m_meshWidth/2;
    startZ = 0.0f - m_meshLength/2;

	// Load the vertex and index arrays with the terrain data.
	for(j=0; j<(m_meshLength-1); j++)
	{
		for(i=0; i<(m_meshWidth-1); i++)
		{
			// LINE 1
			// Upper left.
			positionX = startX + (float)i;
			positionZ = startZ + (float)(j+1);

			vertices[index].position = D3DXVECTOR3(positionX, 0.0f, positionZ);
			vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			indices[index] = index;
			index++;

			// Upper right.
			positionX = startX + (float)(i+1);
			positionZ = startZ + (float)(j+1);

			vertices[index].position = D3DXVECTOR3(positionX, 0.0f, positionZ);
			vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			indices[index] = index;
			index++;

			// LINE 2
			// Upper right.
			positionX = startX + (float)(i+1);
			positionZ = startZ + (float)(j+1);

			vertices[index].position = D3DXVECTOR3(positionX, 0.0f, positionZ);
			vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			indices[index] = index;
			index++;

			// Bottom right.
			positionX = startX + (float)(i+1);
			positionZ = startZ + (float)j;

			vertices[index].position = D3DXVECTOR3(positionX, 0.0f, positionZ);
			vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			indices[index] = index;
			index++;

			// LINE 3
			// Bottom right.
			positionX = startX + (float)(i+1);
			positionZ = startZ + (float)j;

			vertices[index].position = D3DXVECTOR3(positionX, 0.0f, positionZ);
			vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			indices[index] = index;
			index++;

			// Bottom left.
			positionX = startX + (float)i;
			positionZ = startZ + (float)j;

			vertices[index].position = D3DXVECTOR3(positionX, 0.0f, positionZ);
			vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			indices[index] = index;
			index++;

			// LINE 4
			// Bottom left.
			positionX = startX + (float)i;
			positionZ = startZ + (float)j;

			vertices[index].position = D3DXVECTOR3(positionX, 0.0f, positionZ);
			vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			indices[index] = index;
			index++;

			// Upper left.
			positionX = startX + (float)i;
			positionZ = startZ + (float)(j+1);

			vertices[index].position = D3DXVECTOR3(positionX, 0.0f, positionZ);
			vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			indices[index] = index;
			index++;			
		}
	}

	return true;
}


// |----------------------------------------------------------------------------|
// |						   RenderBuffers									|
// |----------------------------------------------------------------------------|
void Mesh::RenderBuffers()
{
	DebugLog ("Mesh::RenderBuffers() called.", DB_GRAPHICS, 10);

	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	D3DManager::GetRef()->GetDeviceContext()
		->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
	D3DManager::GetRef()->GetDeviceContext()
		->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	D3DManager::GetRef()->GetDeviceContext()
		->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	return;
}
