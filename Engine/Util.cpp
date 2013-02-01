// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Util
//      Game-wide utilities.

// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"


// |----------------------------------------------------------------------------|
// |                                debug_log                                   |
// |----------------------------------------------------------------------------|
void debug_log(const char* msg, DEBUG_TYPE type, int level) 
{ 
    if (level <= DEBUG_MODE[type])
    {
        OutputDebugStringA(msg);
        OutputDebugStringA("\n");
    }
}


// |----------------------------------------------------------------------------|
// |                               debug_popup                                  |
// |----------------------------------------------------------------------------|
void debug_popup(const char* msg, HWND hwnd, DEBUG_TYPE type, int level) 
{ 
    if (level <= DEBUG_MODE[type])
    {
        MessageBox(hwnd, L"Could not initialize Direct Sound.", L"Error", MB_OK);
    }
}