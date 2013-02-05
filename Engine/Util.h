// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Util
//      Game-wide utilities.
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <Windows.h>


// |----------------------------------------------------------------------------|
// |                                 Globals                                    |
// |----------------------------------------------------------------------------|
static HWND windowHandle;

// |----------------------------------------------------------------------------|
// |                                Constants                                   |
// |----------------------------------------------------------------------------|
enum DEBUG_TYPE {           GENERAL,    COLLISION,  GRAPHICS,   NUM_DEBUGS};
const int DEBUG_MODE[] = {  1,          1,          1 };


// |----------------------------------------------------------------------------|
// |                            Function Prototypes                             |
// |----------------------------------------------------------------------------|
void DebugLog(const char* msg, DEBUG_TYPE type=GENERAL, int level=1);
void DebugPopup(const wchar_t* msg, DEBUG_TYPE type=GENERAL, int level=1);