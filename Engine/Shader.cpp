// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Shader
//      Abstract class for shaders. Wraps and interacts with vertex and pixel 
//      shaders.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Shader.h"
#include "Graphic.h"


// |----------------------------------------------------------------------------|
// |                           Default Constructor                              |
// |----------------------------------------------------------------------------|
Shader::Shader() :
    m_vertexShader(0),
    m_pixelShader(0),
    m_layout(0),
    m_vsBuffer(0),
    m_psBuffer(0),
    m_vertexShaderName("VertexShader"),
    m_pixelShaderName("PixelShader"),
    m_vertexShaderFile(L"../Engine/shader.vs"),
    m_pixelShaderFile(L"../Engine/shader.ps")
{
}


// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
Shader::Shader(const Shader& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
Shader::~Shader()
{
}


// |----------------------------------------------------------------------------|
// |                              Initialize                                    |
// |----------------------------------------------------------------------------|
bool Shader::Initialize(const char* vertexShaderName, const char* pixelShaderName,
    WCHAR* vertexShaderFile, WCHAR* pixelShaderFile)
{
    bool result;
    
    m_vertexShaderName = vertexShaderName;
    m_pixelShaderName = pixelShaderName;
    m_vertexShaderFile = vertexShaderFile;
    m_pixelShaderFile = pixelShaderFile;
    
    // Initialize the vertex and pixel shaders.
    result = InitializeShader(D3DManager::GetRef()->GetDevice(), m_vertexShaderFile, m_pixelShaderFile);
    if(!result)
    {
        DebugPopup(L"InitializeShader failed.");
        return false;
    }

    return true;
}


// |----------------------------------------------------------------------------|
// |                              Shutdown                                      |
// |----------------------------------------------------------------------------|
void Shader::Shutdown()
{
    // Shutdown the vertex and pixel shaders as well as the related objects.
    ShutdownShader();

    return;
}


// |----------------------------------------------------------------------------|
// |                             InitializeShader                               |
// |----------------------------------------------------------------------------|
bool Shader::InitializeShader(ID3D11Device* device,    WCHAR* vsFilename, 
    WCHAR* psFilename)
{
    HRESULT result;
    ID3D10Blob* errorMessage;
    ID3D10Blob* vertexShaderBuffer;
    ID3D10Blob* pixelShaderBuffer;

    // Initialize the pointers this function will use to null.
    errorMessage = 0;
    vertexShaderBuffer = 0;
    pixelShaderBuffer = 0;

    // Compile the vertex shader code.
    result = D3DX11CompileFromFile(vsFilename, NULL, NULL, m_vertexShaderName, 
        "vs_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vertexShaderBuffer, 
        &errorMessage, NULL);
    if(FAILED(result))
    {
        // If the shader failed to compile it should have writen something to the error message.
        if(errorMessage)
        {
            OutputShaderErrorMessage(errorMessage, vsFilename);
        }
        // If there was nothing in the error message then it simply could not find the shader file itself.
        else
        {
            DebugPopup(L"Missing shader file.");
        }

        return false;
    }

    // Compile the pixel shader code.
    result = D3DX11CompileFromFile(psFilename, NULL, NULL, m_pixelShaderName, 
        "ps_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &pixelShaderBuffer, 
        &errorMessage, NULL);
    if(FAILED(result))
    {
        // If the shader failed to compile it should have writen something to the error message.
        if(errorMessage)
        {
            OutputShaderErrorMessage(errorMessage, psFilename);
        }
        // If there was  nothing in the error message then it simply could not find the file itself.
        else
        {
            DebugPopup(L"Missing shader file.");
        }

        return false;
    }

    // Create the vertex shader from the buffer.
    result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), 
        vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
    if(FAILED(result))
    {
        DebugPopup(L"Could not CreateVertexShader from device.");
        return false;
    }

    // Create the pixel shader from the buffer.
    result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), 
        pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
    if(FAILED(result))
    {
        DebugPopup(L"Could not CreateVertexShader from device.");
        return false;
    }

    // Initialize input layout
    InitializeInputLayout(device, vertexShaderBuffer);

    // Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
    vertexShaderBuffer->Release();
    vertexShaderBuffer = 0;

    pixelShaderBuffer->Release();
    pixelShaderBuffer = 0;

    // Initialize vertex shader buffers
    if (! InitializeVertexShaderBuffers(device) )
        return false;
    
    // Initialize pixel shader buffers
    if (! InitializePixelShaderBuffers(device) )
        return false;

    return true;
}


// |----------------------------------------------------------------------------|
// |                           InitializeInputLayout                            |
// |----------------------------------------------------------------------------|
bool Shader::InitializeInputLayout(ID3D11Device* device, ID3D10Blob* vertexShaderBuffer) 
{
    HRESULT result;
    D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
    unsigned int numElements;
    
    // Create the vertex input layout description.
    // This setup needs to match the VertexType stucture in the Model and in the shader.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "NORMAL";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[2].InputSlot = 0;
	polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;

    // Get a count of the elements in the layout.
    numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

    // Create the vertex input layout.
    result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), 
                       &m_layout);
    if(FAILED(result))
    {
        DebugPopup(L"Could not CreateInputLayout from device.");
        return false;
    }

    return true;
}


