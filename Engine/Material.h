// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Material
//      Wraps information about what shader and shader settings to use.
#pragma once

// TODO: Material settings for alpha blending, back face culling, and z buffer


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include "Util.h"
#include "GraphicsManager.h"


// |----------------------------------------------------------------------------|
// |                            Forward Declarations                            |
// |----------------------------------------------------------------------------|
class Shader;


// |----------------------------------------------------------------------------|
// |                              Class: Material                               |
// |----------------------------------------------------------------------------|
class Material
{

public:

    Material() : 
        m_shader(0),
        m_tintR(1.0),
        m_tintG(1.0),
        m_tintB(1.0),
        m_alpha(1.0),
        m_alphaBlend(false),
        m_particleBlend(false),
        m_backfaceCull(true),
        m_zBuffer(true)
    {}

    // Setters
    void SetShader(std::string name) { m_shader = GraphicsManager::GetRef()->GetShader(name); }
    void SetShader(Shader* shader) { m_shader = shader; }
    void SetTint(float r, float g, float b, float a = 1.0f) {
        m_tintR = Clamp(r,0.0f,1.0f);
        m_tintG = Clamp(g,0.0f,1.0f);
        m_tintB = Clamp(b,0.0f,1.0f);
        m_alpha = Clamp(a,0.0f,1.0f);
    }
    void SetAlphaBlend(bool alphaBlend) { m_alphaBlend = alphaBlend; }
    void SetParticleBlend(bool particleBlend) { m_particleBlend = particleBlend; }
    void SetBackfaceCull(bool backfaceCull) { m_backfaceCull = backfaceCull; }
    void SetZBuffer(bool zBuffer) { m_zBuffer = zBuffer; }

    // Getters
    Shader* GetShader() {return m_shader; }
    float GetTintR() {return m_tintR; }
    float GetTintG() {return m_tintG; }
    float GetTintB() {return m_tintB; }
    float GetAlpha() {return m_alpha; }
    bool GetAlphaBlend() {return m_alphaBlend; }
    bool GetParticleBlend() {return m_particleBlend; }
    bool GetBackfaceCull() {return m_backfaceCull; }
    bool GetZBuffer() {return m_zBuffer; }
    
protected: 

    Shader* m_shader;
    float m_tintR, m_tintG, m_tintB;
    float m_alpha;
    bool m_alphaBlend;
    bool m_particleBlend;
    bool m_backfaceCull;
    bool m_zBuffer;

};