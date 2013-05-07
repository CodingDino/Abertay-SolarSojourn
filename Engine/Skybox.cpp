// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// SkyBox
//      Contains a skybox which automatically renders at the player location. MUST be rendered first.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "SkyBox.h"
#include "Shader.h"


// |----------------------------------------------------------------------------|
// |                           Default Constructor                              |
// |----------------------------------------------------------------------------|
SkyBox::SkyBox() :
    Graphic()
{
}


// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
SkyBox::SkyBox(const SkyBox& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
SkyBox::~SkyBox()
{
}


// |----------------------------------------------------------------------------|
// |                              Initialize                                    |
// |----------------------------------------------------------------------------|
bool SkyBox::Initialize()
{
    
	bool result;

	// Material settings
	if (!m_shader) m_shader = GraphicsManager::GetRef()->GetShader("Texture");
    m_zBuffer = false;
    m_backfaceCull = false;

	// If there's not a model, make a quad
	if (!m_model)
	{
		m_model = AssetManager::GetRef()->GetModel("cube");
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
void SkyBox::Shutdown()
{
    return Graphic::Shutdown();
}


// |----------------------------------------------------------------------------|
// |                         TransformWorldMatrix                               |
// |----------------------------------------------------------------------------|
D3DXMATRIX SkyBox::TransformWorldMatrix(Coord position)
{
	DebugLog ("SkyBox::TransformWorldMatrix() called.", DB_GRAPHICS, 10);

    // Scale, Translate, and Rotate
    D3DXMATRIX worldMatrix = GraphicsManager::GetRef()->GetWorldMatrix();
    D3DXMATRIX scale, rotate, translate;

	// Position on camera
    Camera* camera = GraphicsManager::GetRef()->GetCamera();
    D3DXVECTOR3 cameraPosition(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);
	D3DXMatrixScaling(&scale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixRotationYawPitchRoll(&rotate, m_orientation.x, m_orientation.y, m_orientation.z);
	D3DXMatrixTranslation(&translate, cameraPosition.x+m_position.x, cameraPosition.y+m_position.y, cameraPosition.z+m_position.z);
    worldMatrix = scale * rotate * translate;
    return worldMatrix;

	// Translate
	D3DXMatrixTranslation(&translate, position.x, position.y, position.z);

	// Modify world matrix by scale, rotation, and translation
    worldMatrix = scale * rotate * translate;

    return worldMatrix;
}

