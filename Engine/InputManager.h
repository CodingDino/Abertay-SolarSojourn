// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// InputManager
//      Gets and processes input to be made available for game class to use in 
//      game logic.
#pragma once

// TODO: Set up keybindings

// |----------------------------------------------------------------------------|
// |                        Pre-Processing Directives                           |
// |----------------------------------------------------------------------------|
#define DIRECTINPUT_VERSION 0x0800


// |----------------------------------------------------------------------------|
// |                                 Linking                                    |
// |----------------------------------------------------------------------------|
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <dinput.h>


// |----------------------------------------------------------------------------|
// |                                Constants                                   |
// |----------------------------------------------------------------------------|
enum BUTTON_IDENT {
    BUTTON_EXIT,        // Exits the game
    NUM_BUTTONS         // Number of buttons that can be bound
};


// |----------------------------------------------------------------------------|
// |                           Class: InputClass                                |
// |----------------------------------------------------------------------------|
class InputManager
{
public:

    //|-------------------------------Public Functions--------------------------|

    // Returns instance
    static InputManager* GetInstance();
    
    // Initializes mouse and keyboard settings
    bool Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight);
    
    // Performs shutdown, deallocation, and cleanup for input objects
    void Shutdown();
    
    // Gets input and processes it
    bool Frame();

    // Key press checks

    // Gets mouse position
    void GetMouseLocation(int& mouseX, int& mouseY);

private:

    //|-------------------------------Private Functions-------------------------|

    // Constructors and Destructors
    InputManager();
    InputManager(const InputManager&);
    ~InputManager();

    // Read the current state of the keyboard
    bool ReadKeyboard();

    // Read the current state of the mouse
    bool ReadMouse();

    // Process the changes in the mouse and keyboard
    void ProcessInput();

private:

    //|-----------------------------Private Data Members------------------------|

    // Singleton instance
    static InputManager* s_instance;

    // Pointers to mouse, keyboard, input
    IDirectInput8* m_directInput;
    IDirectInputDevice8* m_keyboard;
    IDirectInputDevice8* m_mouse;

    // States for mouse and keyboard
    unsigned char m_keyboardState[256];
    DIMOUSESTATE m_mouseState;

    // screen dimensions for use with mouse
    int m_screenWidth, m_screenHeight;

    // mouse coordinates
    int m_mouseX, m_mouseY;
};