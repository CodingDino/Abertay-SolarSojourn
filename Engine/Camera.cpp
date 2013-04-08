// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Camera
//      Methods for setting the position and rotation of the camera.



// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "Camera.h"


// |----------------------------------------------------------------------------|
// |						   Default Constructor								|
// |----------------------------------------------------------------------------|
Camera::Camera()
{
}


// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
Camera::Camera(const Camera& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
Camera::~Camera()
{
}


// |----------------------------------------------------------------------------|
// |						     SetPosition									|
// |----------------------------------------------------------------------------|
void Camera::SetPosition(Coord position)
{
    m_position = position;
	return;
}


// |----------------------------------------------------------------------------|
// |						     SetOrientation									|
// |----------------------------------------------------------------------------|
void Camera::SetOrientation(Coord orientation)
{
	m_orientation = orientation;
	return;
}


// |----------------------------------------------------------------------------|
// |						     GetPosition									|
// |----------------------------------------------------------------------------|
Coord Camera::GetPosition()
{
	return m_position;
}


// |----------------------------------------------------------------------------|
// |						     GetOrientation									|
// |----------------------------------------------------------------------------|
Coord Camera::GetOrientation()
{
	return m_orientation;
}



// |----------------------------------------------------------------------------|
// |						     GetViewMatrix									|
// |----------------------------------------------------------------------------|
void Camera::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}


// |----------------------------------------------------------------------------|
// |						       Render										|
// |----------------------------------------------------------------------------|
void Camera::Render()
{
	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;


	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = m_position.x;
	position.y = m_position.y;
	position.z = m_position.z;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_orientation.x * 0.0174532925f;
	yaw   = m_orientation.y * 0.0174532925f;
	roll  = m_orientation.z * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_viewMatrix, &position, &lookAt, &up);

	return;
}