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

    // Setters
    void SetParticleDeviation(Coord particleDeviation) { m_particleDeviation = particleDeviation; }
    void SetParticleVelocity(Coord particleVelocity) { m_particleVelocity = particleVelocity; }
    void SetParticleVelocityVariation(Coord particleVelocityVariation) { m_particleVelocityVariation = particleVelocityVariation; }
    void SetParticleSize(float particleSize) { m_particleSize = particleSize; }
    void SetParticleSpawnFrequency(float particleSpawnFrequency) { m_particleSpawnFrequency = particleSpawnFrequency; }
    void SetParticleLifetime(float particleLifetime) { m_particleLifetime = particleLifetime; }
    void SetParticleFadeout(float particleFadeout) { m_particleFadeout = particleFadeout; }
    void SetMaxParticles(int maxParticles) { m_maxParticles = maxParticles; }

protected:
   
    //|----------------------------Protected Functions-------------------------|

	void EmitParticles();
	void UpdateParticles();
	void KillParticles();

protected:
    
    //|---------------------------Protected Data Members-----------------------|

    // Particle system parameters
    Coord m_particleDeviation;
    Coord m_particleVelocity;
    Coord m_particleVelocityVariation;
    float m_particleSize;
    float m_particleSpawnFrequency;
    float m_particleFadeout;
    float m_particleLifetime;
    int m_maxParticles;

    // Particle management data members
    float m_accumulatedTime;
    std::list<ParticleType> m_particles;
};