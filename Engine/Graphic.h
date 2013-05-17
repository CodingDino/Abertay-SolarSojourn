// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Graphic
//      Contains data for a single graphic, including model, texture, and material.
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"
#include "Model.h"
#include "Texture.h"
#include "Material.h"
#include "GraphicsManager.h"
#include "AssetManager.h"


// |----------------------------------------------------------------------------|
// |                              Class: Graphic                                |
// |----------------------------------------------------------------------------|
class Graphic : public Material
{

public:

    //|-------------------------------Public Functions--------------------------|
    
    // Constructors and Destructors
    Graphic();
    Graphic(const Graphic&);
    virtual ~Graphic();
    
    // Initialization and shutdown
    virtual bool Initialize();
    virtual void Shutdown();

    // Renders the graphic to the supplied context
    virtual void Render();
    virtual void Render(Coord position);

    // Getter functions
    virtual Model* GetModel() { return m_model; }
    virtual Texture* GetTexture() { return m_texture; }
    //virtual Material* GetMaterial() { return this; }
    virtual Coord GetPosition() {return m_position; }
    virtual Coord GetOrientation() {return m_orientation; }
    virtual Coord GetScale() {return m_scale; }

    // Setter functions
    virtual void SetModel(Model* model) { m_model = model; }
    virtual void SetModel(std::string name) { m_model = AssetManager::GetRef()->GetModel(name); }
    virtual void SetTexture(Texture* texture) { m_texture = texture; }
    virtual void SetTexture(std::string name) { m_texture = AssetManager::GetRef()->GetTexture(name); }
    virtual void SetPosition(Coord position) {m_position = position;}
    virtual void SetOrientation(Coord orientation) {m_orientation = orientation;}
    virtual void SetScale(Coord scale) {m_scale = scale;}

protected:

    //|------------------------------Protected Functions------------------------|

    virtual D3DXMATRIX TransformWorldMatrix(Coord position);

protected:

    //|----------------------------Protected Data Members-----------------------|

    // Main Graphic Components
    Model* m_model;
    Texture* m_texture;

    // Graphic Parameters
    Coord m_scale;
    Coord m_orientation;
    Coord m_position;
};