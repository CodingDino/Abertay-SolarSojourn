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
	m_postProcessingEnabled(true),
    m_blur(false),
    m_glow(false),
    m_downSampleFactor(4),
    m_camera(0),
    m_skybox(0),
    m_position(0),
    m_rotation(0),
    m_sun(0)
{
}


// |----------------------------------------------------------------------------|
// |                              Initialize                                    |
// |----------------------------------------------------------------------------|
bool Screen::Initialize() {

    // Define Variables
    bool result = true;
    GameObject* gameObject;

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

    // Set up default skybox
    m_skybox = new SkyBox;
    m_skybox->Initialize();
    //m_skybox->SetRenderTarget(m_renderTexture);
    m_skybox->SetRenderToBackBuffer(true);
	
    // Coordinate display
    m_position = new Text;
    m_position->SetFont("radio_space_regular_20");
    m_position->Initialize();
    m_position->SetRenderToBackBuffer(true);
	if (m_camera)
		m_position->SetText(("pos: "+m_camera->GetPosition().ToString()).c_str());
    // Set up game object
    gameObject = new GameObject;
    gameObject->Initialize();
    gameObject->SetGraphic(m_position);
    m_overlayObjects.push_back(gameObject);

    // Rotation display
    m_rotation = new Text;
    m_rotation->SetFont("radio_space_regular_20");
    m_rotation->Initialize();
    m_rotation->SetRenderToBackBuffer(true);
	if (m_camera)
		m_rotation->SetText(("rot: "+m_camera->GetOrientation().ToString()).c_str());
    // Set up game object
    gameObject = new GameObject;
    gameObject->Initialize();
    gameObject->SetGraphic(m_rotation);
	gameObject->SetPosition(Coord(0.0f,30.0f,0.0f));
    m_overlayObjects.push_back(gameObject);

    // FPS display
    m_fpsDisplay = new Text;
    m_fpsDisplay->SetFont("radio_space_regular_20");
    m_fpsDisplay->Initialize();
    m_fpsDisplay->SetRenderToBackBuffer(true);
	m_fpsDisplay->SetText("fps: 0");
    // Set up game object
    gameObject = new GameObject;
    gameObject->Initialize();
    gameObject->SetGraphic(m_fpsDisplay);
	gameObject->SetPosition(Coord(0.0f,60.0f,0.0f));
    m_overlayObjects.push_back(gameObject);

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
    
    if(m_skybox)
    {
        delete m_skybox;
        m_skybox = 0;
    }
    if(m_sun)
    {
        delete m_sun;
        m_sun = 0;
    }

    return result;
}


