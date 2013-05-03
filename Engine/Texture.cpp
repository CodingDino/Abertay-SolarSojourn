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
	m_texture(0),
    m_width(0),
    m_height(0)
{
}

// |----------------------------------------------------------------------------|
// |						      Initialize									|
// |----------------------------------------------------------------------------|
bool Texture::Initialize(ID3D11Device* device, WCHAR* filename)
{
	DebugLog ("Texture::Initialize() called.", DB_GRAPHICS, 1);
	HRESULT result;

    // Get original image dimmensions
    D3DX11_IMAGE_INFO info;
    D3DX11GetImageInfoFromFile(filename, 0, &info, &result);
    m_width = info.Width;
    m_height = info.Height;

	// Load the texture in.
	result = D3DX11CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &m_texture, NULL);
	if(FAILED(result))
	{
        DebugPopup(L"Could not find texture file.");
		return false;
	}

	return true;
}


// |----------------------------------------------------------------------------|
// |						      Shutdown										|
// |----------------------------------------------------------------------------|
void Texture::Shutdown()
{
	// Release the texture resource.
	if(m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}

	return;
}


// |----------------------------------------------------------------------------|
// |						     GetTexture										|
// |----------------------------------------------------------------------------|
ID3D11ShaderResourceView* Texture::GetResource()
{
	return m_texture;
}