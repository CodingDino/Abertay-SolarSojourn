// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// InputManager
//      Gets and processes input to be made available for game class to use in 
//      game logic.
#pragma once

// |----------------------------------------------------------------------------|
// |                        Pre-Processing Directives                           |
// |----------------------------------------------------------------------------|
#define DIRECTINPUT_VERSION 0x0800
#define KEY_PRESSED 0x80


// |----------------------------------------------------------------------------|
// |                                 Linking                                    |
// |----------------------------------------------------------------------------|
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <dinput.h>
#include "Util.h"
#include "Singleton.h"


// |----------------------------------------------------------------------------|
// |                                Constants                                   |
// |----------------------------------------------------------------------------|
enum BUTTON_IDENT {
	BUTTON_FORWARD,		// Moves player forward
	BUTTON_BACKWARD,	// Moves player backward
	BUTTON_STRAFE_LEFT,	// Moves player left
	BUTTON_STRAFE_RIGHT,// Moves player right
	BUTTON_ASCEND,	    // Moves player left
	BUTTON_DESCEND,     // Moves player right
    BUTTON_EXIT,        // Exits the game
    NUM_BUTTONS         // Number of buttons that can be bound
};


// |----------------------------------------------------------------------------|
// |                           Class: InputClass                                |
// |----------------------------------------------------------------------------|
class InputManager : public Singleton<InputManager>
{
public:

    //|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
	InputManager();
	InputManager(const InputManager&);
	~InputManager();
    
    // Initialization and shutdown
    bool Initialize(HINSTANCE hinstance, int screenWidth, int screenHeight);
    void Shutdown();
    
    // Gets input and processes it
    bool Frame();

    // Key press checks
    bool GetButtonDown(BUTTON_IDENT toCheck);
    bool GetButtonPressed(BUTTON_IDENT toCheck);
    bool GetButtonReleased(BUTTON_IDENT toCheck);

    // Gets mouse information
    void GetMouseLocation(int& mouseX, int& mouseY);
    void GetMouseChange(int& mouseX, int& mouseY);
	bool IsMouseButtonDown(int button) {if (button >= 0 && button < 4) return m_mouseDown; else return false;}
	bool IsMouseButtonPressed(int button) {if (button >= 0 && button < 4) return m_mousePressed; else return false;}


private:

    //|-------------------------------Private Functions-------------------------|

    // Read the current state of the keyboard
    bool ReadKeyboard();

    // Read the current state of the mouse
    bool ReadMouse();

    // Process the changes in the mouse and keyboard
    void ProcessInput();

private:

    //|-----------------------------Private Data Members------------------------|

    // Pointers to mouse, keyboard, input
    IDirectInput8* m_directInput;
    IDirectInputDevice8* m_keyboard;
    IDirectInputDevice8* m_mouse;

    // States for mouse and keyboard
    unsigned char m_keyboardState[256];
    unsigned char m_keyboardStateLast[256];
    DIMOUSESTATE m_mouseState;

    // screen dimensions for use with mouse
    int m_screenWidth, m_screenHeight;

    // mouse information
    int m_mouseX, m_mouseY;
    int m_mouseChangeX, m_mouseChangeY;
	bool m_mouseDown, m_mousePressed;

    // Keybindings
    int m_keybindings[NUM_BUTTONS];
};