// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Planet
//      GameObject class that handles planet orbiting.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Planet.h"


// |----------------------------------------------------------------------------|
// |							   Constructor									|
// |----------------------------------------------------------------------------|
Planet::Planet() :
    m_orbitCenterObject(0),
    m_orbitRadius(0),
    m_orbitSpeed(0),
    m_orbitTilt(0),
    m_orbitAngle(0),
    GameObject()
{
	DebugLog ("Planet: object instantiated.");
}
     

// |----------------------------------------------------------------------------|
// |							  Copy Constructor								|
// |----------------------------------------------------------------------------|
Planet::Planet(const Planet&) {
	DebugLog ("Planet: object copied.");
}


// |----------------------------------------------------------------------------|
// |							   Destructor									|
// |----------------------------------------------------------------------------|
Planet::~Planet() {
	DebugLog ("Planet: object destroyed.");
}


// |----------------------------------------------------------------------------|
// |							   Initialize									|
// |----------------------------------------------------------------------------|
bool Planet::Initialize() {
    GameObject::Initialize();
	DebugLog ("Planet: object initialized.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							    Shutdown									|
// |----------------------------------------------------------------------------|
bool Planet::Shutdown() {
    GameObject::Shutdown();
	DebugLog ("Planet: object shutdown.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							     Logic()									|
// |----------------------------------------------------------------------------|
bool Planet::Logic() {
	DebugLog ("Planet: Logic() called.", DB_LOGIC, 10);

    // Get time for this frame
    float time = TimerManager::GetRef()->GetTime() / 1000;

    // Update orbit Angle based on speed
    m_orbitAngle += m_orbitSpeed * time;

    // Determine relative position based on angle
    float x, y, z;
    z = -1*m_orbitRadius*sin(PI/2 - m_orbitTilt)*cos(m_orbitAngle);
    x = m_orbitRadius*sin(PI/2 - m_orbitTilt)*sin(m_orbitAngle);
    y = m_orbitRadius*cos(PI/2 - m_orbitTilt);
    m_position = Coord(x,y,z);

    // Translate based on center
    if (m_orbitCenterObject)
        m_orbitCenter = m_orbitCenterObject->GetPosition();
    m_position += m_orbitCenter;

	return true;
}

