// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// InputManager
//      Gets and processes input to be made available for game class to use in 
//      game logic.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "InputManager.h"


// |----------------------------------------------------------------------------|
// |                           Default Constructor                              |
// |----------------------------------------------------------------------------|
InputManager::InputManager() :
    m_directInput(0),
    m_keyboard(0),
    m_mouse(0),
	m_mouseDown(false),
	m_mousePressed(false)
{
}


// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
InputManager::InputManager(const InputManager& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
InputManager::~InputManager()
{
}


// |----------------------------------------------------------------------------|
// |                              Initialize                                    |
// |----------------------------------------------------------------------------|
bool InputManager::Initialize(HINSTANCE hinstance, int screenWidth, int screenHeight)
{
    HRESULT result;

    // Set default keybindings
    m_keybindings[BUTTON_EXIT] = DIK_ESCAPE;
    m_keybindings[BUTTON_FORWARD] = DIK_W;
    m_keybindings[BUTTON_BACKWARD] = DIK_S;
    m_keybindings[BUTTON_STRAFE_LEFT] = DIK_A;
    m_keybindings[BUTTON_STRAFE_RIGHT] = DIK_D;
    m_keybindings[BUTTON_ASCEND] = DIK_SPACE;
    m_keybindings[BUTTON_DESCEND] = DIK_LMENU;

    // Store the screen size which will be used for positioning the mouse cursor.
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;

    // Initialize the location of the mouse on the screen.
    m_mouseX = 0;
    m_mouseY = 0;

    // Initialize keyboard states to 0
    for (int i=0; i < 256; ++i)
    {
        m_keyboardState[i] = 0;
        m_keyboardStateLast[i] = 0;
    }

    // Initialize the main direct input interface.
    result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
    if(FAILED(result))
    {
        DebugPopup(L"DirectInput8Create failed.");
        return false;
    }

    // Initialize the direct input interface for the keyboard.
    result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
    if(FAILED(result))
    {
        DebugPopup(L"CreateDevice for keyboard failed.");
        return false;
    }

    // Set the data format.  In this case since it is a keyboard we can use the predefined data format.
    result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
    if(FAILED(result))
    {
        DebugPopup(L"SetDataFormat for keyboard failed.");
        return false;
    }

    // Set the cooperative level of the keyboard to not share with other programs.
    result = m_keyboard->SetCooperativeLevel(windowHandle, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
    if(FAILED(result))
    {
        DebugPopup(L"SetCooperativeLevel for keyboard failed.");
        return false;
    }

    // Now acquire the keyboard.
    result = m_keyboard->Acquire();
    if(FAILED(result))
    {
        DebugPopup(L"Acquire for keyboard failed.");
        return false;
    }

    // Initialize the direct input interface for the mouse.
    result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
    if(FAILED(result))
    {
        DebugPopup(L"CreateDevice for mouse failed.");
        return false;
    }

    // Set the data format for the mouse using the pre-defined mouse data format.
    result = m_mouse->SetDataFormat(&c_dfDIMouse);
    if(FAILED(result))
    {
        DebugPopup(L"SetDataFormat for mouse failed.");
        return false;
    }

    // Set the cooperative level of the mouse to share with other programs.
    result = m_mouse->SetCooperativeLevel(windowHandle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    if(FAILED(result))
    {
        DebugPopup(L"SetCooperativeLevel for mouse failed.");
        return false;
    }

    // Acquire the mouse.
    result = m_mouse->Acquire();
    if(FAILED(result))
    {
        DebugPopup(L"Acquire for mouse failed.");
        return false;
    }

    return true;
}


// |----------------------------------------------------------------------------|
// |                              Shutdown                                      |
// |----------------------------------------------------------------------------|
void InputManager::Shutdown()
{
    // Release the mouse.
    if(m_mouse)
    {
        m_mouse->Unacquire();
        m_mouse->Release();
        m_mouse = 0;
    }

    // Release the keyboard.
    if(m_keyboard)
    {
        m_keyboard->Unacquire();
        m_keyboard->Release();
        m_keyboard = 0;
    }

    // Release the main interface to direct input.
    if(m_directInput)
    {
        m_directInput->Release();
        m_directInput = 0;
    }

    return;
}


// |----------------------------------------------------------------------------|
// |                               Frame                                        |
// |----------------------------------------------------------------------------|
bool InputManager::Frame()
{
    bool result;


    // Read the current state of the keyboard.
    result = ReadKeyboard();
    if(!result)
    {
        return false;
    }

    // Read the current state of the mouse.
    result = ReadMouse();
    if(!result)
    {
        return false;
    }

    // Process the changes in the mouse and keyboard.
    ProcessInput();

    return true;
}


// |----------------------------------------------------------------------------|
// |                            ReadKeyboard                                    |
// |----------------------------------------------------------------------------|
bool InputManager::ReadKeyboard()
{
    HRESULT result;

    // Copy previous keyboard state
    for (int i=0; i < 256; ++i)
    {
        m_keyboardStateLast[i] = m_keyboardState[i];
    }

    // Read the keyboard device.
    result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
    if(FAILED(result))
    {
        // If the keyboard lost focus or was not acquired then try to get control back.
        if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
        {
            m_keyboard->Acquire();
        }
        else
        {
            return false;
        }
    }
        
    return true;
}


// |----------------------------------------------------------------------------|
// |                              ReadMouse                                     |
// |----------------------------------------------------------------------------|
bool InputManager::ReadMouse()
{
    HRESULT result;


    // Read the mouse device.
    result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
    if(FAILED(result))
    {
        // If the mouse lost focus or was not acquired then try to get control back.
        if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
        {
            m_mouse->Acquire();
        }
        else
        {
            return false;
        }
    }

    return true;
}


// |----------------------------------------------------------------------------|
// |                             ProcessInput                                   |
// |----------------------------------------------------------------------------|
void InputManager::ProcessInput()
{
    // Update the location of the mouse cursor based on the change of the mouse location during the frame.
    m_mouseX += m_mouseState.lX;
    m_mouseY += m_mouseState.lY;
    m_mouseChangeX = m_mouseState.lX;
    m_mouseChangeY = m_mouseState.lY;
    if(m_mouseState.lX || m_mouseState.lY)
	    DebugLog ("InputManager: Mouse movement detected", DB_LOGIC, 10);

    // Ensure the mouse location doesn't exceed the screen width or height.
	// NOTE: Will still record movement outside the screen as mouseChange
    if(m_mouseX < 0)  { m_mouseX = 0; }
    if(m_mouseY < 0)  { m_mouseY = 0; }
    
    if(m_mouseX > m_screenWidth)  { m_mouseX = m_screenWidth; }
    if(m_mouseY > m_screenHeight) { m_mouseY = m_screenHeight; }
    
	// Update mouse status
	if (!m_mouseDown && (bool)m_mouseState.rgbButtons[0])
		m_mousePressed = true;
	if (m_mouseDown)
		m_mousePressed = false;
	if (!(bool)m_mouseState.rgbButtons[0])
		m_mousePressed = false;
	m_mouseDown = (bool)m_mouseState.rgbButtons[0];

    return;
}


// |----------------------------------------------------------------------------|
// |                           GetMouseLocation                                 |
// |----------------------------------------------------------------------------|
void InputManager::GetMouseLocation(int& mouseX, int& mouseY)
{
    mouseX = m_mouseX;
    mouseY = m_mouseY;
    return;
}


// |----------------------------------------------------------------------------|
// |                            GetMouseChange                                  |
// |----------------------------------------------------------------------------|
void InputManager::GetMouseChange(int& mouseX, int& mouseY)
{
    mouseX = m_mouseChangeX;
    mouseY = m_mouseChangeY;
    return;
}


// |----------------------------------------------------------------------------|
// |                           GetButtonDown                                    |
// |----------------------------------------------------------------------------|
bool InputManager::GetButtonDown(BUTTON_IDENT toCheck)
{
    unsigned char state = m_keyboardState[(m_keybindings[toCheck])];
    if (state & KEY_PRESSED)
        return true;
    else return false;
}


// |----------------------------------------------------------------------------|
// |                           GetButtonPressed                                 |
// |----------------------------------------------------------------------------|
bool InputManager::GetButtonPressed(BUTTON_IDENT toCheck)
{
    unsigned char state = m_keyboardState[(m_keybindings[toCheck])];
    unsigned char stateLast = m_keyboardStateLast[(m_keybindings[toCheck])];
    if ( (state & KEY_PRESSED) && !(stateLast & KEY_PRESSED) )
        return true;
    else return false;
}


// |----------------------------------------------------------------------------|
// |                           GetButtonReleased                                 |
// |----------------------------------------------------------------------------|
bool InputManager::GetButtonReleased(BUTTON_IDENT toCheck)
{
    unsigned char state = m_keyboardState[(m_keybindings[toCheck])];
    unsigned char stateLast = m_keyboardStateLast[(m_keybindings[toCheck])];
    if ( !(state & KEY_PRESSED) && (stateLast & KEY_PRESSED) )
        return true;
    else return false;
}

