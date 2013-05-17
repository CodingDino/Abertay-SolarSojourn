// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Main
//      Program wrapper.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "SystemManager.h"


// |----------------------------------------------------------------------------|
// |                                 WinMain                                    |
// |----------------------------------------------------------------------------|
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
    SystemManager* system;
    bool result;
    
    
    // Create the system object.
    system = new SystemManager();
    if(!system)
    {
        return 0;
    }

    // Initialize and run the system object.
    result = system->Initialize();
    if(result)
    {
        system->Run();
    }

    // Shutdown and release the system object.
    system->Shutdown();
    delete system;
    system = 0;

    return 0;
}