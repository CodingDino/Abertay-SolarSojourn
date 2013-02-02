// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// SystemManager
//      Contains management classes for game objects, graphics, and input.
//      Runs main game loop and calls sub loops.
#pragma once


// |----------------------------------------------------------------------------|
// |                        Pre-Processing Directives                           |
// |----------------------------------------------------------------------------|
#define WIN32_LEAN_AND_MEAN


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <windows.h>
#include "InputManager.h"
#include "GraphicsManager.h"
//#include "fpsclass.h"
//#include "cpuclass.h"
//#include "timerclass.h"
//#include "positionclass.h"
//#include "soundclass.h"


// |----------------------------------------------------------------------------|
// |                            Class: SystemManager                            |
// |----------------------------------------------------------------------------|
class SystemManager
{
public:

    //|-------------------------------Public Functions--------------------------|

    // Returns instance
    static SystemManager* GetInstance();

    // Initialize all data members
    bool Initialize();

    // Release all data members
    void Shutdown();

    // Run the game (contains main game loop)
    void Run();

    // Handles system messages
    LRESULT CALLBACK MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

private:

    //|-------------------------------Private Functions-------------------------|

    // Constructors and Destructors
    SystemManager();
    SystemManager(const SystemManager&);
    ~SystemManager();

    // Processes each frame (calles input, game, render frame functions)
    bool Frame();

    // Performs Windows initialization tasks
    void InitializeWindows(int& screenWidth, int& screenHeight);

    // Performs Windows shutdown tasks
    void ShutdownWindows();

private:

    //|-----------------------------Private Data Members------------------------|

    // Singleton instance
    static SystemManager* s_instance;

    // Windows parameters
    LPCWSTR m_applicationName;
    HINSTANCE m_hinstance;
    HWND m_hwnd;

    // Input handler
    InputManager* m_input;

    // Graphics handler
    GraphicsManager* m_graphics;    
    
    // Timing classes
    //FpsClass* m_Fps;
    //CpuClass* m_Cpu;
    //TimerClass* m_Timer;

    // Player position
    //PositionClass* m_Position;

    // Sound
    //SoundClass* m_Sound;
};


// |----------------------------------------------------------------------------|
// |                                 Globals                                    |
// |----------------------------------------------------------------------------|
static SystemManager* ApplicationHandle = 0;


// |----------------------------------------------------------------------------|
// |                           Function Prototypes                              |
// |----------------------------------------------------------------------------|
static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

