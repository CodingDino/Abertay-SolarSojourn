// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Graphic
//      Contains data for a single graphic, including model, texture, and material.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"
#include "Model.h"
#include "Texture.h"
#include "Material.h"


// |----------------------------------------------------------------------------|
// |                              Class: Graphic                                |
// |----------------------------------------------------------------------------|
class Graphic
{

public:

    //|-------------------------------Public Functions--------------------------|
    
    // Constructors and Destructors
    Graphic();

    // Initialize the graphic, reads in a vertex and texture file
    bool Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename);

    // Releases data associated with the model
    void Shutdown();

    // Renders the graphic to the supplied context
    void Render(ID3D11DeviceContext* deviceContext);

    // Getter functions
    Model* GetModel() { return m_model; }
    Texture* GetTexture() { return m_texture; }
    Material* GetMaterial() { return m_material; }

private:

    //|-------------------------------Private Functions-------------------------|

private:

    //|-----------------------------Private Data Members------------------------|

    Model* m_model;
    Texture* m_texture;
    Material* m_material;
};