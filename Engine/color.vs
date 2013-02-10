// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// color.vs
//      Vertex shader for handling simple colored shapes with no lighting/texture


// |----------------------------------------------------------------------------|
// |                                 Globals                                    |
// |----------------------------------------------------------------------------|
cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};


// |----------------------------------------------------------------------------|
// |                            Type Definitions                                |
// |----------------------------------------------------------------------------|
struct VertexInputType
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

// |----------------------------------------------------------------------------|
// |                              Vertex Shader                                 |
// |----------------------------------------------------------------------------|
PixelInputType ColorVertexShader(VertexInputType input)
{
    PixelInputType output;

    // Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
    // Store the input color for the pixel shader to use.
    output.color = input.color;
    
    return output;
}