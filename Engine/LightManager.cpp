// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// LightManager
//      Holds light information that can be accessed by shaders


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "LightManager.h"



// |----------------------------------------------------------------------------|
// |							   Constructor									|
// |----------------------------------------------------------------------------|
LightManager::LightManager() : 
    m_ambient(0.0f,0.0f,0.0f,1.0f),
    m_diffuseColor(0.0f,0.0f,0.0f,1.0f),
    m_diffuseDirection(0.0f,0.0f,0.0f),
    m_fogColor(0.0f,0.0f,0.0f,1.0f),
    m_fogDensity(0.0f)
{
	DebugLog ("LightManager: object instantiated.");
}
    

// |----------------------------------------------------------------------------|
// |							      GetLights		   						    |
// |----------------------------------------------------------------------------|
void LightManager::Shutdown()
{
    // De-allocate all point lights
    for (std::list<PointLight*>::iterator it=m_pointLights.begin(); it!=m_pointLights.end(); ++it)
    {
        delete *it;
        *it = 0;
    }
    m_pointLights.clear();
}

// |----------------------------------------------------------------------------|
// |							     AddLight									|
// |----------------------------------------------------------------------------|
void LightManager::AddLight(PointLight to_add)
{
    PointLight* new_light = new PointLight;
    new_light->position = to_add.position;
    new_light->color = to_add.color;
    new_light->brightness = to_add.brightness;
    m_pointLights.push_back(new_light);
}


// |----------------------------------------------------------------------------|
// |							     RemoveLight								|
// |----------------------------------------------------------------------------|
bool LightManager::RemoveLight(PointLight* to_remove)
{
    bool found = false;
    for (std::list<PointLight*>::iterator it=m_pointLights.begin(); it != m_pointLights.end(); ++it)
    {
        if (*it == to_remove)
        {
            found = true;
            delete to_remove;
            m_pointLights.erase(it);
            break;
        }
    }
    return found;
}


// |----------------------------------------------------------------------------|
// |							      GetLights		   						    |
// |----------------------------------------------------------------------------|
std::list<PointLight*> LightManager::GetLights(Coord position, int num_lights)
{
    std::list<PointLight*> to_return;
    D3DXVECTOR3 pos = D3DXVECTOR3(position.x,position.y,position.z);
    float distance = 0.0f;
    float min_distance=1000.0f;
    PointLight* closest = 0;
    float limit_distance=0.0f;
    PointLight* limiter = 0;

    for (int i=0; i < num_lights; ++i)
    {
        bool found = false;

        for (std::list<PointLight*>::iterator it=m_pointLights.begin(); it != m_pointLights.end(); ++it)
        {
            distance = D3DXVec3Length(&(pos-D3DXVECTOR3((*it)->position)));
            if (distance < min_distance && distance >= limit_distance && *it != limiter)
            {
                found = true;
                min_distance = distance;
                closest = *it;
            }
        }

        // Record the closest
        if (found)
        {
            limiter = closest;
            limit_distance = min_distance;
            to_return.push_back(closest);
            closest = 0;
            min_distance = 1000.0f;
        }
        else break; // if we didn't find any on this pass, then break.
    }

    return to_return;
}