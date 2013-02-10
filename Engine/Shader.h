// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Shader
//      Abstract class for shaders. Wraps and interacts with vertex and pixel 
//      shaders.
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
#include "Util.h"
using namespace std;


// |----------------------------------------------------------------------------|
// |                              Class: Shader                                 |
// |----------------------------------------------------------------------------|
class Shader
{
protected:

    //|-------------------------------Type Definitions--------------------------|

    struct MatrixBufferType
    {
        D3DXMATRIX world;
        D3DXMATRIX view;
        D3DXMATRIX projection;
    };

public:

    //|-------------------------------Public Functions--------------------------|
    
    // Constructors and Destructors
    Shader();
    Shader(const char*, const char*, WCHAR*, WCHAR*);
    
    // Initializes the shaders
    bool Initialize(ID3D11Device*);

    // Performs shutdown, deallocation, and cleanup for shaders
    void Shutdown();

    // Renders the provided matrices to the DX device
    bool Render(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);
    
protected:

    //|-----------------------------Protected Functions------------------------|

    // Initializes shaders
    bool InitializeShader(ID3D11Device*, WCHAR*, WCHAR*);
    
    // Performs shutdown, deallocation, and cleanup for shaders
    void ShutdownShader();

    // Relays messages from shaders
    void OutputShaderErrorMessage(ID3D10Blob*, WCHAR*);

    // Passes information to shaders
    bool SetShaderParameters(ID3D11DeviceContext* deviceContext, 
        D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix);

    // Renders shader to device
    void RenderShader(ID3D11DeviceContext*, int);

protected:

    //|---------------------------Protected Data Members-----------------------|

    // Shaders
    ID3D11VertexShader* m_vertexShader;
    ID3D11PixelShader* m_pixelShader;

    // Shader names
    const char* m_vertexShaderName;
    const char* m_pixelShaderName;

    // Shader files
    WCHAR* m_vertexShaderFile;
    WCHAR* m_pixelShaderFile;

    // Layout
    ID3D11InputLayout* m_layout;

    // Buffers
    ID3D11Buffer* m_matrixBuffer;
};