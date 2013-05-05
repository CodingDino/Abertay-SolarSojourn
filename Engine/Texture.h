// Solar Exploration Sim
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

    // Getter functions
    ID3D11ShaderResourceView* GetShaderResourceView();
    int GetWidth() { return m_width; }
    int GetHeight() { return m_height; }

protected:

    //|----------------------------Protected Data Members-----------------------|

    // Texture
    ID3D11ShaderResourceView* m_shaderResourceView;

    // Render to Texture data members
    ID3D11Texture2D* m_renderTargetTexture;
    ID3D11RenderTargetView* m_renderTargetView;

    // Size
    int m_width, m_height;

};