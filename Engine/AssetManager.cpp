// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// AssetManager
//      Manages loading and unloading assets including textures, models, and sounds


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "AssetManager.h"


// |----------------------------------------------------------------------------|
// |                           Default Constructor                              |
// |----------------------------------------------------------------------------|
AssetManager::AssetManager()
{
}


// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
AssetManager::AssetManager(const AssetManager& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
AssetManager::~AssetManager()
{
}


// |----------------------------------------------------------------------------|
// |                              Initialize                                    |
// |----------------------------------------------------------------------------|
bool AssetManager::Initialize()
{
    // Load in default texture
    GetTexture("default");
    GetFont("default");
    // Create quad
    Quad* quad = new Quad;
    quad->Initialize();
    m_models["quad"] = quad;

    return true;
}


// |----------------------------------------------------------------------------|
// |                              Shutdown                                      |
// |----------------------------------------------------------------------------|
void AssetManager::Shutdown()
{
    // De-allocate all fonts
    for (std::map<string,Font*>::iterator it=m_fonts.begin(); it!=m_fonts.end(); ++it)
    {
        it->second->Shutdown();
        delete it->second;
        it->second = 0;
    }
    // De-allocate all textures
    for (std::map<string,Texture*>::iterator it=m_textures.begin(); it!=m_textures.end(); ++it)
    {
        it->second->Shutdown();
        delete it->second;
        it->second = 0;
    }
    // De-allocate all models
    for (std::map<string,Model*>::iterator it=m_models.begin(); it!=m_models.end(); ++it)
    {
        it->second->Shutdown();
        delete it->second;
        it->second = 0;
    }
    
    // Clear maps
    m_textures.clear();
    m_fonts.clear();
    m_models.clear();
    return;
}


// |----------------------------------------------------------------------------|
// |                              GetTexture                                    |
// |----------------------------------------------------------------------------|
Texture* AssetManager::GetTexture(std::string name)
{
	DebugLog ("AssetManager::GetTexture called.", DB_GRAPHICS, 1);

    // If the texture is already in the map, just return it
    if (m_textures.count(name)) 
    {
	    DebugLog ("AssetManager: Texture found.", DB_GRAPHICS, 1);
        return m_textures[name];
    }

    // If not, try loading it from file.
    // Construct string name
    std::wstring  filePath = L"../Engine/data/textures/";
    std::wstring wsTmp(name.begin(), name.end());
    filePath += wsTmp;
    filePath += L".png";
    WCHAR* filePathC = (WCHAR*)filePath.c_str();

    // Attempt to load
    Texture* texture = new Texture;
    bool result = texture->Initialize(filePathC);
    if (!result)
    {
	    DebugLog ("AssetManager: Unable to load texture.", DB_GRAPHICS, 1);
        return m_textures["default"];
    }

    // If it was loaded, add it to the map and return it.
    m_textures[name] = texture;
	DebugLog ("AssetManager: Texture loaded.", DB_GRAPHICS, 1);
    return texture;
}


// |----------------------------------------------------------------------------|
// |                                 GetFont                                    |
// |----------------------------------------------------------------------------|
Font* AssetManager::GetFont(std::string name)
{
	DebugLog ("AssetManager::GetFont called.", DB_GRAPHICS, 1);

    // If the texture is already in the map, just return it
    if (m_fonts.count(name)) 
    {
	    DebugLog ("AssetManager: font found.", DB_GRAPHICS, 1);
        return m_fonts[name];
    }

    // If not, try loading it from file.
    // Construct string name
    std::wstring  filePathW = L"../Engine/data/fonts/";
    std::wstring wsTmp(name.begin(), name.end());
    filePathW += wsTmp;
    filePathW += L".png";
    WCHAR* filePathWC = (WCHAR*)filePathW.c_str();
    std::string filePath = "../Engine/data/fonts/";
    filePath += name;
    filePath += ".xml";
    const char* filtPathC = filePath.c_str();

    // Attempt to load
    Font* font = new Font;
    bool result = font->Initialize(filtPathC, filePathWC);
    if (!result)
    {
	    DebugLog ("AssetManager: Unable to load font.", DB_GRAPHICS, 1);
        return m_fonts["default"];
    }

    // If it was loaded, add it to the map and return it.
    m_fonts[name] = font;
	DebugLog ("AssetManager: font loaded.", DB_GRAPHICS, 1);
    return font;
}


// |----------------------------------------------------------------------------|
// |                                 GetModel                                   |
// |----------------------------------------------------------------------------|
Model* AssetManager::GetModel(std::string name)
{
	DebugLog ("AssetManager::GetModel called.", DB_GRAPHICS, 1);

    // If the texture is already in the map, just return it
    if (m_models.count(name)) 
    {
	    DebugLog ("AssetManager: model found.", DB_GRAPHICS, 1);
        return m_models[name];
    }

    // If not, try loading it from file.
    // Construct string name
    std::string filePath = "../Engine/data/models/";
    filePath += name;
    filePath += ".txt";
    const char* filtPathC = filePath.c_str();

    // Attempt to load
    Model* model = new Model;
    bool result = model->Initialize(filtPathC);
    if (!result)
    {
	    DebugLog ("AssetManager: Unable to load model.", DB_GRAPHICS, 1);
        return m_models["sphere"];
    }

    // If it was loaded, add it to the map and return it.
    m_models[name] = model;
	DebugLog ("AssetManager: model loaded.", DB_GRAPHICS, 1);
    return model;
}