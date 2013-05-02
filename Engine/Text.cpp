// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Text
//      Contains data for a single text object, including texture and rendering 
//		method.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Text.h"
#include "Shader.h"


// |----------------------------------------------------------------------------|
// |                           Default Constructor                              |
// |----------------------------------------------------------------------------|
Text::Text() :
    m_string(0),
    Graphic()
{
}


// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
Text::Text(const Text& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
Text::~Text()
{
}


// |----------------------------------------------------------------------------|
// |                              Initialize                                    |
// |----------------------------------------------------------------------------|
bool Text::Initialize()
{
	DebugLog ("Text::Initialize() called.", DB_GRAPHICS, 1);

	bool result;

	// If there's not a material, make a blank one
	if (!m_material)
	{
		m_material = new Material;
		m_material->Initialize();
		m_material->SetShader(GraphicsManager::GetRef()->GetShader("Texture"));
	}

	// If there's not a model, make a sentence
	if (!m_model)
	{
		m_model = new Sentence();
		m_model->Initialize();
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
void Text::Shutdown()
{
    return Graphic::Shutdown();
}


// |----------------------------------------------------------------------------|
// |                               Render                                       |
// |----------------------------------------------------------------------------|
void Text::Render()
{
	DebugLog ("Text::Render() called.", DB_GRAPHICS, 10);

	// Turn off z buffer
    D3DManager::GetRef()->TurnZBufferOff();

	// Turn on alpha blending
	D3DManager::GetRef()->TurnOnAlphaBlending();

    // Get correct shader to use from material
    Shader* shader = m_material->GetShader();

    // Put the model in the buffer
    if(m_model) m_model->Render();

    // Scale, Translate, and Rotate
    D3DXMATRIX worldMatrix = GraphicsManager::GetRef()->GetWorldMatrix();
    D3DXMATRIX scale, rotate, translate;
	// Scale by texture size and scaling factor
	D3DXMatrixScaling(&scale, m_scale.x, m_scale.y, 1.0f);
	// Rotate by orientation factor
	D3DXMatrixRotationYawPitchRoll(&rotate, 0.0f, 0.0f, m_orientation.z);
	// Translate first to the upper left corner, then based on position factor
    D3DXMatrixTranslation(&translate, 
        0.0f + m_position.x,
        0.0f - m_position.y,
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

	// Turn off alpha blending
	D3DManager::GetRef()->TurnOffAlphaBlending();
	
	// Turn on z buffer
    D3DManager::GetRef()->TurnZBufferOn();

    return;
}


// |----------------------------------------------------------------------------|
// |                               GetText                                      |
// |----------------------------------------------------------------------------|
char* Text::GetText()
{
	char* string = new char[strlen(m_string)+1];
	strcpy(string,m_string);
	return string;
}


// |----------------------------------------------------------------------------|
// |                               SetText                                      |
// |----------------------------------------------------------------------------|
void Text::SetText(const char* string)
{
	// Delete the old string
	delete[] m_string;

	// Copy the new string
	m_string = new char[strlen(string)+1];
	strcpy(m_string,string);

	// Update the vertex buffer based on the new string
	((Sentence*)m_model)->UpdateBuffers(m_string, ((Font*)m_texture));
}


// |----------------------------------------------------------------------------|
// |                               SetColor                                     |
// |----------------------------------------------------------------------------|
void Text::SetColor(float r, float g, float b)
{
	m_material->SetTint(r,g,b,1.0f);
}