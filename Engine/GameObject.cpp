// Solar Exploration Sim
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
GameObject::GameObject()
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

	return true;
}

