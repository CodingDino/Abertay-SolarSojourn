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
    m_material(0)
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

    // Render using the shader and a self pointer.
    shader->Render(D3DManager::GetRef()->GetDeviceContext(),
        m_model->GetIndexCount(),
        GraphicsManager::GetRef()->GetWorldMatrix(),
        GraphicsManager::GetRef()->GetViewMatrix(),
        GraphicsManager::GetRef()->GetProjectionMatrix(),
        this);

    return;
}