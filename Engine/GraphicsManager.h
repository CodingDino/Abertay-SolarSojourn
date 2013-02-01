// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// GraphicsClass
//      Overall control of graphics and rendering, holds model objects and other graphics objects
#pragma once

// TODO: Make this singleton

// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Coord.h"
#include "Util.h"
#include "D3DManager.h"


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
class GraphicsManager
{
public:

    //|-------------------------------Public Functions--------------------------|
    
    // Returns instance
    static GraphicsManager* GetInstance();

    // Creates and initializes all data members, sets initial graphics state
    bool Initialize(int screenWidth, int screenHeight, HWND hwnd);

    // Performs shutdown, deallocation, and cleanup for data members
    void Shutdown();

    // Frame-by-frame graphics processing
    bool Frame(int mouseX, int mouseY, int fps, int cpu, float frameTime, 
        Coord camera_rotation, Coord camera_position, bool transfer);

private:

    //|-------------------------------Private Functions-------------------------|

    // Constructors and Destructors
    GraphicsManager();
    GraphicsManager(const GraphicsManager&);
    ~GraphicsManager();

    // Calls render functions in order
    bool Render(int mouseX, int mouseY, Coord camera_position);

    // Rendering setup (starts scene, gets world, view, and projection matrix)
    bool BeginRender();

    // Rendering cleanup (ends the scene)
    bool EndRender();

    // Renders the passed in model using the given transforms
    //bool ModelRender(ModelClass& to_render, D3DXMATRIX scale, 
    //    D3DXMATRIX translate, D3DXMATRIX rotate);

    // Renders the passed in bitmap using the given transforms
    // bool BitmapRender(BitmapClass& to_render, int x, int y);

private:

    //|-----------------------------Private Data Members------------------------|
    
    // Singleton instance
    static GraphicsManager* s_instance;

    // DirectX object
    D3DManager* m_D3D;

    // Camera
    // TODO: Should this be a game object?
    // CameraClass* m_Camera;

    // Shaders
    // LightShaderClass* m_LightShader;
    // TextureShaderClass* m_TextureShader;

    // Matrices
    D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, baseViewMatrix;

    // Screen
    int m_screen;
    float m_screen_counter;

    // Screen dimmensions
    int m_screen_width;
    int m_screen_height;
};