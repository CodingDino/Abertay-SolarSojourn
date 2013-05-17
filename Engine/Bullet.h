// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Bullet
//      GameObject class that handles bullet functionality.
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"
#include "GameObject.h"
#include <cmath>
#define PI 3.14159265


// |----------------------------------------------------------------------------|
// |                        Class Definition: Bullet                            |
// |----------------------------------------------------------------------------|
class Bullet : public GameObject {

public:
    
    //|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
	Bullet();
	Bullet(const Bullet&);
	virtual ~Bullet();

    // Initialization and shutdown
	virtual bool  Initialize();
	virtual bool  Shutdown();
    
    // Performs logic functions for the object
    virtual bool  Logic();

protected:
    
    //|---------------------------Protected Data Members-----------------------|
};