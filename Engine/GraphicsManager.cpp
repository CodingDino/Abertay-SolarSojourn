// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// GraphicsClass
//      Overall control of graphics and rendering, holds model objects and other graphics objects


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "GraphicsManager.h"

GraphicsManager* GraphicsManager::s_instance = 0;


// |----------------------------------------------------------------------------|
// |                           Default Constructor                              |
// |----------------------------------------------------------------------------|
GraphicsManager::GraphicsManager() :
    m_screen(0),
    m_screenCounter(0),
    m_colorShader(0)
{
}


// |----------------------------------------------------------------------------|
// |                              GetInstance                                   |
// |----------------------------------------------------------------------------|
GraphicsManager* GraphicsManager::GetInstance()
{
    if (s_instance == 0)
        s_instance = new GraphicsManager;
    return s_instance;
}


// |----------------------------------------------------------------------------|
// |                              Initialize                                    |
// |----------------------------------------------------------------------------|
bool GraphicsManager::Initialize(int screenWidth, int screenHeight)
{
    bool result;

    // Record screen dimmensions
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;

    // Create the Direct3D object.
    m_D3D = D3DManager::GetInstance();
    if(!m_D3D)
    {
        DebugPopup(L"D3DManager GetInstance failed.");
        return false;
    }

    // Initialize the Direct3D object.
    result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
    if(!result)
    {
        DebugPopup(L"Could not initialize Direct3D.");
        return false;
    }

    // Create the camera object.
    //m_Camera = new CameraClass;
    //if(!m_Camera)
    //{
    //    return false;
    //}

    // Initialize a base view matrix with the camera for 2D user interface rendering.
    //m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
    //m_Camera->Render();
    //m_Camera->GetViewMatrix(baseViewMatrix);

    // Set the initial position of the camera.
    //m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

    // Create the shader objects.
    m_colorShader = new ColorShader;
    if(!m_colorShader)
    {
        DebugPopup(L"Could not create ColorShader.");
        return false;
    }
    //m_LightShader = new LightShaderClass;
    //if(!m_LightShader)
    //{
    //    return false;
    //}
    //m_TextureShader = new TextureShaderClass;
    //if(!m_LightShader)
    //{
    //    return false;
    //}
    
    // Initialize the shader objects.
    result = m_colorShader->Initialize(m_D3D->GetDevice());
    if(!result)
    {
        DebugPopup(L"Could not initialize ColorShader.");
        return false;
    }
    //result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
    //if(!result)
    //{
    //    MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
    //    return false;
    //}
    //result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
    //if(!result)
    //{
    //    MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
    //    return false;
    //}

    return true;
}


// |----------------------------------------------------------------------------|
// |                              Shutdown                                      |
// |----------------------------------------------------------------------------|
void GraphicsManager::Shutdown()
{
    // Release the shader objects.
    if(m_colorShader)
    {
        m_colorShader->Shutdown();
        delete m_colorShader;
        m_colorShader = 0;
    }
    //if(m_LightShader)
    //{
    //    m_LightShader->Shutdown();
    //    delete m_LightShader;
    //    m_LightShader = 0;
    //}
    //if(m_TextureShader)
    //{
    //    m_TextureShader->Shutdown();
    //    delete m_TextureShader;
    //    m_TextureShader = 0;
    //}

    //// Release the camera object.
    //if(m_Camera)
    //{
    //    delete m_Camera;
    //    m_Camera = 0;
    //}

    // Release the D3D object.
    if(m_D3D)
    {
        m_D3D->Shutdown();
        m_D3D = 0;
    }
    
    // Kill instance
    delete s_instance;
    s_instance = 0;

    return;
}


// |----------------------------------------------------------------------------|
// |                               Frame                                        |
// |----------------------------------------------------------------------------|
bool GraphicsManager::Frame(int mouseX, int mouseY, int fps, int cpu, float frameTime,
    Coord camera_rotation, Coord camera_position, bool transfer)
{
    bool result;

    // Swap out bitmaps if needed
    if (transfer && m_screenCounter >= 1000)
    {
        m_screenCounter = 0;
        m_screen++;
    }
    m_screenCounter += frameTime;

    // Set the position of the camera.
    // m_Camera->SetPosition(camera_position.x, camera_position.y, camera_position.z-300.0f);

    // Set the rotation of the camera.
    // m_Camera->SetRotation(camera_rotation.x, camera_rotation.y, camera_rotation.z);
    
    // Render the graphics scene.
    result = Render(mouseX, mouseY, camera_position);
    if(!result)
    {
        return false;
    }

    return true;
}


