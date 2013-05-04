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
Mesh::Mesh() : 
    m_meshWidth(0),
    m_meshLength(0),
    m_meshHeight(0),
    m_heightMap(0),
    Model()
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

    // Generate a Height Map
    GenerateHeightMap();

	// Set the number of vertices and indices.
	m_vertexCount = (m_meshWidth - 1) * (m_meshLength - 1) * 12;
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

	// Release the height map data.
	ShutdownHeightMap();

    // Parent class shutdown
    Model::Shutdown();

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
	int index1, index2, index3, index4;

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
            index1 = (m_meshWidth * j) + i;          // Bottom left.
			index2 = (m_meshWidth * j) + (i+1);      // Bottom right.
			index3 = (m_meshWidth * (j+1)) + i;      // Upper left.
			index4 = (m_meshWidth * (j+1)) + (i+1);  // Upper right.

			// Upper left.
			vertices[index].position = D3DXVECTOR3(m_heightMap[index3].x, m_heightMap[index3].y, m_heightMap[index3].z);
			vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			indices[index] = index;
			index++;

			// Upper right.
			vertices[index].position = D3DXVECTOR3(m_heightMap[index4].x, m_heightMap[index4].y, m_heightMap[index4].z);
			vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			indices[index] = index;
			index++;

			// Upper right.
			vertices[index].position = D3DXVECTOR3(m_heightMap[index4].x, m_heightMap[index4].y, m_heightMap[index4].z);
			vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			indices[index] = index;
			index++;

			// Bottom left.
			vertices[index].position = D3DXVECTOR3(m_heightMap[index1].x, m_heightMap[index1].y, m_heightMap[index1].z);
			vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			indices[index] = index;
			index++;

			// Bottom left.
			vertices[index].position = D3DXVECTOR3(m_heightMap[index1].x, m_heightMap[index1].y, m_heightMap[index1].z);
			vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			indices[index] = index;
			index++;

			// Upper left.
			vertices[index].position = D3DXVECTOR3(m_heightMap[index3].x, m_heightMap[index3].y, m_heightMap[index3].z);
			vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			indices[index] = index;
			index++;

			// Bottom left.
			vertices[index].position = D3DXVECTOR3(m_heightMap[index1].x, m_heightMap[index1].y, m_heightMap[index1].z);
			vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			indices[index] = index;
			index++;

			// Upper right.
			vertices[index].position = D3DXVECTOR3(m_heightMap[index4].x, m_heightMap[index4].y, m_heightMap[index4].z);
			vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			indices[index] = index;
			index++;

			// Upper right.
			vertices[index].position = D3DXVECTOR3(m_heightMap[index4].x, m_heightMap[index4].y, m_heightMap[index4].z);
			vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			indices[index] = index;
			index++;

			// Bottom right.
			vertices[index].position = D3DXVECTOR3(m_heightMap[index2].x, m_heightMap[index2].y, m_heightMap[index2].z);
			vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			indices[index] = index;
			index++;

			// Bottom right.
			vertices[index].position = D3DXVECTOR3(m_heightMap[index2].x, m_heightMap[index2].y, m_heightMap[index2].z);
			vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			indices[index] = index;
			index++;

			// Bottom left.
			vertices[index].position = D3DXVECTOR3(m_heightMap[index1].x, m_heightMap[index1].y, m_heightMap[index1].z);
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


// |----------------------------------------------------------------------------|
// |						  GenerateHeightMap									|
// |----------------------------------------------------------------------------|
void Mesh::GenerateHeightMap()
{
    if (!m_meshWidth || !m_meshLength)
        return;

    InitializeHeightMap();
    RandomizeHeightMap();
    //NormalizeHeightMap();
}


// |----------------------------------------------------------------------------|
// |						 InitializeHeightMap								|
// |----------------------------------------------------------------------------|
void Mesh::InitializeHeightMap()
{
	int i, j, index;
    // Initialize starting position
    float startX = 0.0f - m_meshWidth/2;
    float startZ = 0.0f - m_meshLength/2;

    m_heightMap = new Coord[m_meshWidth*m_meshLength];
    
	// Read the image data into the height map.
	for(j=0; j<m_meshLength; j++)
	{
		for(i=0; i<m_meshWidth; i++)
		{
			index = (m_meshWidth * j) + i;

			m_heightMap[index].x = startX+(float)i;
			m_heightMap[index].y = (float)0;
			m_heightMap[index].z = startZ+(float)j;
		}
	}
}


// |----------------------------------------------------------------------------|
// |						  RandomizeHeightMap								|
// |----------------------------------------------------------------------------|
void Mesh::RandomizeHeightMap()
{
	int i, j, index;

    // Initialize randomizer
    srand (time(0));
    
	// Read the image data into the height map.
	for(j=0; j<m_meshLength; j++)
	{
		for(i=0; i<m_meshWidth; i++)
		{
			index = (m_meshWidth * j) + i;

			m_heightMap[index].y = (((float)rand()-(float)rand())/RAND_MAX) * m_meshHeight;
		}
	}
}


// |----------------------------------------------------------------------------|
// |						  NormalizeHeightMap								|
// |----------------------------------------------------------------------------|
void Mesh::NormalizeHeightMap()
{
	int i, j, index;
    
	// Read the image data into the height map.
	for(j=0; j<m_meshLength; j++)
	{
		for(i=0; i<m_meshWidth; i++)
		{
			m_heightMap[(m_meshWidth * j) + i].y /= MAXINT;
		}
	}
}


// |----------------------------------------------------------------------------|
// |						   ShutdownHeightMap								|
// |----------------------------------------------------------------------------|
void Mesh::ShutdownHeightMap()
{
	if(m_heightMap)
	{
		delete [] m_heightMap;
		m_heightMap = 0;
	}

	return;
}