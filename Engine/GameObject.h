// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// GameObject
//      Abstract class for game objects. Contains models, evaluates physics and
//      executes other behaviour logic, sends render request to renderer.
#pragma once

// TODO: cpp file, models, textures, materials

// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "Util.h"
#include "Coord.h"


// |----------------------------------------------------------------------------|
// |						Class Definition: GameObject						|
// |----------------------------------------------------------------------------|
class GameObject {

public:
    
    //|-------------------------------Public Functions--------------------------|
    
	// Constructor
	GameObject ();
    
	// Performs logic functions for the object
	bool virtual Frame();

	// Setter functions
	void virtual SetPosition(Coord position);
	void virtual SetRotation(Coord rotation);
	
protected:
    
	//|---------------------------Protected Data Members-----------------------|
	Coord m_position;		// Position of the object
	Coord m_velocity;		// Velocity of the object (updates the position in the Frame function)
	Coord m_rotation;		// Angle of rotation

    // Graphics
	//Model* m_model;		    // Model for the object
    //Texture* m_texture;       // Texture for the object
    //Material* m_material;     // Material for the object
    LAYER m_layer;              // Layer the object should be rendered on

};