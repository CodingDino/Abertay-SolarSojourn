// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Graphic
//      Contains data for a single graphic, including model, texture, and material.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Graphic.h"
#include "Shader.h"


// |----------------------------------------------------------------------------|
// |                           Default Constructor                              |
// |----------------------------------------------------------------------------|
Graphic::Graphic() :
    m_model(0),
    m_texture(0),
    m_material(0),
    m_scale(1.0f,1.0f,1.0f),
    m_orientation(0.0f,0.0f,0.0f),
    m_position(0.0f,0.0f,0.0f)
{
}


// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
Graphic::Graphic(const Graphic& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
Graphic::~Graphic()
{
}


// |----------------------------------------------------------------------------|
// |                              Initialize                                    |
// |----------------------------------------------------------------------------|
bool Graphic::Initialize()
{
    return true;
}


// |----------------------------------------------------------------------------|
// |                              Shutdown                                      |
// |----------------------------------------------------------------------------|
void Graphic::Shutdown()
{
    return;
}


// |----------------------------------------------------------------------------|
// |                               Render                                       |
// |----------------------------------------------------------------------------|
void Graphic::Render()
{
	DebugLog ("Graphic::Render() called.", DB_GRAPHICS, 10);
    // Get correct shader to use from material
    Shader* shader = m_material->GetShader();

    // Put the model in the buffer
    if(m_model) m_model->Render(D3DManager::GetRef()->GetDeviceContext());

    // Scale, Translate, and Rotate
    D3DXMATRIX worldMatrix = GraphicsManager::GetRef()->GetWorldMatrix();
    D3DXMATRIX scale, rotate, translate;
	D3DXMatrixScaling(&scale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixRotationYawPitchRoll(&rotate, m_orientation.x, m_orientation.y, m_orientation.z);
	D3DXMatrixTranslation(&translate, m_position.x, m_position.y, m_position.z);
    worldMatrix = scale * rotate * translate;

    // Render using the shader and a self pointer.
    shader->Render(D3DManager::GetRef()->GetDeviceContext(),
        m_model->GetIndexCount(),
        worldMatrix,
        GraphicsManager::GetRef()->GetViewMatrix(),
        GraphicsManager::GetRef()->GetProjectionMatrix(),
        this);

    return;
}