// |----------------------------------------------------------------------------|
// |                       InitializeVertexShaderBuffers                        |
// |----------------------------------------------------------------------------|
bool Shader::InitializeVertexShaderBuffers(ID3D11Device* device)
{
    HRESULT result;
    D3D11_BUFFER_DESC vsBufferDesc;

    // Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
    vsBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    vsBufferDesc.ByteWidth = sizeof(VSBufferType);
    vsBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    vsBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    vsBufferDesc.MiscFlags = 0;
    vsBufferDesc.StructureByteStride = 0;

    // Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
    result = device->CreateBuffer(&vsBufferDesc, NULL, &m_vsBuffer);
    if(FAILED(result))
    {
        DebugPopup(L"Could not create vsBuffer from device.");
        return false;
    }

    return true;
}

// |----------------------------------------------------------------------------|
// |                       InitializePixelShaderBuffers                         |
// |----------------------------------------------------------------------------|
bool Shader::InitializePixelShaderBuffers(ID3D11Device* device)
{
    HRESULT result;
    D3D11_BUFFER_DESC psBufferDesc;

    // Setup the description of the dynamic matrix constant buffer that is in the pixel shader.
    psBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    psBufferDesc.ByteWidth = sizeof(PSBufferType);
    psBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    psBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    psBufferDesc.MiscFlags = 0;
    psBufferDesc.StructureByteStride = 0;

    // Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
    result = device->CreateBuffer(&psBufferDesc, NULL, &m_psBuffer);
    if(FAILED(result))
    {
        DebugPopup(L"Could not create psBuffer from device.");
        return false;
    }

    return true;
}

// |----------------------------------------------------------------------------|
// |                              ShutdownShader                                |
// |----------------------------------------------------------------------------|
void Shader::ShutdownShader()
{
    // Release the vs and ps constant buffers.
    if(m_vsBuffer)
    {
        m_vsBuffer->Release();
        m_vsBuffer = 0;
    }
    if(m_psBuffer)
    {
        m_psBuffer->Release();
        m_psBuffer = 0;
    }

    // Release the layout.
    if(m_layout)
    {
        m_layout->Release();
        m_layout = 0;
    }

    // Release the pixel shader.
    if(m_pixelShader)
    {
        m_pixelShader->Release();
        m_pixelShader = 0;
    }

    // Release the vertex shader.
    if(m_vertexShader)
    {
        m_vertexShader->Release();
        m_vertexShader = 0;
    }

    return;
}

// |----------------------------------------------------------------------------|
// |                          OutputShaderErrorMessage                          |
// |----------------------------------------------------------------------------|
void Shader::OutputShaderErrorMessage(ID3D10Blob* errorMessage, WCHAR* shaderFilename)
{
    char* compileErrors;
    unsigned long bufferSize, i;
    ofstream fout;

    // Get a pointer to the error message text buffer.
    compileErrors = (char*)(errorMessage->GetBufferPointer());

    // Get the length of the message.
    bufferSize = errorMessage->GetBufferSize();

    // Open a file to write the error message to.
    fout.open("shader-error.txt");

    // Write out the error message.
    for(i=0; i<bufferSize; i++)
    {
        fout << compileErrors[i];
    }

    // Close the file.
    fout.close();

    // Release the error message.
    errorMessage->Release();
    errorMessage = 0;

    // Pop a message up on the screen to notify the user to check the text file for compile errors.
    DebugPopup(L"Error compiling shader.  Check shader-error.txt for message.");

    return;
}

// |----------------------------------------------------------------------------|
// |                                RenderShader                                |
// |----------------------------------------------------------------------------|
void Shader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
    // Set the vertex input layout.
    deviceContext->IASetInputLayout(m_layout);

    // Set the vertex and pixel shaders that will be used to render this triangle.
    deviceContext->VSSetShader(m_vertexShader, NULL, 0);
    deviceContext->PSSetShader(m_pixelShader, NULL, 0);

    // Render the model.
    deviceContext->DrawIndexed(indexCount, 0, 0);

    return;
}


// |----------------------------------------------------------------------------|
// |                            SetShaderParameters                             |
// |----------------------------------------------------------------------------|
bool Shader::SetShaderParameters(ID3D11DeviceContext* deviceContext, 
        D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
        D3DXMATRIX projectionMatrix, Graphic* graphic)
{
	DebugLog ("Shader::SetShaderParameters() called.", DB_GRAPHICS, 10);
    // Set up vertex and pixel buffers
    SetVSBuffer(deviceContext, worldMatrix, viewMatrix, projectionMatrix, graphic);
    SetPSBuffer(deviceContext, graphic);

    return true;
} 


// |----------------------------------------------------------------------------|
// |                               Render                                       |
// |----------------------------------------------------------------------------|
bool Shader::Render(ID3D11DeviceContext* deviceContext, 
    int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
    D3DXMATRIX projectionMatrix, Graphic* graphic)
{
	DebugLog ("Shader::Render() called.", DB_GRAPHICS, 10);
    bool result;

    // Set the shader parameters that it will use for rendering.
    result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix, 
        projectionMatrix, graphic);
    if(!result)
    {
        DebugPopup(L"SetShaderParameters failed.");
        return false;
    }

    // Now render the prepared buffers with the shader.
    RenderShader(deviceContext, indexCount);

    return true;
}