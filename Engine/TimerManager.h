// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// TimerManager
//      Manages time keeping for the game.
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"
#include "Singleton.h"


// |----------------------------------------------------------------------------|
// |                            Class: GameManager                              |
// |----------------------------------------------------------------------------|
class TimerManager : public Singleton<TimerManager>
{
public:

    //|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
	TimerManager();
	TimerManager(const TimerManager&);
	~TimerManager();
    
    // Initialization and shutdown
    bool Initialize();
    void Shutdown();

    // Processes timers each frame
    bool Frame();

    // Getter functions
    float GetTime();
    
private:

    //|-------------------------------Private Functions-------------------------|

private:

    //|-----------------------------Private Data Members------------------------|
    
    // Screens
	INT64 m_frequency;
	float m_ticksPerMs;
	INT64 m_startTime;
	float m_frameTime;


};