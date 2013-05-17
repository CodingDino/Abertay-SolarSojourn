// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// LightManager
//      Holds light information that can be accessed by shaders
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"
#include "Singleton.h"
#include <d3dx10math.h>
#include "Coord.h"
#include <list>


// |----------------------------------------------------------------------------|
// |                             Struct: PointLight                             |
// |----------------------------------------------------------------------------|
struct PointLight
{
    D3DXVECTOR4 position;
    D3DXVECTOR4 color;
    float brightness; // Controlls how far this light reaches (range/attenuation)

    void SetPosition(Coord pos)
    {
        position.x = pos.x;
        position.y = pos.y;
        position.z = pos.z;
        position.w = 1.0f;
    }
    void SetColor(float r, float g, float b, float a)
    {
        color.x = r;
        color.y = g;
        color.z = b;
        color.w = a;
    }
    void SetBrightness(float val)
    {
        brightness = val;
    }
};

// |----------------------------------------------------------------------------|
// |                             Class: LightManager                            |
// |----------------------------------------------------------------------------|
class LightManager : public Singleton<LightManager>
{
public:

    //|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
    LightManager();
	LightManager(const LightManager&) {}
	~LightManager() {}
    
    // Initialization and shutdown
    bool Initialize() {return true;}
    void Shutdown();

    // Getters
    D3DXVECTOR4 GetAmbient() {return m_ambient;}
    D3DXVECTOR4 GetDiffuseColor() {return m_diffuseColor;}
    D3DXVECTOR3 GetDiffuseDirection() {return m_diffuseDirection;}
    D3DXVECTOR4 GetFogColor() {return m_fogColor;}
    float GetFogDensity() {return m_fogDensity;}

    // Setters
    void SetAmbient(float r, float g, float b) {m_ambient = D3DXVECTOR4(r,g,b,1.0f);}
    void SetDiffuseColor(float r, float g, float b) {m_diffuseColor = D3DXVECTOR4(r,g,b,1.0f);}
    void SetDiffuseDirection(float x, float y, float z) {m_diffuseDirection = D3DXVECTOR3(x,y,z);}
    void SetDiffuseDirection(Coord coord) {m_diffuseDirection = D3DXVECTOR3(coord.x,coord.y,coord.z);}
    void SetFogColor(float r, float g, float b) {m_fogColor = D3DXVECTOR4(r,g,b,1.0f);}
    void SetFogDensity(float val) {m_fogDensity = val;}

    // Point light managers
    void AddLight(PointLight to_add);
    bool RemoveLight(PointLight* to_remove);
    std::list<PointLight*> GetLights(Coord position, int num_lights);


private:

    //|-------------------------------Private Functions-------------------------|

private:

    //|-----------------------------Private Data Members------------------------|
    D3DXVECTOR4 m_ambient;
    D3DXVECTOR4 m_diffuseColor;
    D3DXVECTOR3 m_diffuseDirection;
    std::list<PointLight*> m_pointLights;

    // Fog
    D3DXVECTOR4 m_fogColor;
    float m_fogDensity;

};