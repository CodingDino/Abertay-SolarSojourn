// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// SystemManager
//      Contains management classes for game objects, graphics, and input.
//      Runs main game loop and calls sub loops.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "SystemManager.h"


// |----------------------------------------------------------------------------|
// |                           Default Constructor                              |
// |----------------------------------------------------------------------------|
SystemManager::SystemManager() :
    m_input(0),
    m_graphics(0),
    m_timer(0),
    m_assets(0),
    m_lights(0),
    m_sound(0),
    m_game(0)
{
}


// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
SystemManager::SystemManager(const SystemManager& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
SystemManager::~SystemManager()
{
}


// |----------------------------------------------------------------------------|
// |                              Initialize                                    |
// |----------------------------------------------------------------------------|
bool SystemManager::Initialize()
{
    int screenWidth, screenHeight;
    bool result;


    // Initialize the width and height of the screen to zero before sending the variables into the function.
    screenWidth = 0;
    screenHeight = 0;

    // Initialize the windows api.
    InitializeWindows(screenWidth, screenHeight);

    // Create the input object.  This object will be used to handle reading the keyboard input from the user.
    m_input = new InputManager();
    if(!m_input)
    {
        DebugPopup(L"Could not get instance of InputManager. Aborting.");
        return false;
    }

    // Initialize the input object.
    result = m_input->Initialize(m_hinstance, screenWidth, screenHeight);
    if(!result)
    {
        DebugPopup(L"Could not initialize InputManager. Aborting.");
        return false;
    }

    // Create the graphics object.  This object will handle rendering all the graphics for this application.
    m_graphics = new GraphicsManager();
    if(!m_graphics)
    {
        DebugPopup(L"Could not get instance of GraphicsManager. Aborting.");
        return false;
    }

    // Initialize the graphics object.
    result = m_graphics->Initialize(screenWidth, screenHeight);
    if(!result)
    {
        DebugPopup(L"Could not initialize GraphicsManager. Aborting.");
        return false;
    }

    // Create the sound object.
    m_sound = new SoundManager;
    if(!m_sound)
    {
        return false;
    }
 
    // Initialize the sound object.
    result = m_sound->Initialize();
    if(!result)
    {
        DebugPopup(L"Could not initialize Direct Sound.");
        return false;
    }

    // Create the timer object.
    m_timer = new TimerManager();
    if(!m_timer)
    {
        DebugPopup(L"Could not get instance of TimerManager. Aborting.");
        return false;
    }

    // Initialize the timer object.
    result = m_timer->Initialize();
    if(!result)
    {
        DebugPopup(L"Could not initialize TimerManager. Aborting.");
        return false;
    }

    // Create the assets object.
    m_assets = new AssetManager();
    if(!m_assets)
    {
        DebugPopup(L"Could not get instance of AssetManager. Aborting.");
        return false;
    }

    // Initialize the assets object.
    result = m_assets->Initialize();
    if(!result)
    {
        DebugPopup(L"Could not initialize AssetManager. Aborting.");
        return false;
    }

    // Create the lights object.
    m_lights = new LightManager();
    if(!m_lights)
    {
        DebugPopup(L"Could not get instance of LightManager. Aborting.");
        return false;
    }

    // Initialize the lights object.
    result = m_lights->Initialize();
    if(!result)
    {
        DebugPopup(L"Could not initialize LightManager. Aborting.");
        return false;
    }

    // Create the game object.
    m_game = new GameManager();
    if(!m_game)
    {
        DebugPopup(L"Could not get instance of GameManager. Aborting.");
        return false;
    }

    // Initialize the game object.
    result = m_game->Initialize();
    if(!result)
    {
        DebugPopup(L"Could not initialize GameManager. Aborting.");
        return false;
    }

    
    return true;
}


// |----------------------------------------------------------------------------|
// |                              Shutdown                                      |
// |----------------------------------------------------------------------------|
void SystemManager::Shutdown()
{

    // Release the assets object.
    if(m_assets)
    {
        m_assets->Shutdown();
        delete m_assets;
        m_assets = 0;
    }

    // Release the graphics object.
    if(m_graphics)
    {
        m_graphics->Shutdown();
        delete m_graphics;
        m_graphics = 0;
    }

    // Release the input object.
    if(m_input)
    {
        m_input->Shutdown();
        delete m_input;
        m_input = 0;
    }

    // Release the sound object.
    if(m_sound)
    {
        m_sound->Shutdown();
        delete m_sound;
        m_sound = 0;
    }

    // Release the timer object.
    if(m_timer)
    {
        m_timer->Shutdown();
        delete m_timer;
        m_timer = 0;
    }

    // Release the lights object.
    if(m_lights)
    {
        m_lights->Shutdown();
        delete m_lights;
        m_lights = 0;
    }

    // Release the game object.
    if(m_game)
    {
        m_game->Shutdown();
        delete m_game;
        m_game = 0;
    }

    // Shutdown the window.
    ShutdownWindows();

    return;
}


// |----------------------------------------------------------------------------|
// |                               Run                                          |
// |----------------------------------------------------------------------------|
void SystemManager::Run()
{
    MSG msg;
    bool done, result;


    // Initialize the message structure.
    ZeroMemory(&msg, sizeof(MSG));
    
    // Loop until there is a quit message from the window or the user.
    done = false;
    while(!done)
    {
        // Handle the windows messages.
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // If windows signals to end the application then exit out.
        if(msg.message == WM_QUIT)
        {
            done = true;
        }
        else
        {
            // Otherwise do the frame processing.
            result = Frame();
            if(!result)
            {
                done = true;
            }
        }

        // Check if the user pressed escape and wants to quit.
        if(m_input->GetButtonPressed(BUTTON_EXIT))
        {
            done = true;
        }

    }

    return;
}


// |----------------------------------------------------------------------------|
// |                               Frame                                        |
// |----------------------------------------------------------------------------|
bool SystemManager::Frame()
{
    bool result;

    // Do the input processing.
    result = m_input->Frame();
    if(!result)
    {
        return false;
    }

    // Process timer
    result = m_timer->Frame();
    if(!result)
    {
        return false;
    }

    // Process game logic
    result = m_game->Logic();
    if(!result)
    {
        return false;
    }

    // Process graphics
	result = m_graphics->BeginRender()
	      && m_game->Draw()
	      && m_graphics->EndRender();
    if(!result)
    {
        return false;
    }

    return true;
}


// |----------------------------------------------------------------------------|
// |                           MessageHandler                                   |
// |----------------------------------------------------------------------------|
LRESULT CALLBACK SystemManager::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
    return DefWindowProc(hwnd, umsg, wparam, lparam);
}


