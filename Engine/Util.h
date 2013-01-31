// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Util
//		Game-wide utilities.
#pragma once


// |----------------------------------------------------------------------------|
// |								Constants									|
// |----------------------------------------------------------------------------|
enum DEBUG_TYPE {			GENERAL,	COLLISION,	GRAPHICS,	NUM_DEBUGS};
const int DEBUG_MODE[] = {	1,			1,			1 };

// |----------------------------------------------------------------------------|
// |							Function Prototypes								|
// |----------------------------------------------------------------------------|
void debug_log(const char* msg, DEBUG_TYPE type=GENERAL, int level=1);
void debug_popup(const char* msg, HWND hwnd, DEBUG_TYPE type=GENERAL, int level=1);