// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// AssetManager
//      Manages loading and unloading assets including textures, models, and sounds
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"
#include "Singleton.h"
#include "Texture.h"
#include "Font.h"
#include "Model.h"
#include "Quad.h"
#include "Sentence.h"
#include <string>
#include <map>


// |----------------------------------------------------------------------------|
// |                              Class: AssetManager                           |
// |----------------------------------------------------------------------------|
class AssetManager : public Singleton<AssetManager>
{
public:

    //|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
	AssetManager();
	AssetManager(const AssetManager&);
	~AssetManager();
    
    // Initialization and shutdown
    bool Initialize();
    void Shutdown();

    // Getters
    Texture* GetTexture(std::string name);
    Font* GetFont(std::string name);
    Model* GetModel(std::string name);

private:

    //|-------------------------------Private Functions-------------------------|

private:

    //|-----------------------------Private Data Members------------------------|

    std::map<std::string,Texture*> m_textures;
    std::map<std::string,Font*> m_fonts;
    std::map<std::string,Model*> m_models;
    //std::map<std::string,Sample*> m_samples;

};