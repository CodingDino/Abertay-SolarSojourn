// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// GameObject
//      Abstract class for game all objects. Contains models, evaluates basic physics 
//      and executes other behaviour logic, sends render request to renderer.
#pragma once

// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"
#include "Coord.h"
#include "Graphic.h"
#include "TimerManager.h"


// |----------------------------------------------------------------------------|
// |                        Class Definition: GameObject                        |
// |----------------------------------------------------------------------------|
class GameObject {

public:
    
    //|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
	GameObject();
	GameObject(const GameObject&);
	virtual ~GameObject();

    // Initialization and shutdown
	bool virtual Initialize();
	bool virtual Shutdown();
    
    // Performs logic functions for the object
    bool virtual Logic();
    
    // Sends any models or bitmaps associated with the object to the renderer
    bool virtual Draw();

    // Getter functions
    Coord virtual GetPosition() {return m_position; }
    Coord virtual GetOrientation() {return m_orientation; }
    Coord virtual GetLinearVelocity() {return m_linearVelocity; }
    Coord virtual GetAngularVelocity() {return m_angularVelocity; }
    Graphic* GetGraphic() {return m_graphic; }

    // Setter functions
    void virtual SetPosition(Coord position) {m_position = position;}
    void virtual SetOrientation(Coord orientation) {m_orientation = orientation;}
    void virtual SetLinearVelocity(Coord linearVelocity) {m_linearVelocity = linearVelocity;}
    void virtual SetAngularVelocity(Coord angularVelocity) {m_angularVelocity = angularVelocity;}
    void virtual SetGraphic(Graphic* graphic) {m_graphic = graphic; }

protected:
    
    //|---------------------------Protected Data Members-----------------------|
    Coord m_position;               // Position of the object
    Coord m_orientation;            // Orientation in pitch, yaw, roll
    Coord m_linearVelocity;         // Velocity of the object (updates the position in the Frame function)
    Coord m_angularVelocity;        // Angular velocity in pitch/s, yaw/s, roll/s

    // Graphics
    Graphic* m_graphic;

};