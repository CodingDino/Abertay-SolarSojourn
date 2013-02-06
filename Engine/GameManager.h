// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// GameManager
//      Manages game screens and game logic within those screens.
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"


// |----------------------------------------------------------------------------|
// |                            Class: GameManager                              |
// |----------------------------------------------------------------------------|
class GameManager
{
public:

    //|-------------------------------Public Functions--------------------------|
    
    // Returns instance
    static GameManager* GetInstance();

    // Initializes the DirectX interface
    bool Initialize();

    // Performs shutdown, deallocation, and cleanup
    void Shutdown();
    
private:

    //|-------------------------------Private Functions-------------------------|
    
    // Constructors and Destructors
    GameManager();

private:

    //|-----------------------------Private Data Members------------------------|
    
    // Singleton instance
    static GameManager* s_instance;

};