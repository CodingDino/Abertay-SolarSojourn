// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// GlowShader
//      Wraps and interacts with vertex and pixel shader.
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Shader.h"

// |----------------------------------------------------------------------------|
// |                            Class: GlowShader                               |
// |----------------------------------------------------------------------------|
class GlowShader: public Shader
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
		float glowStrength;
		D3DXVECTOR3 padding;
    };

public:

    //|-------------------------------Public Functions--------------------------|
    
    // Constructors and Destructors
    GlowShader() : 
        m_sampleState(0),
        m_glowBuffer(0) 
    {}
    
    // Initialization and shutdown
    virtual bool Initialize();
    
protected:

    //|-----------------------------Protected Functions------------------------|
    
    // Initialize the sampler state for use in texture sampling
    virtual bool InitializeSamplerState(ID3D11Device* device);

    // Passes information to shaders
    virtual bool SetVSBuffer(ID3D11DeviceContext* deviceContext, 
        D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix,
        Graphic* graphic);
    virtual bool SetPSBuffer(ID3D11DeviceContext* deviceContext,
        Graphic* graphic);

    // Renders shader to device
    virtual void RenderShader(ID3D11DeviceContext*, int);

    //|---------------------------Protected Data Members-----------------------|
    

	// Sampler state
	ID3D11SamplerState* m_sampleState;
    
    // Extra buffer for the glow texture
	ID3D11Buffer* m_glowBuffer;

};