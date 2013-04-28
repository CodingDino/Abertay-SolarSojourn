// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// MouseLookCamera
//      GameObject class that mouse look, and adjusts the main camera if set to active.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "MouseLookCamera.h"


// |----------------------------------------------------------------------------|
// |							   Constructor									|
// |----------------------------------------------------------------------------|
MouseLookCamera::MouseLookCamera() :
    m_active(true),
    m_mouseSensitivity(1.0f),
    GameObject()
{
	DebugLog ("MouseLookCamera: object instantiated.");
}
     

// |----------------------------------------------------------------------------|
// |							  Copy Constructor								|
// |----------------------------------------------------------------------------|
MouseLookCamera::MouseLookCamera(const MouseLookCamera&) {
	DebugLog ("MouseLookCamera: object copied.");
}


// |----------------------------------------------------------------------------|
// |							   Destructor									|
// |----------------------------------------------------------------------------|
MouseLookCamera::~MouseLookCamera() {
	DebugLog ("MouseLookCamera: object destroyed.");
}


// |----------------------------------------------------------------------------|
// |							   Initialize									|
// |----------------------------------------------------------------------------|
bool MouseLookCamera::Initialize() {
    GameObject::Initialize();
	DebugLog ("MouseLookCamera: object initialized.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							    Shutdown									|
// |----------------------------------------------------------------------------|
bool MouseLookCamera::Shutdown() {
    GameObject::Shutdown();
	DebugLog ("MouseLookCamera: object shutdown.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							     Logic()									|
// |----------------------------------------------------------------------------|
bool MouseLookCamera::Logic() {
	DebugLog ("MouseLookCamera: Logic() called.", DB_LOGIC, 10);

    // Exit if the camera is not active
    if (!m_active) return true;

    // Get mouse input for orientation
    int mouseX, mouseY;
    InputManager::GetRef()->GetMouseChange(mouseX, mouseY);
    m_orientation.x += m_mouseSensitivity * mouseY; // TODO: Scale by elapsed time
    m_orientation.y += m_mouseSensitivity * mouseX; // TODO: Scale by elapsed time

    // Set camera orientation
    Camera* camera = GraphicsManager::GetRef()->GetCamera();
    camera->SetOrientation(m_orientation);

    // TODO: Get keyboard input for movement

    // TODO: Set camera position

	return true;
}


// |----------------------------------------------------------------------------|
// |							     Draw()										|
// |----------------------------------------------------------------------------|
bool MouseLookCamera::Draw() {
	DebugLog ("MouseLookCamera: Draw() called.", DB_GRAPHICS, 10);

    // Call parent draw
    GameObject::Draw();

	return true;
}

