// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Camera
//      Methods for setting the position and rotation of the camera.
#pragma once

// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include <d3dx10math.h>
#include "Util.h"
#include "Coord.h"

// |----------------------------------------------------------------------------|
// |						   Class: CameraClass								|
// |----------------------------------------------------------------------------|
class Camera
{
public:
	//|-------------------------------Public Functions--------------------------|

	// Constrcutors and Deconstructors
	Camera();
	Camera(const Camera&);
	~Camera();
    
    // Initialization and shutdown (placeholder)
    bool Initialize() { return true; }
    void Shutdown() {}

	// Get and set functions
	void SetPosition(Coord position);
	void SetOrientation(Coord orientation);
	Coord GetPosition();
	Coord GetOrientation();
	void GetViewMatrix(D3DXMATRIX&);

	// Transforms the viewMatrix for use with rendering
	void Render();

private:
	//|-----------------------------Private Data Members------------------------|

	// Position of the camera in the game world
	Coord m_position;

	// Rotation of the camera in the game world, in degrees
    Coord m_orientation;

	// Matrix for use with world transformations, set by Render function
	D3DXMATRIX m_viewMatrix;
};