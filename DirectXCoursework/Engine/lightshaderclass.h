// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// LightShaderClass
//		Wraps and interacts with the shaders (vertex and pixel shaders)
#pragma once


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;


// |----------------------------------------------------------------------------|
// |						Class: LightShaderClass								|
// |----------------------------------------------------------------------------|
class LightShaderClass
{
private:

	//|-----------------------------Private Data Types--------------------------|

	// Wraps the world, view, and projection matrices to send to vertex shader
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	// Wraps the camera information to send to vertex shader
	struct CameraBufferType
	{
		D3DXVECTOR3 cameraPosition;
		float padding;
	};

	struct LightPositionBufferType
	{
		D3DXVECTOR4 lightPosition;
	};

	// Wraps lighting information to send to pixel shader
	struct LightBufferType
	{
		D3DXVECTOR4 ambientColor;
		D3DXVECTOR4 diffuseColor;
		//D3DXVECTOR3 lightDirection;
		float specularPower;
		D3DXVECTOR4 specularColor;
		D3DXVECTOR3 padding;
	};

public:

	//|-------------------------------Public Functions--------------------------|
	
	// Constructors and Destructors
	LightShaderClass();
	LightShaderClass(const LightShaderClass&);
	~LightShaderClass();
	
	// Initializes the shaders
	bool Initialize(ID3D11Device* device, HWND hwnd);
	
	// Performs shutdown, deallocation, and cleanup for shaders
	void Shutdown();

	// Renders the provided matrices to the DX device
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, 
		D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, 
		D3DXVECTOR4 lightPosition, D3DXVECTOR4 ambientColor, D3DXVECTOR4 diffuseColor, 
		D3DXVECTOR3 cameraPosition, D3DXVECTOR4 specularColor, float specularPower, 
		ID3D11ShaderResourceView* texture);
private:

	//|-------------------------------Private Functions-------------------------|

	// Initializes shaders
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	
	// Performs shutdown, deallocation, and cleanup for shaders
	void ShutdownShader();

	// Relays messages from shaders
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	// Passes information to shaders
	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, 
		D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, 
		D3DXVECTOR4 lightPosition, D3DXVECTOR4 ambientColor,D3DXVECTOR4 diffuseColor, 
		D3DXVECTOR3 cameraPosition, D3DXVECTOR4 specularColor, float specularPower, 
		ID3D11ShaderResourceView* texture);

	// Renders shader to device
	void RenderShader(ID3D11DeviceContext*, int);

private:

	//|-----------------------------Private Data Members------------------------|

	// Shaders
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;

	// Layout
	ID3D11InputLayout* m_layout;

	// Sampler state
	ID3D11SamplerState* m_sampleState;

	// Buffers
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_lightBuffer;
	ID3D11Buffer* m_cameraBuffer;
	ID3D11Buffer* m_lightPositionBuffer;
};