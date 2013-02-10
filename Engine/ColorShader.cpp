// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// ColorShader
//      Wraps and interacts with vertex and pixel shader.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "ColorShader.h"


// |----------------------------------------------------------------------------|
// |                           Default Constructor                              |
// |----------------------------------------------------------------------------|
ColorShader::ColorShader() :
    Shader("ColorVertexShader", "ColorPixelShader", L"../Engine/color.vs", L"../Engine/color.ps")
{
}