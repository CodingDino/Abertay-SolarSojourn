// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// GameManager
//      Manages game screens and game logic within those screens.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "GameManager.h"

// |----------------------------------------------------------------------------|
// |                                 Globals                                    |
// |----------------------------------------------------------------------------|
GameManager* GameManager::s_instance = 0;


// |----------------------------------------------------------------------------|
// |                           Default Constructor                              |
// |----------------------------------------------------------------------------|
GameManager::GameManager()
{
}


// |----------------------------------------------------------------------------|
// |                              GetInstance                                   |
// |----------------------------------------------------------------------------|
GameManager* GameManager::GetInstance()
{
    if (s_instance == 0)
        s_instance = new GameManager;
    return s_instance;
}


// |----------------------------------------------------------------------------|
// |                              Initialize                                    |
// |----------------------------------------------------------------------------|
bool GameManager::Initialize()
{

    return true;
}


// |----------------------------------------------------------------------------|
// |                              Shutdown                                      |
// |----------------------------------------------------------------------------|
void GameManager::Shutdown()
{
    
    // Kill instance
    delete s_instance;
    s_instance = 0;

    return;
}