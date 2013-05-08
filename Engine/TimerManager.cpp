// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// TimerManager
//      Manages time keeping for the game.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "TimerManager.h"


// |----------------------------------------------------------------------------|
// |                           Default Constructor                              |
// |----------------------------------------------------------------------------|
TimerManager::TimerManager() :
    m_frequency(0),
    m_ticksPerMs(0),
    m_startTime(0),
    m_frameTime(0),
    m_frameCount(0),
    m_fps(0),
    m_fpsCurrentTime(0)
{
}


// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
TimerManager::TimerManager(const TimerManager& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
TimerManager::~TimerManager()
{
}


// |----------------------------------------------------------------------------|
// |                              Initialize                                    |
// |----------------------------------------------------------------------------|
bool TimerManager::Initialize()
{
	// Check to see if this system supports high performance timers.
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	if(m_frequency == 0)
	{
		return false;
	}

	// Find out how many times the frequency counter ticks every millisecond.
	m_ticksPerMs = (float)(m_frequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);
	
	// Initialize fps start time
	m_fpsCurrentTime = 0;

	return true;
}


// |----------------------------------------------------------------------------|
// |                              Shutdown                                      |
// |----------------------------------------------------------------------------|
void TimerManager::Shutdown()
{

}


// |----------------------------------------------------------------------------|
// |						        Frame										|
// |----------------------------------------------------------------------------|
bool TimerManager::Frame()
{
	INT64 currentTime;
	float timeDifference;


	QueryPerformanceCounter((LARGE_INTEGER*)& currentTime);

	timeDifference = (float)(currentTime - m_startTime);

	m_frameTime = timeDifference / m_ticksPerMs;

	m_startTime = currentTime;
	
	// FPS calculations
	m_frameCount++;
	m_fpsCurrentTime += m_frameTime;

	if(m_fpsCurrentTime >= 1000)
	{
		m_fps = m_frameCount;
		m_frameCount = 0;
		
		m_fpsCurrentTime = 0;
	}

	return true;
}