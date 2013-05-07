// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Screen
//      Abstract class for screens. Contains game objects, executes their game
//      logic.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Screen.h"


// |----------------------------------------------------------------------------|
// |                              Constructor                                   |
// |----------------------------------------------------------------------------|
Screen::Screen() : 
    m_done(0), 
    m_nextScreen(SCREEN_QUIT),
    m_renderTexture(0),
    m_glowMapTexture(0),
    m_glowTexture(0),
    m_intermediate(0),
    m_downSampleTexture(0),
    m_upSampleTexture(0),
    m_postProcessing(0),
    m_downSampleImage(0),
    m_blur(false),
    m_glow(false),
    m_downSampleFactor(4),
    m_camera(0)
{
}


// |----------------------------------------------------------------------------|
// |                              Initialize                                    |
// |----------------------------------------------------------------------------|
bool Screen::Initialize() {
    bool result = true;

    // Set up render texture
    m_renderTexture = new Texture;
    result = result && m_renderTexture->Initialize();

    // Set up glow map texture
    m_glowMapTexture = new Texture;
    result = result && m_glowMapTexture->Initialize();

    // Set up glow texture
    m_glowTexture = new Texture;
    result = result && m_glowTexture->Initialize();

    // Set up post processing image
    m_postProcessing = new Image;
    m_postProcessing->SetTexture(m_renderTexture);
    m_postProcessing->SetShader("Texture");
    m_postProcessing->Initialize();
    m_postProcessing->SetRenderToBackBuffer(true);
    m_postProcessing->SetTexOrtho(true);
    result = result && m_postProcessing->Initialize();

    // Set up downsample
    m_downSampleTexture = new Texture;
    result = result && m_downSampleTexture->Initialize(SCREEN_WIDTH / m_downSampleFactor, SCREEN_HEIGHT / m_downSampleFactor);
    m_intermediate = new Texture;
    result = result && m_intermediate->Initialize(SCREEN_WIDTH / m_downSampleFactor, SCREEN_HEIGHT / m_downSampleFactor);
    m_downSampleImage = new Image;
    m_downSampleImage->SetTexture(m_downSampleTexture);
    m_downSampleImage->SetShader("Texture");
    m_downSampleImage->Initialize();
    m_downSampleImage->SetRenderToBackBuffer(false);
    m_downSampleImage->SetTexOrtho(true);
    m_downSampleImage->SetScale(Coord(1/(float)m_downSampleFactor,1/(float)m_downSampleFactor,1.0f));
    m_downSampleImage->SetPosition(Coord((SCREEN_WIDTH - SCREEN_WIDTH / m_downSampleFactor)/2,(SCREEN_HEIGHT - SCREEN_HEIGHT / m_downSampleFactor)/2,1.0f));
    result = result && m_downSampleImage->Initialize();
    
    // Set up upsample texture
    m_upSampleTexture = new Texture;
    result = result && m_upSampleTexture->Initialize();

    return result;
}


