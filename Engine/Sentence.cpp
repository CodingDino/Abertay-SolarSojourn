// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Sentence
//      Contains model information for set of text



// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "Sentence.h"


// |----------------------------------------------------------------------------|
// |						   Default Constructor								|
// |----------------------------------------------------------------------------|
Sentence::Sentence() : 
	m_maxLength(0),
	Model()
{
}

// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
Sentence::Sentence(const Sentence& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
Sentence::~Sentence()
{
}


// |----------------------------------------------------------------------------|
// |						      Initialize									|
// |----------------------------------------------------------------------------|
bool Sentence::Initialize(int maxLength)
{
	DebugLog ("Sentence::Initialize() called.", DB_GRAPHICS, 1);
	bool result;

	// Set the number of vertices and indices.
	m_maxLength = maxLength;
	m_vertexCount = 6 * maxLength;
	m_indexCount = m_vertexCount;

	// Set buffer flags
	m_bufferUsage = D3D11_USAGE_DYNAMIC;
	m_bufferCPUAccess = D3D11_CPU_ACCESS_WRITE;
	
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
bool Sentence::PopulateBuffers(VertexType*& vertices, unsigned long*& indices)
{
	DebugLog ("Sentence::PopulateBuffers() called.", DB_GRAPHICS, 10);

	// Initialize index array
	for(int i=0; i<m_indexCount; i++)
	{
		indices[i] = i;
	}

	// Initialize vertex array
	for(int i=0; i<m_vertexCount; i++)
	{
		vertices[i].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertices[i].texture = D3DXVECTOR2(0.0f, 0.0f);
	}

	return true;
}


// |----------------------------------------------------------------------------|
// |						    UpdateBuffers									|
// |----------------------------------------------------------------------------|
bool Sentence::UpdateBuffers(char* string, Font* font)
{
	DebugLog ("Sentence::UpdateBuffers() called.", DB_GRAPHICS, 2);

	int numLetters;
	VertexType* vertices;
	unsigned long* indices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;
	float drawX, drawY;
	HRESULT result;

	// Get the number of letters in the sentence.
	numLetters = (int)strlen(string);
	if(numLetters > m_maxLength)
	{
		return false;
	}

	// Initialize the index and vertex arrays.
	indices = new unsigned long[m_indexCount];
	vertices = new VertexType[m_vertexCount];
	PopulateBuffers(vertices,indices);
	
	// Calculate the X and Y pixel position on the screen to start drawing to.
	drawX = (SCREEN_WIDTH / 2.0f) * -1.0f;
	drawY = SCREEN_HEIGHT / 2.0f;
	
	// Use the font class to build the vertex array from the sentence text and sentence draw location.
	font->BuildVertexArray(vertices, string, drawX, drawY);
	
	// Lock the vertex buffer so it can be written to.
	result = D3DManager::GetRef()->GetDeviceContext()->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the vertex buffer.
	verticesPtr = (VertexType*)mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * m_vertexCount));

	// Unlock the vertex buffer.
	D3DManager::GetRef()->GetDeviceContext()->Unmap(m_vertexBuffer, 0);

	// Release the vertex array as it is no longer needed.
	delete [] vertices;
	vertices = 0;

	return true;
}