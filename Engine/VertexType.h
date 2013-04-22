// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// VertexType
//      A typedef for a vertex, used in models, meshes, and fonts.
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <d3dx10math.h>

// |----------------------------------------------------------------------------|
// |                            Struct: VertexType                              |
// |----------------------------------------------------------------------------|
struct VertexType
{
    D3DXVECTOR3 position;   // Vertex position in 3d space
    D3DXVECTOR2 texture;    // Texture coordinate for 2D texture
    D3DXVECTOR3 normal;     // Normal vector for this vertex
};