// |----------------------------------------------------------------------------|
// |                              Render                                        |
// |----------------------------------------------------------------------------|
bool GraphicsManager::Render(int mouseX, int mouseY, Coord camera_position)
{
    bool result;
    static float rotation = 0.0f;

    result = BeginRender();

    // Turn off the Z buffer and culling for skybox
    //m_D3D->TurnZBufferOff();
    //m_D3D->TurnOffBackCulling();

    // Skybox rendering

    // Turn the Z buffer and back culling on now that skybox is rendered.
    //m_D3D->TurnZBufferOn();
    //m_D3D->TurnOnBackCulling();

    // Render Normal Objects

    // Turn on alpha blending.
    //m_D3D->TurnOnAlphaBlending();

    //// Put the particle system vertex and index buffers on the graphics pipeline to prepare them for drawing.
    //m_ParticleSystem->Render(m_D3D->GetDeviceContext());

    //// Render the particles using the texture shader.
    //D3DXMatrixIdentity(&worldMatrix);
    //result = m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
    //                  m_ParticleSystem->GetTexture());
    //if(!result)
    //{
    //    return false;
    //}

    // Turn off alpha blending.
    //m_D3D->TurnOffAlphaBlending();

    // Turn off the Z buffer to begin all 2D rendering.
    //m_D3D->TurnZBufferOff();

    // Turn on the alpha blending before rendering the text.
    //m_D3D->TurnOnAlphaBlending();

    // BITMAP rendering
    //result = result && BitmapRender(*crosshairs, mouseX-30, mouseY-25);
    //result = result && BitmapRender(*HUD, 0, 0);

    // TEXT rendering
    //result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
    //if(!result)
    //{
    //    return false;
    //}

    // Turn off alpha blending after rendering the text.
    //m_D3D->TurnOffAlphaBlending();

    // Turn the Z buffer back on now that all 2D rendering has completed.
    //m_D3D->TurnZBufferOn();

    // Perform closing actions
    result = result && EndRender();

    return result;
}


// |----------------------------------------------------------------------------|
// |                            BeginRender                                     |
// |----------------------------------------------------------------------------|
bool GraphicsManager::BeginRender()
{
    // Clear the buffers to begin the scene.
    m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

    // Generate the view matrix based on the camera's position.
    //m_Camera->Render();

    // Get the world, view, and projection matrices from the camera and d3d objects.
    //m_Camera->GetViewMatrix(viewMatrix);
    //m_D3D->GetWorldMatrix(worldMatrix);
    //m_D3D->GetProjectionMatrix(projectionMatrix);
    //m_D3D->GetOrthoMatrix(orthoMatrix);

    return true;
}


// |----------------------------------------------------------------------------|
// |                            EndRender                                       |
// |----------------------------------------------------------------------------|
bool GraphicsManager::EndRender()
{
    // Present the rendered scene to the screen.
    m_D3D->EndScene();

    return true;
}


// |----------------------------------------------------------------------------|
// |                            ModelRender                                     |
// |----------------------------------------------------------------------------|
//bool GraphicsManager::ModelRender(ModelClass& to_render, D3DXMATRIX scale, 
//    D3DXMATRIX translate, D3DXMATRIX rotate)
//{
//    D3DXMATRIX scaleMatrix, translationMatrix, rotationMatrix;
//    bool result = true;
//
//    // Modify the world matrix as needed.
//    D3DXMatrixIdentity(&worldMatrix);
//    worldMatrix = scale * rotate * translate;
//    
//    // Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
//    to_render.Render(m_D3D->GetDeviceContext());
//    
//    // Render the model using the light shader.
//    result = m_LightShader->Render(m_D3D->GetDeviceContext(), to_render.GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
//                                    m_Light->GetPosition(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), 
//                                    m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), to_render.GetTexture());
//
//    return result;
//}



// |----------------------------------------------------------------------------|
// |                            BitmapRender                                    |
// |----------------------------------------------------------------------------|
//bool GraphicsManager::BitmapRender(BitmapClass& to_render, int x, int y)
//{
//    bool result;
//
//    // Change world matrix to identity before rendering.
//    D3DXMatrixIdentity(&worldMatrix);
//    
//    // Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
//    result = to_render.Render(m_D3D->GetDeviceContext(), x, y);
//    if(!result)
//    {
//        return false;
//    }
//    // Render the bitmap with the texture shader.
//    result = m_TextureShader->Render(m_D3D->GetDeviceContext(), to_render.GetIndexCount(), 
//        worldMatrix, baseViewMatrix, orthoMatrix, to_render.GetTexture());
//    if(!result)
//    {
//        return false;
//    }
//
//    return result;
//}