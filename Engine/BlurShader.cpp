// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// HorizontalBlurShader
//      Wraps and interacts with vertex and pixel shader.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "BlurShader.h"
#include "Graphic.h"


// |----------------------------------------------------------------------------|
// |                           Default Constructor                              |
// |----------------------------------------------------------------------------|
bool BlurShader::Initialize()
{
    // Set up the shader files
    return Shader::Initialize("BlurVertexShader", "BlurPixelShader", L"shaders/blur.vs", L"shaders/blur.ps");

    // Initialize vertex shader buffers
    if (! InitializeVertexShaderBuffers(D3DManager::GetRef()->GetDevice()) )
        return false;

}


// |----------------------------------------------------------------------------|
// |                           InitializeSamplerState                           |
// |----------------------------------------------------------------------------|
bool BlurShader::InitializeSamplerState(ID3D11Device* device)
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
void BlurShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
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
bool BlurShader::SetVSBuffer(ID3D11DeviceContext* deviceContext, 
        D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
        D3DXMATRIX projectionMatrix, Graphic* graphic)
{
	DebugLog ("BlurShader::SetVSBuffer() called.", DB_GRAPHICS, 10);
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
    t_vsbuffer->world = worldMatrix;
    t_vsbuffer->view = viewMatrix;
    t_vsbuffer->projection = projectionMatrix;
	t_vsbuffer->horizontal = graphic->GetReBlur();
    if(t_vsbuffer->horizontal)
	    t_vsbuffer->texelScale = graphic->GetTexture()->GetWidth(); 
    else
	    t_vsbuffer->texelScale = graphic->GetTexture()->GetHeight(); 
    t_vsbuffer->padding = D3DXVECTOR2(0.0f, 0.0f);

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
bool BlurShader::SetPSBuffer(ID3D11DeviceContext* deviceContext,
        Graphic* graphic)
{
	DebugLog ("BlurShader::SetPSBuffer() called.", DB_GRAPHICS, 10);

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

	// Copy the color into the constant buffer.
    t_psbuffer->padding = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
        
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