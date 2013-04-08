// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// GraphicsClass
//      Overall control of graphics and rendering, holds model objects and other graphics objects
#pragma once

// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Coord.h"
#include "D3DManager.h"
#include "ColorShader.h"
#include "Singleton.h"
#include "Camera.h"
#include <cstring>


// |----------------------------------------------------------------------------|
// |                                 Globals                                    |
// |----------------------------------------------------------------------------|
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;
const int NUM_MODELS=20;


// |----------------------------------------------------------------------------|
// |                          Class: GraphicsManager                            |
// |----------------------------------------------------------------------------|
class GraphicsManager : public Singleton<GraphicsManager>
{
public:

    //|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
	GraphicsManager();
	GraphicsManager(const GraphicsManager&);
	~GraphicsManager();
    
    // Initialization and shutdown
    bool Initialize(int screenWidth, int screenHeight);
    void Shutdown();

    // Frame-by-frame graphics processing
    bool Frame(int mouseX, int mouseY, int fps, int cpu, float frameTime, 
        Coord camera_rotation, Coord camera_position, bool transfer);

    // Rendering setup (starts scene, gets world, view, and projection matrix)
    bool BeginRender();

    // Rendering cleanup (ends the scene)
    bool EndRender();

    // Get matrices
    D3DXMATRIX GetWorldMatrix() {return worldMatrix;}
    D3DXMATRIX GetViewMatrix() {return viewMatrix;}
    D3DXMATRIX GetProjectionMatrix() {return projectionMatrix;}
    D3DXMATRIX GetOrthoMatrix() {return orthoMatrix;}
    D3DXMATRIX GetBaseViewMatrix() {return baseViewMatrix;}

    // Get shaders
    Shader* GetShader(const char* key);

private:

    //|-------------------------------Private Functions-------------------------|

    // Calls render functions in order
    bool Render(int mouseX, int mouseY, Coord camera_position);

    // Renders the passed in model using the given transforms
    //bool ModelRender(ModelClass& to_render, D3DXMATRIX scale, 
    //    D3DXMATRIX translate, D3DXMATRIX rotate);

    // Renders the passed in bitmap using the given transforms
    // bool BitmapRender(BitmapClass& to_render, int x, int y);

private:

    //|-----------------------------Private Data Members------------------------|

    // DirectX object
    D3DManager* m_D3D;

    // Camera
    Camera* m_Camera;

    // Shaders
    ColorShader* m_colorShader;
    // LightShaderClass* m_LightShader;
    // TextureShaderClass* m_TextureShader;

    // Matrices
    D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, baseViewMatrix;

    // Screen
    int m_screen;
    float m_screenCounter;

    // Screen dimmensions
    int m_screenWidth;
    int m_screenHeight;
};