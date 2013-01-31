// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// SystemManager
//      Contains management classes for game objects, graphics, and input.
//      Runs main game loop and calls sub loops.
#pragma once

// TODO: Make this singleton


// |----------------------------------------------------------------------------|
// |                        Pre-Processing Directives                           |
// |----------------------------------------------------------------------------|
#define WIN32_LEAN_AND_MEAN


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <windows.h>
//#include "inputclass.h"
//#include "graphicsclass.h"
//#include "fpsclass.h"
//#include "cpuclass.h"
//#include "timerclass.h"
//#include "positionclass.h"
//#include "soundclass.h"


// |----------------------------------------------------------------------------|
// |                            Class: SystemClass                              |
// |----------------------------------------------------------------------------|
class SystemManager
{
public:

    //|-------------------------------Public Functions--------------------------|

    // Constructors and Destructors
    SystemManager();
    SystemManager(const SystemManager&);
    ~SystemManager();

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

    // Processes each frame (calles input, game, render frame functions)
    bool Frame();

    // Performs Windows initialization tasks
    void InitializeWindows(int& screenWidth, int& screenHeight);

    // Performs Windows shutdown tasks
    void ShutdownWindows();

private:

    // Windows parameters
    LPCWSTR m_applicationName;
    HINSTANCE m_hinstance;
    HWND m_hwnd;

    // Input handler
    //InputClass* m_Input;

    // Graphics handler
    //GraphicsClass* m_Graphics;    
    
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