// |----------------------------------------------------------------------------|
// |                                Shutdown                                    |
// |----------------------------------------------------------------------------|
bool Screen::Shutdown() {
    bool result = true;
    
    for (std::list<GameObject*>::iterator it=m_backgroundObjects.begin(); it != m_backgroundObjects.end(); ++it)
         delete (*it);
    m_backgroundObjects.clear();
    for (std::list<GameObject*>::iterator it=m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
         delete (*it);
    m_gameObjects.clear();
    for (std::list<GameObject*>::iterator it=m_overlayObjects.begin(); it != m_overlayObjects.end(); ++it)
         delete (*it);
    m_overlayObjects.clear();

    delete m_renderTexture;
    m_renderTexture = 0;
    delete m_intermediate;
    m_intermediate = 0;
    delete m_postProcessing;
    m_postProcessing = 0;
    delete m_downSampleTexture;
    m_downSampleTexture = 0;
    delete m_downSampleImage;
    m_downSampleImage = 0;
    delete m_glowMapTexture;
    m_glowMapTexture = 0;
    delete m_glowTexture;
    m_glowTexture = 0;
    delete m_upSampleTexture;
    m_upSampleTexture = 0;

    return result;
}


// |----------------------------------------------------------------------------|
// |                                 Logic                                      |
// |----------------------------------------------------------------------------|
bool Screen::Logic() 
{ 
    bool result = true;

    m_camera->Logic();

    for (std::list<GameObject*>::iterator it=m_backgroundObjects.begin(); it != m_backgroundObjects.end(); ++it)
         result = result && (*it)->Logic();
    for (std::list<GameObject*>::iterator it=m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
         result = result && (*it)->Logic();
    for (std::list<GameObject*>::iterator it=m_overlayObjects.begin(); it != m_overlayObjects.end(); ++it)
         result = result && (*it)->Logic();

    return result;
}


// |----------------------------------------------------------------------------|
// |                                  Draw                                      |
// |----------------------------------------------------------------------------|
bool Screen::Draw()
{ 
	DebugLog ("Screen: Draw() called.", DB_GRAPHICS, 10);
    bool result = true;

    // Prepare the render to texture for rendering
    m_renderTexture->ClearRenderTarget(0.0f,0.0f,0.0f,0.0f);

    // Draw Background objects
    for (std::list<GameObject*>::iterator it=m_backgroundObjects.begin(); it != m_backgroundObjects.end(); ++it)
         result = result && (*it)->Draw();

    // Draw main objects
    for (std::list<GameObject*>::iterator it=m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
         result = result && (*it)->Draw();

    // Apply Post-Processing
    if (m_blur) // Full-screen blur
    {

        // blur from the glow mapped texture
        m_downSampleImage->SetTexture(m_renderTexture);

        // Render the upsampled texture back to the to_render texture
        m_renderTexture->ClearRenderTarget(0.0f,0.0f,0.0f,0.0f);
        m_postProcessing->SetTexture(m_upSampleTexture);
        m_postProcessing->SetShader("Texture");
        m_postProcessing->SetRenderToBackBuffer(false);
        m_postProcessing->SetRenderTarget(m_renderTexture);
        m_postProcessing->Render();
        m_postProcessing->SetTexture(m_renderTexture);
        m_postProcessing->SetRenderTarget(0);
        m_postProcessing->SetRenderToBackBuffer(true);  
    }
    if (m_glow) // Glow in bright items
    {
        ApplyGlowMask();

        // Blur
        m_downSampleFactor = 64;
        m_downSampleImage->SetTexture(m_glowMapTexture);
        DownSampleTexture();
        BlurDownsampledTexture(10);
        UpSampleTexture();

        m_downSampleFactor = 32;
        m_downSampleImage->SetTexture(m_upSampleTexture);
        DownSampleTexture();
        BlurDownsampledTexture(8);
        UpSampleTexture();

        m_downSampleFactor = 16;
        m_downSampleImage->SetTexture(m_upSampleTexture);
        DownSampleTexture();
        BlurDownsampledTexture(6);
        UpSampleTexture();

        m_downSampleFactor = 8;
        m_downSampleImage->SetTexture(m_upSampleTexture);
        DownSampleTexture();
        BlurDownsampledTexture(4);
        UpSampleTexture();

        m_downSampleFactor = 4;
        m_downSampleImage->SetTexture(m_upSampleTexture);
        DownSampleTexture();
        BlurDownsampledTexture(2);
        UpSampleTexture();

        // Inner blur
        m_downSampleFactor = 2;
        m_downSampleImage->SetTexture(m_upSampleTexture);
        DownSampleTexture();
        BlurDownsampledTexture();
        UpSampleTexture();

        // Combine the glow texture and the scene
        m_postProcessing->SetGlowStrength(3.0f);
        CombineGlowTexture();

        // Render the processed texture back to the to_render texture
        m_renderTexture->ClearRenderTarget(0.0f,0.0f,0.0f,0.0f);
        m_postProcessing->SetTexture(m_glowTexture);
        m_postProcessing->SetShader("Texture");
        m_postProcessing->SetAlphaBlend(true);
        m_postProcessing->SetRenderToBackBuffer(false);
        m_postProcessing->SetRenderTarget(m_renderTexture);
        m_postProcessing->Render();
        m_postProcessing->SetTexture(m_renderTexture);
        m_postProcessing->SetRenderTarget(0);
        m_postProcessing->SetRenderToBackBuffer(true);  
    }

    // Render the post-processed scene to the backbuffer
    m_postProcessing->Render();

    // Draw Overlay
    for (std::list<GameObject*>::iterator it=m_overlayObjects.begin(); it != m_overlayObjects.end(); ++it)
         result = result && (*it)->Draw();

    return result;
}


// |----------------------------------------------------------------------------|
// |                            ApplyGlowMask                                   |
// |----------------------------------------------------------------------------|
bool Screen::ApplyGlowMask()
{ 
	DebugLog ("Screen: ApplyGlowMask() called.", DB_GRAPHICS, 10);
    bool result = true;

    // Prepare the render to texture for rendering
    m_glowMapTexture->ClearRenderTarget(0.0f,0.0f,0.0f,0.0f);
    m_postProcessing->SetTexture(m_renderTexture);
    m_postProcessing->SetShader("GlowMap");
    m_postProcessing->SetRenderToBackBuffer(false);
    m_postProcessing->SetRenderTarget(m_glowMapTexture);
    m_postProcessing->Render();

    return result;
}


// |----------------------------------------------------------------------------|
// |                                  Blur                                      |
// |----------------------------------------------------------------------------|
bool Screen::BlurDownsampledTexture(int numTimes)
{ 
	DebugLog ("Screen: BlurDownsampledTexture() called.", DB_GRAPHICS, 10);
    bool result = true;

    for (int i=0; i<numTimes; ++i)
    {

        // Prepare the render to texture for rendering
        m_intermediate->ClearRenderTarget(0.0f,0.0f,0.0f,0.0f);
    
        // Horizontal Blur
        m_downSampleTexture->SetWidth(SCREEN_WIDTH);
        m_downSampleTexture->SetHeight(SCREEN_HEIGHT);
        m_intermediate->SetWidth(SCREEN_WIDTH/m_downSampleFactor);
        m_intermediate->SetHeight(SCREEN_HEIGHT/m_downSampleFactor);
        m_downSampleImage->SetTexture(m_downSampleTexture);
        m_downSampleImage->SetShader("Blur");
        m_downSampleImage->SetRenderToBackBuffer(false);
        m_downSampleImage->SetRenderTarget(m_intermediate);
        m_downSampleImage->Render();

        // Prepare the render to texture for rendering
        m_downSampleTexture->ClearRenderTarget(0.0f,0.0f,0.0f,0.0f);
    
        // Vertical Blur
        m_intermediate->SetWidth(SCREEN_WIDTH);
        m_intermediate->SetHeight(SCREEN_HEIGHT);
        m_downSampleTexture->SetWidth(SCREEN_WIDTH/m_downSampleFactor);
        m_downSampleTexture->SetHeight(SCREEN_HEIGHT/m_downSampleFactor);
        m_downSampleImage->SetReBlur(true);
        m_downSampleImage->SetTexture(m_intermediate);
        m_downSampleImage->SetRenderToBackBuffer(false);
        m_downSampleImage->SetRenderTarget(m_downSampleTexture);
        m_downSampleImage->Render();
        m_downSampleImage->SetReBlur(false);

    }
    return result;
}


// |----------------------------------------------------------------------------|
// |                          DownSampleTexture                                 |
// |----------------------------------------------------------------------------|
bool Screen::DownSampleTexture()
{ 
	DebugLog ("Screen: DownSampleTexture() called.", DB_GRAPHICS, 10);
    bool result = true;

    // Prepare the render to texture for rendering
    m_downSampleTexture->ClearRenderTarget(0.0f,0.0f,0.0f,0.0f);
    m_downSampleTexture->SetWidth(SCREEN_WIDTH/m_downSampleFactor);
    m_downSampleTexture->SetHeight(SCREEN_HEIGHT/m_downSampleFactor);
    m_downSampleImage->SetShader("Texture");
    m_downSampleImage->SetRenderToBackBuffer(false);
    m_downSampleImage->SetRenderTarget(m_downSampleTexture);
    m_downSampleImage->Render();

    return result;
}


// |----------------------------------------------------------------------------|
// |                           UpSampleTexture                                  |
// |----------------------------------------------------------------------------|
bool Screen::UpSampleTexture()
{ 
	DebugLog ("Screen: UpSampleTexture() called.", DB_GRAPHICS, 10);
    bool result = true;

    // Prepare the render to texture for rendering
    m_upSampleTexture->ClearRenderTarget(0.0f,0.0f,0.0f,0.0f);
    
    m_downSampleTexture->SetWidth(SCREEN_WIDTH);
    m_downSampleTexture->SetHeight(SCREEN_HEIGHT);
    m_postProcessing->SetTexture(m_downSampleTexture);
    m_postProcessing->SetShader("Texture");
    m_postProcessing->SetRenderToBackBuffer(false);
    m_postProcessing->SetRenderTarget(m_upSampleTexture);
    m_postProcessing->Render();

    return result;
}


// |----------------------------------------------------------------------------|
// |                          CombineGlowTexture                                |
// |----------------------------------------------------------------------------|
bool Screen::CombineGlowTexture()
{ 
	DebugLog ("Screen: CombineGlowTexture() called.", DB_GRAPHICS, 10);
    bool result = true;

    // Prepare the render to texture for rendering
    m_glowTexture->ClearRenderTarget(0.0f,0.0f,0.0f,0.0f);
    m_postProcessing->SetTexture(m_renderTexture);
    m_postProcessing->SetGlowTexture(m_upSampleTexture);
    m_postProcessing->SetShader("Glow");
    m_postProcessing->SetRenderToBackBuffer(false);
    m_postProcessing->SetRenderTarget(m_glowTexture);
    m_postProcessing->Render();

    return result;
}