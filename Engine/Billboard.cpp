// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Billboard
//      Contains data for a single 2D billboard, rendered on a quad and 
//      automatically turned to face the camera


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Billboard.h"
#include "Shader.h"


// |----------------------------------------------------------------------------|
// |                           Default Constructor                              |
// |----------------------------------------------------------------------------|
Billboard::Billboard() :
    Graphic()
{
}


// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
Billboard::Billboard(const Billboard& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
Billboard::~Billboard()
{
}


// |----------------------------------------------------------------------------|
// |                              Initialize                                    |
// |----------------------------------------------------------------------------|
bool Billboard::Initialize()
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
void Billboard::Shutdown()
{
    return Graphic::Shutdown();
}


// |----------------------------------------------------------------------------|
// |                               Render                                       |
// |----------------------------------------------------------------------------|
void Billboard::Render(Coord position)
{
	DebugLog ("Billboard::Render() called.", DB_GRAPHICS, 10);

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
    D3DXMATRIX scale, rotateY, rotateX, lookat, rotate, translate;

	// Scale by texture size and scaling factor
    if(m_texture)
	    D3DXMatrixScaling(&scale, m_texture->GetWidth()*m_scale.x, m_texture->GetHeight()*m_scale.y, m_scale.z);
    else
	    D3DXMatrixScaling(&scale, m_scale.x, m_scale.y, m_scale.z);


	// Rotate to face camera
    Camera* camera = GraphicsManager::GetRef()->GetCamera();
    //D3DXVECTOR3 positionVec(position.x, position.y, position.z);
    D3DXVECTOR3 cameraPosition(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);
    D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
    D3DXVECTOR3 direction(position.x - camera->GetPosition().x, 
        position.y - camera->GetPosition().y, 
        position.z - camera->GetPosition().z);
    D3DXVECTOR3 axis;
    D3DXVec3Cross(&axis,&direction,&up);
    float mag = D3DXVec3Length(&direction);
    float yaw = atan2(direction.x,direction.z);
    float pitch = D3DX_PI/2 - acos(-direction.y / mag);
    D3DXMatrixRotationYawPitchRoll(&rotate, yaw, pitch, 0.0f);

	// Translate
	D3DXMatrixTranslation(&translate, position.x, position.y, position.z);

	// Modify world matrix by scale, rotation, and translation
    worldMatrix = scale * rotate * translate;

    // Render using the shader and a self pointer.
    shader->Render(D3DManager::GetRef()->GetDeviceContext(),
        m_model->GetIndexCount(),
        worldMatrix,
        GraphicsManager::GetRef()->GetViewMatrix(),
        GraphicsManager::GetRef()->GetProjectionMatrix(),
        this);
    

    // Reset pipeline settings
    D3DManager::GetRef()->TurnOffAlphaBlending();
    D3DManager::GetRef()->TurnOnBackCulling();
    D3DManager::GetRef()->TurnZBufferOn();

    return;
}