// |----------------------------------------------------------------------------|
// |                                 Logic                                      |
// |----------------------------------------------------------------------------|
bool Screen::Logic() 
{ 
    bool result = true;

    if(m_camera)
		m_camera->Logic();

    for (std::list<GameObject*>::iterator it=m_backgroundObjects.begin(); it != m_backgroundObjects.end(); ++it)
         result = result && (*it)->Logic();
    for (std::list<GameObject*>::iterator it=m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
         result = result && (*it)->Logic();
    for (std::list<GameObject*>::iterator it=m_overlayObjects.begin(); it != m_overlayObjects.end(); ++it)
         result = result && (*it)->Logic();
	
    // Update position / rotation readout
	if (m_camera && m_position && m_rotation)
	{
		m_position->SetText(("pos: "+m_camera->GetPosition().ToString()).c_str());
		m_rotation->SetText(("rot: "+m_camera->GetOrientation().ToString()).c_str());
	}
	// Update fps
	if (m_fpsDisplay)
	{
		std::string string = "";
		string += "fps: ";
		string += std::to_string(static_cast<long long>(TimerManager::GetRef()->GetFPS()));
		m_fpsDisplay->SetText(string.c_str());
	}
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

    // Draw skybox
    if (m_skybox) m_skybox->Render();
    // Draw sun
    if (m_sun) m_sun->Render();

    // Draw Background objects
    for (std::list<GameObject*>::iterator it=m_backgroundObjects.begin(); it != m_backgroundObjects.end(); ++it)
         result = result && (*it)->Draw();

    // Draw main objects
    for (std::list<GameObject*>::iterator it=m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
         result = result && (*it)->Draw();

    // Apply Post-Processing
    if (m_postProcessingEnabled && m_blur) // Full-screen blur
    {
        // Blur
        m_downSampleFactor = 2;
        m_downSampleImage->SetTexture(m_renderTexture);
        DownSampleTexture();
        BlurDownsampledTexture(1);
        UpSampleTexture();

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
    if (m_postProcessingEnabled && m_glow) // Glow in bright items
    {
        ApplyGlowMask();

        // Blur
        m_downSampleFactor = 64;
        m_downSampleImage->SetTexture(m_glowMapTexture);
        DownSampleTexture();
        BlurDownsampledTexture(1);
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
    if (m_postProcessingEnabled) 
		m_postProcessing->Render();

    // Draw Overlay
    for (std::list<GameObject*>::iterator it=m_overlayObjects.begin(); it != m_overlayObjects.end(); ++it)
         result = result && (*it)->Draw();

    return result;
}


// |----------------------------------------------------------------------------|
// |                            EnablePostProcessing                            |
// |----------------------------------------------------------------------------|
void Screen::EnablePostProcessing()
{ 
	DebugLog ("Screen: EnablePostProcessing() called.", DB_GRAPHICS, 1);
	
	m_postProcessingEnabled = true;

	// Skybox
    if (m_skybox) 
	{
    	m_skybox->SetRenderTarget(m_renderTexture);
		m_skybox->SetRenderToBackBuffer(false);
	}
	// Sun
    if (m_sun) 
	{
    	m_sun->SetRenderTarget(m_renderTexture);
		m_sun->SetRenderToBackBuffer(false);
	}

    // Background objects
    for (std::list<GameObject*>::iterator it=m_backgroundObjects.begin(); it != m_backgroundObjects.end(); ++it)
    {
		if ((*it)->GetGraphic())
		{
    		(*it)->GetGraphic()->SetRenderTarget(m_renderTexture);
			(*it)->GetGraphic()->SetRenderToBackBuffer(false);
		}
	}

    // main objects
    for (std::list<GameObject*>::iterator it=m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
    {
		if ((*it)->GetGraphic())
		{
    		(*it)->GetGraphic()->SetRenderTarget(m_renderTexture);
			(*it)->GetGraphic()->SetRenderToBackBuffer(false);
		}
	}
}


// |----------------------------------------------------------------------------|
// |                           DisablePostProcessing                            |
// |----------------------------------------------------------------------------|
void Screen::DisablePostProcessing()
{ 
	DebugLog ("Screen: DisablePostProcessing() called.", DB_GRAPHICS, 1);

	m_postProcessingEnabled = false;

	// Skybox
    if (m_skybox) 
	{
    	m_skybox->SetRenderTarget(0);
		m_skybox->SetRenderToBackBuffer(true);
	}
	// Sun
    if (m_sun) 
	{
    	m_sun->SetRenderTarget(0);
		m_sun->SetRenderToBackBuffer(true);
	}

    // Background objects
    for (std::list<GameObject*>::iterator it=m_backgroundObjects.begin(); it != m_backgroundObjects.end(); ++it)
    {
		if ((*it)->GetGraphic())
		{
    		(*it)->GetGraphic()->SetRenderTarget(0);
			(*it)->GetGraphic()->SetRenderToBackBuffer(true);
		}
	}

    // main objects
    for (std::list<GameObject*>::iterator it=m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
    {
		if ((*it)->GetGraphic())
		{
    		(*it)->GetGraphic()->SetRenderTarget(0);
			(*it)->GetGraphic()->SetRenderToBackBuffer(true);
		}
	}
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