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
#include "Singleton.h"
#include "InputManager.h"
#include "GraphicsManager.h"
#include "GameManager.h"
#include "TimerManager.h"
#include "AssetManager.h"
//#include "SoundManager.h"


// |----------------------------------------------------------------------------|
// |                            Class: SystemManager                            |
// |----------------------------------------------------------------------------|
class SystemManager : public Singleton<SystemManager>
{
public:

    //|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
	SystemManager();
	SystemManager(const SystemManager&);
	~SystemManager();
    
    // Initialization and shutdown
    bool Initialize();
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

    //|-----------------------------Private Data Members------------------------|

    // Windows parameters
    LPCWSTR m_applicationName;
    HINSTANCE m_hinstance;

    // Input Manager
    InputManager* m_input;

    // Graphics Manager
    GraphicsManager* m_graphics;  

    // Sound Manager
    //SoundManager* m_sound;

    // Timer Manager
    TimerManager* m_timer;

    // Game Manager
    GameManager* m_game;

    // Asset Manager
    AssetManager* m_assets;
};


// |----------------------------------------------------------------------------|
// |                                 Globals                                    |
// |----------------------------------------------------------------------------|
static SystemManager* ApplicationHandle = 0;


// |----------------------------------------------------------------------------|
// |                           Function Prototypes                              |
// |----------------------------------------------------------------------------|
static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

