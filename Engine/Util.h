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
// |                                Constants                                   |
// |----------------------------------------------------------------------------|
enum DEBUG_TYPE {           DB_GENERAL, DB_COLLISION,   DB_LOGIC,   DB_GRAPHICS,   NUM_DEBUGS};
const int DEBUG_MODE[] = {  1,          1,              1,          1 };
enum SCREEN {SCREEN_TITLE, SCREEN_HOWTO, SCREEN_OVERWORLD, NUM_SCREENS, 
    SCREEN_QUIT};


// |----------------------------------------------------------------------------|
// |								 Globals									|
// |----------------------------------------------------------------------------|
extern HWND windowHandle;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern float SCALE_X;
extern float SCALE_Y;


// |----------------------------------------------------------------------------|
// |                            Function Prototypes                             |
// |----------------------------------------------------------------------------|
void DebugLog(const char* msg, DEBUG_TYPE type=DB_GENERAL, int level=1);
void DebugPopup(const wchar_t* msg, DEBUG_TYPE type=DB_GENERAL, int level=1);
double Clamp(double val, double min, double max);