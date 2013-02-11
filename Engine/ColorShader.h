// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// ColorShader
//      Wraps and interacts with vertex and pixel shader.
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Shader.h"


// |----------------------------------------------------------------------------|
// |                            Class: SystemManager                            |
// |----------------------------------------------------------------------------|
class ColorShader: public Shader
{
protected:

    //|-------------------------------Type Definitions--------------------------|
    struct VSBufferType
    {
        D3DXMATRIX world;
        D3DXMATRIX view;
        D3DXMATRIX projection;
    };

    struct PSBufferType
    {
		D3DXVECTOR4 color;
    };

public:

    //|-------------------------------Public Functions--------------------------|
    
    // Constructors and Destructors
    ColorShader();

    // Renders the provided matrices to the DX device
    virtual bool Render(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, 
        D3DXMATRIX, D3DXVECTOR4);
    
protected:

    //|-----------------------------Protected Functions------------------------|

    // Passes information to shaders
    virtual bool SetShaderParameters(ID3D11DeviceContext* deviceContext, 
        D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix,
        D3DXVECTOR4 color);
    virtual bool SetVSBuffer(ID3D11DeviceContext* deviceContext, 
        D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix);
    virtual bool SetPSBuffer(ID3D11DeviceContext* deviceContext, 
        D3DXVECTOR4 color);

};