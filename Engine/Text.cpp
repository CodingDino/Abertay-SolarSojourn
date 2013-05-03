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

	// Material settings
	if (!m_shader) m_shader = GraphicsManager::GetRef()->GetShader("Texture");
	m_alphaBlend = true;
	m_zBuffer = false;
	m_baseView = true;
	m_ortho = true;

	// If there's not a model, make a setence
	if (!m_model)
	{
        m_model = new Sentence;
        m_model->Initialize();
	}

	// If there's not a font, use default
	if (!m_texture)
	{
		m_texture = AssetManager::GetRef()->GetFont("default");
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
    // Owns sentence
    m_model->Shutdown();
    delete m_model;
    m_model = 0;

    return Graphic::Shutdown();
}


// |----------------------------------------------------------------------------|
// |                          TransformWorldMatrix                              |
// |----------------------------------------------------------------------------|
D3DXMATRIX Text::TransformWorldMatrix(Coord position)
{
	DebugLog ("Text::TransformWorldMatrix() called.", DB_GRAPHICS, 10);

    // Scale, Translate, and Rotate
    D3DXMATRIX worldMatrix = GraphicsManager::GetRef()->GetWorldMatrix();
    D3DXMATRIX scale, rotate, translate;
	// Scale by texture size and scaling factor
	D3DXMatrixScaling(&scale, m_scale.x, m_scale.y, 1.0f);
	// Rotate by orientation factor
	D3DXMatrixRotationYawPitchRoll(&rotate, 0.0f, 0.0f, m_orientation.z);
	// Translate first to the upper left corner, then based on position factor
    D3DXMatrixTranslation(&translate, 
        0.0f + position.x,
        0.0f - position.y,
        0.0f);
	// Modify world matrix by scale, rotation, and translation
    worldMatrix = scale * rotate * translate;

    return worldMatrix;
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
	SetTint(r,g,b,1.0f);
}