// |----------------------------------------------------------------------------|
// |                         InitializeWindows                                  |
// |----------------------------------------------------------------------------|
void SystemManager::InitializeWindows(int& screenWidth, int& screenHeight)
{
    WNDCLASSEX wc;
    DEVMODE dmScreenSettings;
    int posX, posY;


    // Get an external pointer to this object.    
    ApplicationHandle = this;

    // Get the instance of this application.
    m_hinstance = GetModuleHandle(NULL);

    // Give the application a name.
    m_applicationName = L"Engine";

    // Setup the windows class with default settings.
    wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = m_hinstance;
    wc.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
    wc.hIconSm       = wc.hIcon;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = m_applicationName;
    wc.cbSize        = sizeof(WNDCLASSEX);
    
    // Register the window class.
    RegisterClassEx(&wc);

    // Determine the resolution of the clients desktop screen.
    screenWidth  = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Setup the screen settings depending on whether it is running in full screen or in windowed mode.
    if(FULL_SCREEN)
    {
        // If full screen set the screen to maximum size of the users desktop and 32bit.
        memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
        dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
        dmScreenSettings.dmPelsWidth  = (unsigned long)screenWidth;
        dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
        dmScreenSettings.dmBitsPerPel = 32;            
        dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        // Change the display settings to full screen.
        ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

        // Set the position of the window to the top left corner.
        posX = posY = 0;
    }
    else
    {
        // If windowed then set it to 800x600 resolution.
        screenWidth  = 800;
        screenHeight = 600;

        // Place the window in the middle of the screen.
        posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth)  / 2;
        posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
    }
	
	SCREEN_WIDTH = screenWidth;
	SCREEN_HEIGHT = screenHeight;

    // Create the window with the screen settings and get the handle to it.
    windowHandle = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, 
                            WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
                            posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

    // Bring the window up on the screen and set it as main focus.
    ShowWindow(windowHandle, SW_SHOW);
    SetForegroundWindow(windowHandle);
    SetFocus(windowHandle);

    // Hide the mouse cursor.
    ShowCursor(false);

    return;
}


// |----------------------------------------------------------------------------|
// |                         ShutdownWindows                                    |
// |----------------------------------------------------------------------------|
void SystemManager::ShutdownWindows()
{
    // Show the mouse cursor.
    ShowCursor(true);

    // Fix the display settings if leaving full screen mode.
    if(FULL_SCREEN)
    {
        ChangeDisplaySettings(NULL, 0);
    }

    // Remove the window.
    DestroyWindow(windowHandle);
    windowHandle = NULL;

    // Remove the application instance.
    UnregisterClass(m_applicationName, m_hinstance);
    m_hinstance = NULL;

    // Release the pointer to this class.
    ApplicationHandle = NULL;

    return;
}


// |----------------------------------------------------------------------------|
// |                           WndProc                                          |
// |----------------------------------------------------------------------------|
LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
    switch(umessage)
    {
        // Check if the window is being destroyed.
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }

        // Check if the window is being closed.
        case WM_CLOSE:
        {
            PostQuitMessage(0);        
            return 0;
        }

        // All other messages pass to the message handler in the system class.
        default:
        {
            return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
        }
    }
}