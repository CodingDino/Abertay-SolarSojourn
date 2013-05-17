// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// GameObject
//      Abstract class for game all objects. Contains models, evaluates basic physics 
//      and executes other behaviour logic, sends render request to renderer.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "GameObject.h"


// |----------------------------------------------------------------------------|
// |							   Constructor									|
// |----------------------------------------------------------------------------|
GameObject::GameObject() :
    m_graphic(0)
{
	DebugLog ("GameObject: object instantiated.");
}
     

// |----------------------------------------------------------------------------|
// |							  Copy Constructor								|
// |----------------------------------------------------------------------------|
GameObject::GameObject(const GameObject&) {
	DebugLog ("GameObject: object copied.");
}


// |----------------------------------------------------------------------------|
// |							   Destructor									|
// |----------------------------------------------------------------------------|
GameObject::~GameObject() {
	DebugLog ("GameObject: object destroyed.");
}


// |----------------------------------------------------------------------------|
// |							   Initialize									|
// |----------------------------------------------------------------------------|
bool GameObject::Initialize() {

	DebugLog ("GameObject: object initialized.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							    Shutdown									|
// |----------------------------------------------------------------------------|
bool GameObject::Shutdown() {
    // TODO: Should we clean up graphic? Theoretically models and textures 
    //       should all be in one place, rather than owned by individual game objects.
    //       Graphic should be cleaned up here, but model, texture, material should be cleaned up elsewhere.

	DebugLog ("GameObject: object shutdown.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							     Logic()									|
// |----------------------------------------------------------------------------|
bool GameObject::Logic() {
	DebugLog ("GameObject: Logic() called.", DB_LOGIC, 10);

	return true;
}

// |----------------------------------------------------------------------------|
// |							     Draw()										|
// |----------------------------------------------------------------------------|
bool GameObject::Draw() {
	DebugLog ("GameObject: Draw() called.", DB_GRAPHICS, 10);

    if (!m_active) return true;

    if (m_graphic)
    {
        m_graphic->SetOrientation(m_orientation);
        m_graphic->SetPosition(m_position);
        m_graphic->Render();
    }

	return true;
}


// |----------------------------------------------------------------------------|
// |							     Draw()										|
// |----------------------------------------------------------------------------|
bool GameObject::Draw(Texture* renderTexture) {
	DebugLog ("GameObject: Draw() called.", DB_GRAPHICS, 10);

    if (!m_active) return true;

    if (m_graphic)
    {
        m_graphic->SetRenderTarget(renderTexture);
    }
    Draw();

	return true;
}

