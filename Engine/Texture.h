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


// |----------------------------------------------------------------------------|
// |                              Class: Texture                                |
// |----------------------------------------------------------------------------|
class Texture
{
public:

    //|-------------------------------Public Functions--------------------------|

    // Constructors and Destructors
    Texture();

    // Initiallizes a texture
    bool Initialize(ID3D11Device* device, WCHAR* filename);

    // Releases texture data
    void Shutdown();

    // Getter functions
    ID3D11ShaderResourceView* GetResource();
    int GetWidth() { return m_width; }
    int GetHeight() { return m_height; }

protected:

    //|----------------------------Protected Data Members-----------------------|

    // Texture
    ID3D11ShaderResourceView* m_texture;

    // Size
    int m_width, m_height;

};