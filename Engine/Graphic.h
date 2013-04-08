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
#include "GraphicsManager.h"


// |----------------------------------------------------------------------------|
// |                              Class: Graphic                                |
// |----------------------------------------------------------------------------|
class Graphic
{

public:

    //|-------------------------------Public Functions--------------------------|
    
    // Constructors and Destructors
    Graphic();
    Graphic(const Graphic&);
    virtual ~Graphic();
    
    // Initialization and shutdown
    bool Initialize();
    void Shutdown();

    // Renders the graphic to the supplied context
    void Render();

    // Getter functions
    Model* GetModel() { return m_model; }
    Texture* GetTexture() { return m_texture; }
    Material* GetMaterial() { return m_material; }

    // Setter functions
    void SetModel(Model* model) { m_model = model; }
    void SetTexture(Texture* texture) { m_texture = texture; }
    void SetMaterial(Material* material) { m_material = material; }

private:

    //|-------------------------------Private Functions-------------------------|

private:

    //|-----------------------------Private Data Members------------------------|

    Model* m_model;
    Texture* m_texture;
    Material* m_material;
};