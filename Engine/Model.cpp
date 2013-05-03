// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Model
//      Contains model data.


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "Model.h"


// |----------------------------------------------------------------------------|
// |						   Default Constructor								|
// |----------------------------------------------------------------------------|
Model::Model() :
	m_vertexBuffer(0),
	m_indexBuffer(0),
	m_model(0),
	m_bufferUsage(D3D11_USAGE_DEFAULT),
	m_bufferCPUAccess(0)
{
}


// |----------------------------------------------------------------------------|
// |						      Initialize									|
// |----------------------------------------------------------------------------|
bool Model::Initialize(const char* modelFilename)
{
	DebugLog ("Model::Initialize() called.", DB_GRAPHICS, 1);
	bool result;

	// Set buffer flags
	m_bufferUsage = D3D11_USAGE_DEFAULT;
	m_bufferCPUAccess = 0;

	// Load in the model data,
	result = LoadModel(modelFilename);
	if(!result)
	{
        DebugLog("Could not load model file.");
		return false;
	}

	// Initialize the vertex and index buffers.
	result = InitializeBuffers();
	if(!result)
	{
		return false;
	}

	return true;
}


// |----------------------------------------------------------------------------|
// |						      Shutdown										|
// |----------------------------------------------------------------------------|
void Model::Shutdown()
{
	DebugLog ("Model::Shutdown() called.", DB_GRAPHICS, 1);
	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	// Release the model data.
	ReleaseModel();

	return;
}


// |----------------------------------------------------------------------------|
// |						       Render										|
// |----------------------------------------------------------------------------|
void Model::Render()
{
	DebugLog ("Model::Render() called.", DB_GRAPHICS, 10);
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers();

	return;
}


// |----------------------------------------------------------------------------|
// |						    GetIndexCount									|
// |----------------------------------------------------------------------------|
int Model::GetIndexCount()
{
	DebugLog ("Model::GetIndexCount() called.", DB_GRAPHICS, 10);
	return m_indexCount;
}


// |----------------------------------------------------------------------------|
// |						  InitializeBuffers									|
// |----------------------------------------------------------------------------|
bool Model::InitializeBuffers()
{
	DebugLog ("Model::InitializeBuffers() called.", DB_GRAPHICS, 1);
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}

	// Populate vertex data
	PopulateBuffers(vertices,indices);

	// Set up the description of the static vertex buffer.
    vertexBufferDesc.Usage = m_bufferUsage;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = m_bufferCPUAccess;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
    result = D3DManager::GetRef()->GetDevice()->
		CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
    indexBufferDesc.Usage = m_bufferUsage;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = m_bufferCPUAccess;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = D3DManager::GetRef()->GetDevice()->
		CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}


// |----------------------------------------------------------------------------|
// |						  PopulateBuffers									|
// |----------------------------------------------------------------------------|
bool Model::PopulateBuffers(VertexType*& vertices, unsigned long*& indices)
{
	DebugLog ("Model::PopulateBuffers() called.", DB_GRAPHICS, 10);

	// Load the vertex array and index array with data.
	for(int i=0; i<m_vertexCount; i++)
	{
		vertices[i].position = D3DXVECTOR3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = D3DXVECTOR2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = D3DXVECTOR3(m_model[i].nx, m_model[i].ny, m_model[i].nz);

		indices[i] = i;
	}

	return true;
}


// |----------------------------------------------------------------------------|
// |						   ShutdownBuffers									|
// |----------------------------------------------------------------------------|
void Model::ShutdownBuffers()
{
	DebugLog ("Model::ShutdownBuffers() called.", DB_GRAPHICS, 1);

	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


// |----------------------------------------------------------------------------|
// |						   RenderBuffers									|
// |----------------------------------------------------------------------------|
void Model::RenderBuffers()
{
	DebugLog ("Model::RenderBuffers() called.", DB_GRAPHICS, 10);

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
		->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}


// |----------------------------------------------------------------------------|
// |				   		    LoadModel										|
// |----------------------------------------------------------------------------|
bool Model::LoadModel(const char* filename)
{
	DebugLog ("Model::LoadModel() called.", DB_GRAPHICS, 1);

	ifstream fin;
	char input;
	int i;


	// Open the model file.
	fin.open(filename);
	
	// If it could not open the file then exit.
	if(fin.fail())
	{
		return false;
	}

	// Read up to the value of vertex count.
	fin.get(input);
	while(input != ':')
	{
		fin.get(input);
	}

	// Read in the vertex count.
	fin >> m_vertexCount;

	// Set the number of indices to be the same as the vertex count.
	m_indexCount = m_vertexCount;

	// Create the model using the vertex count that was read in.
	m_model = new ModelType[m_vertexCount];
	if(!m_model)
	{
		return false;
	}

	// Read up to the beginning of the data.
	fin.get(input);
	while(input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	// Read in the vertex data.
	for(i=0; i<m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	// Close the model file.
	fin.close();

	return true;
}


// |----------------------------------------------------------------------------|
// |				   		   ReleaseModel										|
// |----------------------------------------------------------------------------|
void Model::ReleaseModel()
{
	DebugLog ("Model::ReleaseModel() called.", DB_GRAPHICS, 1);

	if(m_model)
	{
		delete [] m_model;
		m_model = 0;
	}

	return;
}
