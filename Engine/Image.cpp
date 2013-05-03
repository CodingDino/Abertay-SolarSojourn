// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Image
//      Contains data for a single 2D image, including texture and rendering method.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Image.h"
#include "Shader.h"


// |----------------------------------------------------------------------------|
// |                           Default Constructor                              |
// |----------------------------------------------------------------------------|
Image::Image() :
    Graphic()
{
}


// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
Image::Image(const Image& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
Image::~Image()
{
}


// |----------------------------------------------------------------------------|
// |                              Initialize                                    |
// |----------------------------------------------------------------------------|
bool Image::Initialize()
{
    
	bool result;

	// If there's not a material, make a blank one
	if (!m_material)
	{
		m_material = new Material;
		m_material->shader = GraphicsManager::GetRef()->GetShader("Texture");
	}

	// If there's not a model, make a quad
	if (!m_model)
	{
		m_model = AssetManager::GetRef()->GetModel("quad");
	}

	// If there's not a texture, use default
	if (!m_texture)
	{
		m_texture = AssetManager::GetRef()->GetTexture("default");
	}

    // Initialize parent class
    result =  Graphic::Initialize();
	if (!result)
		return false;

	// Return success
	return true;
}


// |----------------------------------------------------------------------------|
// |                              Shutdown                                      |
// |----------------------------------------------------------------------------|
void Image::Shutdown()
{
    return Graphic::Shutdown();
}


// |----------------------------------------------------------------------------|
// |                               Render                                       |
// |----------------------------------------------------------------------------|
void Image::Render()
{
	DebugLog ("Image::Render() called.", DB_GRAPHICS, 10);

    // Get correct shader to use from material
    Shader* shader = m_material->shader;

    // Pipeline settings
    if (m_material)
    {
        if (m_material->alphaBlend)
            D3DManager::GetRef()->TurnOnAlphaBlending();
        if (m_material->particleBlend)
            D3DManager::GetRef()->TurnOnParticleBlending();
        if (!m_material->backfaceCull)
            D3DManager::GetRef()->TurnOffBackCulling();
        if (!m_material->zBuffer)
            D3DManager::GetRef()->TurnZBufferOff();
    }

    // Put the quad in the buffer
    if(m_model) m_model->Render();

    // Scale, Translate, and Rotate
    D3DXMATRIX worldMatrix = GraphicsManager::GetRef()->GetWorldMatrix();
    D3DXMATRIX scale, rotate, translate;
	// Scale by texture size and scaling factor
	D3DXMatrixScaling(&scale, m_texture->GetWidth()*m_scale.x, m_texture->GetHeight()*m_scale.y, 1.0f);
	// Rotate by orientation factor
	D3DXMatrixRotationYawPitchRoll(&rotate, 0.0f, 0.0f, m_orientation.z);
	// Translate first to the upper left corner, then based on position factor
    D3DXMatrixTranslation(&translate, 
        m_scale.x*m_texture->GetWidth()/2 - SCREEN_WIDTH/2 + m_position.x, 
        -1*m_scale.y*m_texture->GetHeight()/2 + SCREEN_HEIGHT/2 - m_position.y, 
        0.0f);
	// Modify world matrix by scale, rotation, and translation
    worldMatrix = scale * rotate * translate;

    // Render using the shader and a self pointer.
    shader->Render(D3DManager::GetRef()->GetDeviceContext(),
        m_model->GetIndexCount(),
        worldMatrix,
        GraphicsManager::GetRef()->GetBaseViewMatrix(),
        GraphicsManager::GetRef()->GetOrthoMatrix(),
        this);
	
    // Reset pipeline settings
    D3DManager::GetRef()->TurnOffAlphaBlending();
    D3DManager::GetRef()->TurnOnBackCulling();
    D3DManager::GetRef()->TurnZBufferOn();

    return;
}

