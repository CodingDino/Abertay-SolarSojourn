// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// ParticleSystem
//      Manages a set of particles, emitted and handled based on set parameters
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"
#include "GameObject.h"
#include <list>


// |----------------------------------------------------------------------------|
// |                     Class Definition: ParticleSystem                       |
// |----------------------------------------------------------------------------|
class ParticleSystem : public GameObject {

private:

    //|-------------------------------Private TypeDefs--------------------------|

    struct ParticleType
	{
		Coord position;
		float red, green, blue, alpha;
        float lifetime;
        float maxLife;
		Coord velocity;
        Camera* camera;

        bool operator<(const ParticleType& rhs);
	};

public:
    
    //|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
	ParticleSystem();
	ParticleSystem(const ParticleSystem&);
	virtual ~ParticleSystem();

    // Initialization and shutdown
	virtual bool  Initialize();
	virtual bool  Shutdown();
    
    // Performs logic functions for the object
    virtual bool  Logic();
    
    // Renders camera
    bool virtual Draw();

	// Emits all particles at once (as in an explosion)
	void EmitAllParticles();

    // Setters
	void SetSpawnParticles(bool val) {m_spawnParticles = val;}
    void SetParticleDeviation(Coord particleDeviation) { m_particleDeviation = particleDeviation; }
    void SetParticleVelocity(Coord particleVelocity) { m_particleVelocity = particleVelocity; }
    void SetParticleVelocityVariation(Coord particleVelocityVariation) { m_particleVelocityVariation = particleVelocityVariation; }
    void SetParticleSize(float particleSize) { m_particleSize = particleSize; }
    void SetParticleSpawnFrequency(float particleSpawnFrequency) { m_particleSpawnFrequency = particleSpawnFrequency; }
    void SetParticleLifetime(float particleLifetime) { m_particleLifetime = particleLifetime; }
    void SetParticleFadeout(float particleFadeout) { m_particleFadeout = particleFadeout; }
    void SetMaxParticles(int maxParticles) { m_maxParticles = maxParticles; }
	void SetParticleDarken(float val) {m_particleDarken = val; }
    
    void SetTint(float r, float g, float b, float a = 1.0f) {
        m_tintR = r;
        m_tintG = g;
        m_tintB = b;
        m_alpha = a;
    }
    void SetTintVar(float r, float g, float b, float a = 1.0f) {
        m_tintRVar = r;
        m_tintGVar = g;
        m_tintBVar = b;
        m_alphaVar = a;
    }

protected:
   
    //|----------------------------Protected Functions-------------------------|

	void EmitParticle();
	void UpdateParticles();
	void KillParticles();

protected:
    
    //|---------------------------Protected Data Members-----------------------|

    // Particle system parameters
    float m_tintR, m_tintG, m_tintB, m_alpha;
    float m_tintRVar, m_tintGVar, m_tintBVar, m_alphaVar;
    Coord m_particleDeviation;
    Coord m_particleVelocity;
    Coord m_particleVelocityVariation;
    float m_particleSize;
    float m_particleSpawnFrequency;
    float m_particleFadeout;
    float m_particleLifetime;
	float m_particleDarken;
    int m_maxParticles;

    // Particle management data members
    float m_accumulatedTime;
	bool m_spawnParticles;
    std::list<ParticleType> m_particles;
};