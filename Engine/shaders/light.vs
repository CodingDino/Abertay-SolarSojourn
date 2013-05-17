// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// light.vs
//      Vertex shader for handling simple textured shapes with lighting

// |----------------------------------------------------------------------------|
// |                                 Defines                                    |
// |----------------------------------------------------------------------------|
#define NUM_LIGHTS 4

// |----------------------------------------------------------------------------|
// |                                 Globals                                    |
// |----------------------------------------------------------------------------|
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
    float3 cameraPosition;
    float fogDensity;
    float4 pointLightPosition[NUM_LIGHTS];
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
    float3 normal : NORMAL;
    float3 viewDirection : TEXCOORD1;
    float4 pointLightPos[NUM_LIGHTS] : TEXCOORD2;
    float fogFactor : FOG;
};


// |----------------------------------------------------------------------------|
// |                              Vertex Shader                                 |
// |----------------------------------------------------------------------------|
PixelInputType LightVertexShader(VertexInputType input)
{
    PixelInputType output;
    float4 worldPosition;
    float4 fogPosition;
    
    // Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

    // Store the texture coordinates for the pixel shader.
    output.tex = input.tex;

    // Calculate the normal vector against the world matrix only.
    output.normal = mul(input.normal, (float3x3)worldMatrix);
	
    // Normalize the normal vector.
    output.normal = normalize(output.normal);

    // Calculate the position of the vertex in the world.
    worldPosition = mul(input.position, worldMatrix);

    // Determine the viewing direction based on the position of the camera and the position of the vertex in the world.
    output.viewDirection = cameraPosition.xyz - worldPosition.xyz;
	
    // Normalize the viewing direction vector.
    output.viewDirection = normalize(output.viewDirection);

    int test = ((int)(NUM_LIGHTS/2));

    for( uint i = 0; i < NUM_LIGHTS; i++ )
    {
        // Determine the light positions based on the position of the lights and the position of the vertex in the world.
        output.pointLightPos[i] = pointLightPosition[i] - worldPosition;

        // Normalize the light position vectors.
        output.pointLightPos[i] = normalize(output.pointLightPos[i]);
    }
    
    // Calculate the camera position.
    fogPosition = mul(input.position, worldMatrix);
    fogPosition = mul(fogPosition, viewMatrix);

    // Calculate linear fog.    
    output.fogFactor = 1.0f - 1.0 / pow (2.71828, (fogPosition.z * (fogDensity / 10)));

    return output; 
}