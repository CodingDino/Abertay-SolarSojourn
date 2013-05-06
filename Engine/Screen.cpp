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
    m_intermediate(0),
    m_postProcessing(0),
    m_blur(false),
    m_camera(0)
{
}


// |----------------------------------------------------------------------------|
// |                              Initialize                                    |
// |----------------------------------------------------------------------------|
bool Screen::Initialize() {
    bool result = true;

    m_renderTexture = new Texture;
    result = result && m_renderTexture->Initialize();

    m_intermediate = new Texture;
    result = result && m_intermediate->Initialize();

    m_postProcessing = new Image;
    m_postProcessing->SetTexture(m_renderTexture);
    m_postProcessing->SetShader("Texture");
    m_postProcessing->SetRenderToBackBuffer(true);
    result = result && m_postProcessing->Initialize();

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
    if (m_blur) Blur();

    // Render the post-processed scene to the backbuffer
    m_postProcessing->Render();

    // Draw Overlay
    for (std::list<GameObject*>::iterator it=m_overlayObjects.begin(); it != m_overlayObjects.end(); ++it)
         result = result && (*it)->Draw();

    return result;
}

// |----------------------------------------------------------------------------|
// |                                  Blur                                      |
// |----------------------------------------------------------------------------|
bool Screen::Blur()
{ 
	DebugLog ("Screen: Blur() called.", DB_GRAPHICS, 10);
    bool result = true;
    
    m_postProcessing->SetShader("Blur");
    m_postProcessing->SetRenderToBackBuffer(false);
    m_postProcessing->SetRenderTarget(m_intermediate);
    m_postProcessing->Render();
    m_postProcessing->SetReBlur(true);
    m_postProcessing->SetTexture(m_intermediate);
    m_postProcessing->SetRenderTarget(m_renderTexture);
    m_postProcessing->Render();
    m_postProcessing->SetReBlur(false);
    m_postProcessing->SetTexture(m_renderTexture);
    m_postProcessing->SetRenderToBackBuffer(true);
    m_postProcessing->SetRenderTarget(0);

    return result;
}