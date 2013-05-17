// Solar Sojourn
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
// |								 Globals									|
// |----------------------------------------------------------------------------|
HWND windowHandle;
int SCREEN_WIDTH;
int SCREEN_HEIGHT;
float SCALE_X;
float SCALE_Y;


// |----------------------------------------------------------------------------|
// |                                debug_log                                   |
// |----------------------------------------------------------------------------|
void DebugLog(const char* msg, DEBUG_TYPE type, int level) 
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
void DebugPopup(const wchar_t* msg, DEBUG_TYPE type, int level) 
{ 
    if (level <= DEBUG_MODE[type])
    {
        MessageBox(windowHandle, msg, L"Error", MB_OK);
    }
}


// |----------------------------------------------------------------------------|
// |                                  Clamp                                     |
// |----------------------------------------------------------------------------|
double Clamp(double val, double min, double max)
{ 
    return min(max(val,min),max);
}