// Solar Sojourn
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
// |                           Default Constructor                              |
// |----------------------------------------------------------------------------|
GameManager::GameManager() :
    m_screens(0),
    m_currentScreen(0)
{
}


// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
GameManager::GameManager(const GameManager& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
GameManager::~GameManager()
{
}


// |----------------------------------------------------------------------------|
// |                              Initialize                                    |
// |----------------------------------------------------------------------------|
bool GameManager::Initialize()
{
    bool result;
    
    // Initialize screens
    m_screens = new Screen* [NUM_SCREENS];
    for (int i = 0 ; i < NUM_SCREENS; ++i) {
        m_screens[i] = NULL;
    }
    m_screens[SCREEN_TITLE] = new TitleScreen();
    m_screens[SCREEN_TITLE]->Initialize();
    m_screens[SCREEN_LEVEL] = new LevelScreen();
    m_screens[SCREEN_LEVEL]->Initialize();
    m_currentScreen = m_screens[SCREEN_TITLE];
    result = m_currentScreen->OnLoad();

    return true;
}


// |----------------------------------------------------------------------------|
// |                              Shutdown                                      |
// |----------------------------------------------------------------------------|
void GameManager::Shutdown()
{

    // Screen Cleanup
    if (m_screens) {
        for (int i = 0 ; i < NUM_SCREENS; ++i) {
            delete m_screens[i];
        }
        delete m_screens;
        m_screens = 0;
    }
    m_currentScreen = 0;

    return;
}


// |----------------------------------------------------------------------------|
// |                               Logic                                        |
// |----------------------------------------------------------------------------|
bool GameManager::Logic()
{
    bool result;

    // Check if we need to change screens
    if (m_currentScreen->IsDone()) {

        // Perform onExit functions for the old screen
        result = m_currentScreen->OnExit();
        if (!result)
            return false;

        // Check if the screen is telling the game to quit.
        if (m_currentScreen->GetNextScreen() == SCREEN_QUIT) {
            // If so, quit.
            return true;
        }

        // If the screen is NOT telling the game to quit, load the next screen
        else {
            // Set the new screen as current
            m_currentScreen = m_screens[m_currentScreen->GetNextScreen()];
            // Perform onLoad functions for the new screen
            result = m_currentScreen->OnLoad();
            if(!result)
                return false;
        }

    }
    
    // Perform game logic for current screen
    result = m_currentScreen->Logic();
    if (!result)
        return false;

    return true;
}


// |----------------------------------------------------------------------------|
// |                               Draw                                         |
// |----------------------------------------------------------------------------|
bool GameManager::Draw()
{
    bool result;

    // Send game objects in screen to be rendered
    result = m_currentScreen->Draw();
    if (!result)
        return false;

    return true;
}