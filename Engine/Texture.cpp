// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Texture
//      Holds one texture


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "Texture.h"


// |----------------------------------------------------------------------------|
// |						   Default Constructor								|
// |----------------------------------------------------------------------------|
Texture::Texture() :
	m_shaderResourceView(0),
    m_renderTargetTexture(0),
    m_renderTargetView(0),
    m_width(0),
    m_height(0)
{
}

// |----------------------------------------------------------------------------|
// |						      Initialize									|
// |----------------------------------------------------------------------------|
bool Texture::Initialize(WCHAR* filename)
{
	DebugLog ("Texture::Initialize() called.", DB_GRAPHICS, 1);
	HRESULT result;

    // Get device
    ID3D11Device* device = D3DManager::GetRef()->GetDevice();

    // Get original image dimmensions
    D3DX11_IMAGE_INFO info;
    D3DX11GetImageInfoFromFile(filename, 0, &info, &result);
    m_width = info.Width;
    m_height = info.Height;

	// Load the texture in.
	result = D3DX11CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &m_shaderResourceView, NULL);
	if(FAILED(result))
	{
        DebugPopup(L"Could not find texture file.");
		return false;
	}

	return true;
}



// |----------------------------------------------------------------------------|
// |						      Initialize									|
// |----------------------------------------------------------------------------|
bool Texture::Initialize(int textureWidth, int textureHeight)
{
	DebugLog ("Texture::Initialize() called.", DB_GRAPHICS, 1);

	D3D11_TEXTURE2D_DESC textureDesc;
	HRESULT result;
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

    // Get device
    ID3D11Device* device = D3DManager::GetRef()->GetDevice();

    // Set sizes
    m_width = textureWidth;
    m_height = textureHeight;
    
	// Initialize the render target texture description.
	ZeroMemory(&textureDesc, sizeof(textureDesc));

	// Setup the render target texture description.
	textureDesc.Width = textureWidth;
	textureDesc.Height = textureHeight;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	// Create the render target texture.
	result = device->CreateTexture2D(&textureDesc, NULL, &m_renderTargetTexture);
	if(FAILED(result))
	{
		return false;
	}

	// Setup the description of the render target view.
	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	// Create the render target view.
	result = device->CreateRenderTargetView(m_renderTargetTexture, &renderTargetViewDesc, &m_renderTargetView);
	if(FAILED(result))
	{
		return false;
	}

	// Setup the description of the shader resource view.
	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	// Create the shader resource view.
	result = device->CreateShaderResourceView(m_renderTargetTexture, &shaderResourceViewDesc, &m_shaderResourceView);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}
// |----------------------------------------------------------------------------|
// |						      Shutdown										|
// |----------------------------------------------------------------------------|
void Texture::Shutdown()
{
	if(m_shaderResourceView)
	{
		m_shaderResourceView->Release();
		m_shaderResourceView = 0;
	}

	if(m_renderTargetView)
	{
		m_renderTargetView->Release();
		m_renderTargetView = 0;
	}

	if(m_renderTargetTexture)
	{
		m_renderTargetTexture->Release();
		m_renderTargetTexture = 0;
	}

	return;
}


// |----------------------------------------------------------------------------|
// |						   SetAsRenderTarget								|
// |----------------------------------------------------------------------------|
void Texture::SetAsRenderTarget()
{
    ID3D11DeviceContext* deviceContext = D3DManager::GetRef()->GetDeviceContext();
    ID3D11DepthStencilView* depthStencilView = D3DManager::GetRef()->GetDepthStencilView();

	// Bind the render target view and depth stencil buffer to the output render pipeline.
	deviceContext->OMSetRenderTargets(1, &m_renderTargetView, depthStencilView);
	
	return;
}


// |----------------------------------------------------------------------------|
// |						   ClearRenderTarget								|
// |----------------------------------------------------------------------------|
void Texture::ClearRenderTarget(float r, float g, float b, float a)
{
    ID3D11DeviceContext* deviceContext = D3DManager::GetRef()->GetDeviceContext();
    ID3D11DepthStencilView* depthStencilView = D3DManager::GetRef()->GetDepthStencilView();

	// Setup the color to clear the buffer to.
	float color[4];
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;

	// Clear the back buffer.
	deviceContext->ClearRenderTargetView(m_renderTargetView, color);
    
	// Clear the depth buffer.
	deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	return;
}


// |----------------------------------------------------------------------------|
// |						     GetTexture										|
// |----------------------------------------------------------------------------|
ID3D11ShaderResourceView* Texture::GetShaderResourceView()
{
	return m_shaderResourceView;
}