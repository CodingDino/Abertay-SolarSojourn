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
    //m_Input(0),
    m_graphics(0)
    //m_Fps(0),
    //m_Cpu(0),
    //m_Timer(0),
    //m_Position(0),
    //m_Sound(0)
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

    // Create the fps object.
    //m_Fps = new FpsClass;
    //if(!m_Fps)
    //{
    //    return false;
    //}

    // Initialize the fps object.
    //m_Fps->Initialize();

    // Create the cpu object.
    //m_Cpu = new CpuClass;
    //if(!m_Cpu)
    //{
    //    return false;
    //}

    // Initialize the cpu object.
    //m_Cpu->Initialize();

    // Create the timer object.
    //m_Timer = new TimerClass;
    //if(!m_Timer)
    //{
    //    return false;
    //}

    // Initialize the timer object.
    //result = m_Timer->Initialize();
    //if(!result)
    //{
    //    MessageBox(s_hwnd, L"Could not initialize the Timer object.", L"Error", MB_OK);
    //    return false;
    //}

    // Create the position object.
    //m_Position = new PositionClass;
    //if(!m_Position)
    //{
    //    return false;
    //}

    // Create the sound object.
    //m_Sound = new SoundClass;
    //if(!m_Sound)
    //{
    //    return false;
    //}
 
    // Initialize the sound object.
    //result = m_Sound->Initialize(s_hwnd);
    //if(!result)
    //{
    //    MessageBox(s_hwnd, L"Could not initialize Direct Sound.", L"Error", MB_OK);
    //    return false;
    //}
    //m_Sound->StartMusic();
    
    return true;
}


// |----------------------------------------------------------------------------|
// |                              Shutdown                                      |
// |----------------------------------------------------------------------------|
void SystemManager::Shutdown()
{
    //// Release the position object.
    //if(m_Position)
    //{
    //    delete m_Position;
    //    m_Position = 0;
    //}

    //// Release the timer object.
    //if(m_Timer)
    //{
    //    delete m_Timer;
    //    m_Timer = 0;
    //}

    //// Release the cpu object.
    //if(m_Cpu)
    //{
    //    m_Cpu->Shutdown();
    //    delete m_Cpu;
    //    m_Cpu = 0;
    //}

    //// Release the fps object.
    //if(m_Fps)
    //{
    //    delete m_Fps;
    //    m_Fps = 0;
    //}

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

    //// Release the sound object.
    //if(m_Sound)
    //{
    //    m_Sound->Shutdown();
    //    delete m_Sound;
    //    m_Sound = 0;
    //}

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
    int mouseX, mouseY;
    //bool keyDown;
    //Coord camera_position;
    //Coord camera_rotation;

    // Do the input processing.
    result = m_input->Frame();
    if(!result)
    {
        return false;
    }

    // Set the frame time for calculating the updated position.
    //m_Position->SetFrameTime(m_Timer->GetTime());

    //// Use the input to determine camera position.
    //// Rotate left
    //keyDown = m_Input->IsAPressed();
    //m_Position->TurnLeft(keyDown);
    //// Rotate right
    //keyDown = m_Input->IsDPressed();
    //m_Position->TurnRight(keyDown);
    //// Rotate up
    //keyDown = m_Input->IsWPressed();
    //m_Position->TurnUp(keyDown);
    //// Rotate down
    //keyDown = m_Input->IsSPressed();
    //m_Position->TurnDown(keyDown);
    //// Roll left
    //keyDown = m_Input->IsQPressed();
    //m_Position->RollLeft(keyDown);
    //// Roll right
    //keyDown = m_Input->IsEPressed();
    //m_Position->RollRight(keyDown);
    //// Move left
    //keyDown = m_Input->IsLeftArrowPressed();
    //m_Position->MoveLeft(keyDown);
    //// Move right
    //keyDown = m_Input->IsRightArrowPressed();
    //m_Position->MoveRight(keyDown);
    //// Move forward
    //keyDown = m_Input->IsUpArrowPressed();
    //m_Position->MoveForward(keyDown);
    //// Move backwards
    //keyDown = m_Input->IsDownArrowPressed();
    //m_Position->MoveBackward(keyDown);
    //// Move up
    //keyDown = m_Input->IsSpacePressed();
    //m_Position->MoveUp(keyDown);
    //// Move down
    //keyDown = m_Input->IsLeftControlPressed();
    //m_Position->MoveDown(keyDown);

    //// Sound effect
    //if (m_Input->IsMPressed()) m_Sound->Mute();
    //if (m_Input->IsNPressed()) m_Sound->UnMute();
    //if (m_Input->IsMovementPressed()) m_Sound->StartShipEngine();
    //else  m_Sound->StopShipEngine();
    //m_Sound->Frame(m_Timer->GetTime());

    //// Get coordinates and rotation from position object
    //m_Position->GetRotation(camera_rotation.x, camera_rotation.y, camera_rotation.z);
    //m_Position->GetPosition(camera_position.x, camera_position.y, camera_position.z);

    // Get the location of the mouse from the input object,
    m_input->GetMouseLocation(mouseX, mouseY);

    //// Update the system timers.
    //m_Timer->Frame();
    //m_Fps->Frame();
    //m_Cpu->Frame();

    //// Decide if we need to transfer to a new screen
    //bool transfer = m_Input->IsSpacePressed();

    //// Do the frame processing for the graphics object.
    //result = m_Graphics->Frame(mouseX, mouseY, m_Fps->GetFps(), 
    //    m_Cpu->GetCpuPercentage(), m_Timer->GetTime(), camera_rotation, 
    //    camera_position, transfer);
    //if(!result)
    //{
    //    return false;
    //}

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
    //if(FULL_SCREEN)
    //{
    //    ChangeDisplaySettings(NULL, 0);
    //}

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