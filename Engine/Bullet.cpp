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
#include "Bullet.h"


// |----------------------------------------------------------------------------|
// |							   Constructor									|
// |----------------------------------------------------------------------------|
Bullet::Bullet() :
    GameObject()
{
	DebugLog ("Bullet: object instantiated.");
}
     

// |----------------------------------------------------------------------------|
// |							  Copy Constructor								|
// |----------------------------------------------------------------------------|
Bullet::Bullet(const Bullet&) {
	DebugLog ("Bullet: object copied.");
}


// |----------------------------------------------------------------------------|
// |							   Destructor									|
// |----------------------------------------------------------------------------|
Bullet::~Bullet() {
	DebugLog ("Bullet: object destroyed.");
}


// |----------------------------------------------------------------------------|
// |							   Initialize									|
// |----------------------------------------------------------------------------|
bool Bullet::Initialize() {
    GameObject::Initialize();

	m_graphic = new Graphic;
    m_graphic->SetTint(0.8f,1.0f,0.8f,1.0f);
    m_graphic->SetShader("Texture");
	m_graphic->SetTexture("default");
    m_graphic->SetModel("sphere");
	m_graphic->SetReflectiveness(0.9f);
    m_graphic->SetScale(Coord(0.1f,0.1f,0.1f));
    m_graphic->Initialize();

	DebugLog ("Bullet: object initialized.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							    Shutdown									|
// |----------------------------------------------------------------------------|
bool Bullet::Shutdown() {
    GameObject::Shutdown();
	DebugLog ("Bullet: object shutdown.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							     Logic()									|
// |----------------------------------------------------------------------------|
bool Bullet::Logic() {
	DebugLog ("Bullet: Logic() called.", DB_LOGIC, 10);

	
    float time = TimerManager::GetRef()->GetTime() / 1000;

	m_position += m_linearVelocity * time;

	return true;
}

