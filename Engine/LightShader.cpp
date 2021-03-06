// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// LightShader
//      Wraps and interacts with vertex and pixel shader.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "LightShader.h"
#include "Graphic.h"


// |----------------------------------------------------------------------------|
// |                                Initialize                                  |
// |----------------------------------------------------------------------------|
bool LightShader::Initialize()
{
    // Set up the shader files
    return Shader::Initialize("LightVertexShader", "LightPixelShader", L"shaders/light.vs", L"shaders/light.ps");

    // Initialize vertex shader buffers
    if (! InitializeVertexShaderBuffers(D3DManager::GetRef()->GetDevice()) )
        return false;

}


// |----------------------------------------------------------------------------|
// |                           InitializeSamplerState                           |
// |----------------------------------------------------------------------------|
bool LightShader::InitializeSamplerState(ID3D11Device* device)
{	
    HRESULT result;
    D3D11_SAMPLER_DESC samplerDesc;
    
    // Create a texture sampler state description.
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	result = device->CreateSamplerState(&samplerDesc, &m_sampleState);
	if(FAILED(result))
	{
        DebugPopup(L"Could not CreateSamplerState from device.");
		return false;
	}

	return true;
}


// |----------------------------------------------------------------------------|
// |                                RenderShader                                |
// |----------------------------------------------------------------------------|
void LightShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
    // Set the vertex input layout.
    deviceContext->IASetInputLayout(m_layout);

    // Set the vertex and pixel shaders that will be used to render this triangle.
    deviceContext->VSSetShader(m_vertexShader, NULL, 0);
    deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	// Set the sampler state in the pixel shader.
	deviceContext->PSSetSamplers(0, 1, &m_sampleState);

    // Render the model.
    deviceContext->DrawIndexed(indexCount, 0, 0);

    return;
}


// |----------------------------------------------------------------------------|
// |                               SetVSBuffer                                  |
// |----------------------------------------------------------------------------|
bool LightShader::SetVSBuffer(ID3D11DeviceContext* deviceContext, 
        D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
        D3DXMATRIX projectionMatrix, Graphic* graphic)
{
	DebugLog ("LightShader::SetVSBuffer() called.", DB_GRAPHICS, 10);
    HRESULT result;
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    unsigned int bufferNumber;
    VSBufferType* t_vsbuffer;

    // Transpose the matrices to prepare them for the shader.
    D3DXMatrixTranspose(&worldMatrix, &worldMatrix);
    D3DXMatrixTranspose(&viewMatrix, &viewMatrix);
    D3DXMatrixTranspose(&projectionMatrix, &projectionMatrix);

    // Lock the matrix constant buffer so it can be written to.
    result = deviceContext->Map(m_vsBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    if(FAILED(result))
    {
        return false;
    }

    // Get a pointer to the data in the constant buffer.
    t_vsbuffer = (VSBufferType*)mappedResource.pData;

    // Copy the matrices into the constant buffer.
    Camera* camera = GraphicsManager::GetRef()->GetCamera();
    t_vsbuffer->world = worldMatrix;
    t_vsbuffer->view = viewMatrix;
    t_vsbuffer->projection = projectionMatrix;
    t_vsbuffer->cameraPosition = D3DXVECTOR3(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);
    
    // Point Lights
    std::list<PointLight*> pointLights = LightManager::GetRef()->GetLights(graphic->GetPosition(),NUM_LIGHTS);
    // Initialize lights
    for (int i=0; i < NUM_LIGHTS; ++i)
    {
        t_vsbuffer->pointLightPosition[i] = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
    }
    // Copy lights from list
    int i= 0;
    for (std::list<PointLight*>::iterator it=pointLights.begin(); it != pointLights.end(); ++it)
    {
        t_vsbuffer->pointLightPosition[i] = (*it)->position;
        ++i;
    }

    // Fog
    t_vsbuffer->fogDensity = LightManager::GetRef()->GetFogDensity();

    // Unlock the constant buffer.
    deviceContext->Unmap(m_vsBuffer, 0);

    // Set the position of the constant buffer in the vertex shader.
    bufferNumber = 0;

    // Now set the constant buffer in the vertex shader with the updated values.
    deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_vsBuffer);

    return true;
}

// |----------------------------------------------------------------------------|
// |                               SetPSBuffer                                  |
// |----------------------------------------------------------------------------|
bool LightShader::SetPSBuffer(ID3D11DeviceContext* deviceContext,
        Graphic* graphic)
{
	DebugLog ("LightShader::SetPSBuffer() called.", DB_GRAPHICS, 10);

    HRESULT result;
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    unsigned int bufferNumber;
    PSBufferType* t_psbuffer;

    // Lock the light constant buffer so it can be written to.
	result = deviceContext->Map(m_psBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	t_psbuffer = (PSBufferType*)mappedResource.pData;

	// Copy the color and light into the constant buffer.
    t_psbuffer->tint = D3DXVECTOR4(graphic->GetTintR(), graphic->GetTintG(), graphic->GetTintB(), graphic->GetAlpha());
    t_psbuffer->directionalLightColor = LightManager::GetRef()->GetDiffuseColor();
    t_psbuffer->directionalLightDirection = LightManager::GetRef()->GetDiffuseDirection();
    t_psbuffer->ambientColor = LightManager::GetRef()->GetAmbient();
    if (graphic->GetReflectiveness())
        t_psbuffer->specularPower = (1-graphic->GetReflectiveness())*100.0f;
    else
        t_psbuffer->specularPower = 100000.0f;
    t_psbuffer->specularColor = D3DXVECTOR4(
        Clamp(t_psbuffer->directionalLightColor.x+0.5,0.0f,1.0f),
        Clamp(t_psbuffer->directionalLightColor.y+0.5,0.0f,1.0f),
        Clamp(t_psbuffer->directionalLightColor.z+0.5,0.0f,1.0f),
        Clamp(t_psbuffer->directionalLightColor.w+0.5,0.0f,1.0f) );

    // Point Lights
    std::list<PointLight*> pointLights = LightManager::GetRef()->GetLights(graphic->GetPosition(),NUM_LIGHTS);
    // Initialize lights
    for (int i=0; i < NUM_LIGHTS; ++i)
    {
        t_psbuffer->pointLightColor[i] = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
    }
    // Copy lights from list
    int i= 0;
    for (std::list<PointLight*>::iterator it=pointLights.begin(); it != pointLights.end(); ++it)
    {
        t_psbuffer->pointLightColor[i] = (*it)->color;
        ++i;
    }
    
    // Fog Color
    t_psbuffer->fogColor = LightManager::GetRef()->GetFogColor();

 
	// Unlock the constant buffer.
	deviceContext->Unmap(m_psBuffer, 0);

	// Set the position of the light constant buffer in the pixel shader.
	bufferNumber = 0;

	// Send the color buffer to the pixel shader.
	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_psBuffer);

	// Send the texture sampler to the pixel shader.
    ID3D11ShaderResourceView* texture = graphic->GetTexture()->GetShaderResourceView();
	deviceContext->PSSetShaderResources(0, 1, &texture);

    return true;
}