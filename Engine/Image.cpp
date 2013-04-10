// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Image
//      Contains data for a single 2D image, including texture and rendering method.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Image.h"
#include "Shader.h"


// |----------------------------------------------------------------------------|
// |                           Default Constructor                              |
// |----------------------------------------------------------------------------|
Image::Image() :
    m_vertexBuffer(0),
    m_indexBuffer(0),
    m_vertexCount(0),
    m_indexCount(0),
    m_previousPosition(-1.0f,-1.0f,-1.0f),
    Graphic()
{
}


// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
Image::Image(const Image& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
Image::~Image()
{
}


// |----------------------------------------------------------------------------|
// |                              Initialize                                    |
// |----------------------------------------------------------------------------|
bool Image::Initialize()
{
    
	bool result;

    // Initialize parent class
    result =  Graphic::Initialize();
	if (!result)
		return false;

	// Initialize the vertex and index buffers
	result = InitializeBuffers(D3DManager::GetRef()->GetDevice());
	if (!result)
		return false;

	// Return success
	return true;
}


// |----------------------------------------------------------------------------|
// |                              Shutdown                                      |
// |----------------------------------------------------------------------------|
void Image::Shutdown()
{

	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

    return Graphic::Shutdown();
}


// |----------------------------------------------------------------------------|
// |                               Render                                       |
// |----------------------------------------------------------------------------|
void Image::Render()
{
	DebugLog ("Image::Render() called.", DB_GRAPHICS, 10);

    // Get correct shader to use from material
    Shader* shader = m_material->GetShader();

	// Re-build the dynamic vertex buffer for rendering to possibly a different location on the screen.
	UpdateBuffers(D3DManager::GetRef()->GetDeviceContext());

	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(D3DManager::GetRef()->GetDeviceContext());

    // Scale, Translate, and Rotate
    D3DXMATRIX worldMatrix = GraphicsManager::GetRef()->GetWorldMatrix();
    D3DXMATRIX scale, rotate, translate;
	D3DXMatrixScaling(&scale, m_scale.x, m_scale.y, 1.0f);
	D3DXMatrixRotationYawPitchRoll(&rotate, 0.0f, 0.0f, m_orientation.z);
    D3DXMatrixTranslation(&translate, 
        m_scale.x*m_texture->GetWidth()/2 - SCREEN_WIDTH/2 + m_position.x, 
        -1*m_scale.y*m_texture->GetHeight()/2 + SCREEN_HEIGHT/2 - m_position.y, 
        0.0f);
    worldMatrix = scale * rotate * translate;

    // Render using the shader and a self pointer.
    shader->Render(D3DManager::GetRef()->GetDeviceContext(),
        m_model->GetIndexCount(),
        worldMatrix,
        GraphicsManager::GetRef()->GetBaseViewMatrix(),
        GraphicsManager::GetRef()->GetOrthoMatrix(),
        this);

    return;
}


// |----------------------------------------------------------------------------|
// |						     InitializeBuffers								|
// |----------------------------------------------------------------------------|
/*InitializeBuffers is the function that is used to build the vertex and index 
buffer that will be used to draw the 2D image.*/
bool Image::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;
	
	/*We set the vertices to six since we are making a square out of two triangles, 
	so six points are needed. The indices will be the same.*/

	// Set the number of vertices in the vertex array.
	m_vertexCount = 6;

	// Set the number of indices in the index array.
	m_indexCount = m_vertexCount;

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

	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * m_vertexCount));

	// Load the index array with data.
	for(i=0; i<m_indexCount; i++)
	{
		indices[i] = i;
	}

	/*Here is the big change in comparison to the ModelClass. We are now creating 
	a dynamic vertex buffer so we can modify the data inside the vertex buffer each 
	frame if we need to. To make it dynamic we set Usage to D3D11_USAGE_DYNAMIC and 
	CPUAccessFlags to D3D11_CPU_ACCESS_WRITE in the description. */

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	/*We don't need to make the index buffer dynamic since the six indices will 
	always point to the same six vertices even though the coordinates of the 
	vertex may change. */

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
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
// |						      ShutdownBuffers								|
// |----------------------------------------------------------------------------|
/*ShutdownBuffers releases the vertex and index buffers. */
void Image::ShutdownBuffers()
{
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
// |						       UpdateBuffers								|
// |----------------------------------------------------------------------------|
/*The UpdateBuffers function is called each frame to update the contents of the 
dynamic vertex buffer to re-position the 2D bitmap image on the screen if need 
be. */
bool Image::UpdateBuffers(ID3D11DeviceContext* deviceContext)
{
	float left, right, top, bottom;
	VertexType* vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;
	HRESULT result;

	/*We check if the position to render this image has changed. If it hasn't 
	changed then we just exit since the vertex buffer doesn't need any changes 
	for this frame. This check can save us a lot of processing. */

	// If the position we are rendering this bitmap to has not changed then don't 
	// update the vertex buffer since it currently has the correct parameters.
	if(m_previousPosition == m_position)
	{
		return true;
	}

	/*If the position to render this image has changed then we record the new 
	location for the next time we come through this function. */

	// If it has changed then update the position it is being rendered to.
	m_previousPosition = m_position;

	/*The four sides of the image need to be calculated. See the diagram at the 
	top of the tutorial for a complete explaination. */

	// Calculate the screen coordinates of the left side of the bitmap.
	//left = (float)((SCREEN_WIDTH / 2) * -1) + m_position.x;
	left = -1* ((float)m_texture->GetWidth()) / 2.0f;

	// Calculate the screen coordinates of the right side of the bitmap.
    if (!m_texture) return false;
	//right = left + (float)m_texture->GetWidth()*m_scale.x;
	right = ((float)m_texture->GetWidth()) / 2.0f;

	// Calculate the screen coordinates of the top of the bitmap.
	//top = (float)(SCREEN_HEIGHT / 2) - m_position.y;
	top = ((float)m_texture->GetHeight()) / 2.0f;

	// Calculate the screen coordinates of the bottom of the bitmap.
	//bottom = top - (float)m_texture->GetHeight()*m_scale.y;
	bottom = -1* ((float)m_texture->GetHeight()) / 2.0f;

	/*Now that the coordinates are calculated create a temporary vertex 
	array and fill it with the new six vertex points. */

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Load the vertex array with data.
	// First triangle.
	vertices[0].position = D3DXVECTOR3(left, top, 0.0f);  // Top left.
	vertices[0].texture = D3DXVECTOR2(0.0f, 0.0f);

	vertices[1].position = D3DXVECTOR3(right, bottom, 0.0f);  // Bottom right.
	vertices[1].texture = D3DXVECTOR2(1.0f, 1.0f);

	vertices[2].position = D3DXVECTOR3(left, bottom, 0.0f);  // Bottom left.
	vertices[2].texture = D3DXVECTOR2(0.0f, 1.0f);

	// Second triangle.
	vertices[3].position = D3DXVECTOR3(left, top, 0.0f);  // Top left.
	vertices[3].texture = D3DXVECTOR2(0.0f, 0.0f);

	vertices[4].position = D3DXVECTOR3(right, top, 0.0f);  // Top right.
	vertices[4].texture = D3DXVECTOR2(1.0f, 0.0f);

	vertices[5].position = D3DXVECTOR3(right, bottom, 0.0f);  // Bottom right.
	vertices[5].texture = D3DXVECTOR2(1.0f, 1.0f);

	/*Now copy the contents of the vertex array into the vertex buffer using the 
	Map and memcpy functions. */

	// Lock the vertex buffer so it can be written to.
	result = deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the vertex buffer.
	verticesPtr = (VertexType*)mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * m_vertexCount));

	// Unlock the vertex buffer.
	deviceContext->Unmap(m_vertexBuffer, 0);

	// Release the vertex array as it is no longer needed.
	delete [] vertices;
	vertices = 0;

	return true;
}


// |----------------------------------------------------------------------------|
// |							 RenderBuffers									|
// |----------------------------------------------------------------------------|
/*The RenderBuffers function sets up the vertex and index buffers on the gpu to 
be drawn by the shader.*/
void Image::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

