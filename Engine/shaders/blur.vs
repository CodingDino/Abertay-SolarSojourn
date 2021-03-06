// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// blur.vs
//      Vertex shader for handling 2-pass Gaussian blurring of textures

// |----------------------------------------------------------------------------|
// |                                 Defines                                    |
// |----------------------------------------------------------------------------|
#define NUM_PIXELS 9


// |----------------------------------------------------------------------------|
// |                                 Globals                                    |
// |----------------------------------------------------------------------------|
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
    float texelScale;
    bool horizontal;
    float2 padding;
};


// |----------------------------------------------------------------------------|
// |                            Type Definitions                                |
// |----------------------------------------------------------------------------|
struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float2 texCoord[NUM_PIXELS] : TEXCOORD1;
};


// |----------------------------------------------------------------------------|
// |                              Vertex Shader                                 |
// |----------------------------------------------------------------------------|
PixelInputType BlurVertexShader(VertexInputType input)
{
    PixelInputType output;
    float texelSize;


    // Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
    // Store the texture coordinates for the pixel shader.
    output.tex = input.tex;

    // Determine the floating point size of a texel for a screen with this specific width.
    texelSize = 1.0f / texelScale;

    // Create UV coordinates for the pixel and its four horizontal neighbors on either side.
    
    for( uint i = 0; i < NUM_PIXELS; i++ )
    {
        float neighbor = (float)i - (float)(NUM_PIXELS/2);
        if (horizontal)
            output.texCoord[i] = input.tex + float2(texelSize * neighbor, 0.0f);
        else
            output.texCoord[i] = input.tex + float2(0.0f, texelSize * neighbor);
    }

    return output;
}