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
		m_material->Initialize();
		m_material->SetShader(GraphicsManager::GetRef()->GetShader("Texture"));
	}

	// If there's not a model, make a quad
	if (!m_model)
	{
		m_model = new Quad();
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
void Billboard::Shutdown()
{
    return Graphic::Shutdown();
}


// |----------------------------------------------------------------------------|
// |                               Render                                       |
// |----------------------------------------------------------------------------|
void Billboard::Render()
{
	DebugLog ("Billboard::Render() called.", DB_GRAPHICS, 10);

	// Turn on alpha blending
	D3DManager::GetRef()->TurnOnAlphaBlending();

    // Get correct shader to use from material
    Shader* shader = m_material->GetShader();

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
    Coord cameraPosition = camera->GetPosition();
    Coord direction = m_position - cameraPosition;
    float mag = sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
    float yaw = atan2(direction.x,direction.z);
    float pitch = -atan2(direction.y,direction.z);
    
	D3DXMatrixRotationX(&rotateX, pitch);
	D3DXMatrixRotationY(&rotateY, yaw);
    rotate =  rotateX;

	// Translate
	D3DXMatrixTranslation(&translate, m_position.x, m_position.y, m_position.z);

	// Modify world matrix by scale, rotation, and translation
    worldMatrix = scale * rotate * translate;

    // Render using the shader and a self pointer.
    shader->Render(D3DManager::GetRef()->GetDeviceContext(),
        m_model->GetIndexCount(),
        worldMatrix,
        GraphicsManager::GetRef()->GetViewMatrix(),
        GraphicsManager::GetRef()->GetProjectionMatrix(),
        this);
    
	// Turn off alpha blending
	D3DManager::GetRef()->TurnOffAlphaBlending();

    return;
}

