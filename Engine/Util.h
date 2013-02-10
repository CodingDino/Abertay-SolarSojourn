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
extern HWND windowHandle;


// |----------------------------------------------------------------------------|
// |                                Constants                                   |
// |----------------------------------------------------------------------------|
enum DEBUG_TYPE {           DB_GENERAL, DB_COLLISION,   DB_GRAPHICS,   NUM_DEBUGS};
const int DEBUG_MODE[] = {  1,          1,              1 };
enum SCREEN {SCREEN_TITLE, SCREEN_HOW_TO, SCREEN_OVERWORLD, NUM_SCREENS, 
    SCREEN_QUIT};
enum LAYER {LAYER_BACKGROUND, LAYER_OVERLAY, NUM_LAYERS};


// |----------------------------------------------------------------------------|
// |                            Function Prototypes                             |
// |----------------------------------------------------------------------------|
void DebugLog(const char* msg, DEBUG_TYPE type=DB_GENERAL, int level=1);
void DebugPopup(const wchar_t* msg, DEBUG_TYPE type=DB_GENERAL, int level=1);