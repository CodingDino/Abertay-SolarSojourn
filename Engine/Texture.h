// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Texture
//      Holds one texture
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <d3d11.h>
#include <d3dx11tex.h>
#include <D3dx9tex.h>
#include "Util.h"
#include "D3DManager.h"
#include "GraphicsManager.h"


// |----------------------------------------------------------------------------|
// |                              Class: Texture                                |
// |----------------------------------------------------------------------------|
class Texture
{
public:

    //|-------------------------------Public Functions--------------------------|

    // Constructors and Destructors
    Texture();

    // Initiallizes a texture to read from file
    bool Initialize(WCHAR* filename);

    // Initialize a texture to render from screen
    bool Initialize(int textureWidth = SCREEN_WIDTH, int textureHeight = SCREEN_HEIGHT);

    // Releases texture data
    void Shutdown();

    // Render to Texture functions
    void SetAsRenderTarget();
    void ClearRenderTarget(float r=0.0f, float g=0.0f, float b=0.0f, float a=1.0f);
    void SetWidth(int val) { m_width = val; }
    void SetHeight(int val) { m_height = val; }

    // Getter functions
    ID3D11ShaderResourceView* GetShaderResourceView();
    int GetWidth() { return m_width; }
    int GetHeight() { return m_height; }
	D3DXMATRIX GetProjectionMatrix() {return m_projectionMatrix;}
	D3DXMATRIX GetOrthoMatrix() {return m_orthoMatrix;}

protected:

    //|----------------------------Protected Data Members-----------------------|

    // Texture
    ID3D11ShaderResourceView* m_shaderResourceView;

    // Render to Texture data members
    ID3D11Texture2D* m_renderTargetTexture;
    ID3D11RenderTargetView* m_renderTargetView;

    // Size
    int m_width, m_height;

    // Viewport
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilView* m_depthStencilView;
	D3D11_VIEWPORT m_viewport;
	D3DXMATRIX m_projectionMatrix;
	D3DXMATRIX m_orthoMatrix;
};