// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Explosion
//      Manages a set of particles, emitted and handled based on set parameters
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"
#include "GameObject.h"
#include "Billboard.h"
#include <list>


// |----------------------------------------------------------------------------|
// |                     Class Definition: ParticleSystem                       |
// |----------------------------------------------------------------------------|
class Explosion : public GameObject {

private:

    //|-------------------------------Private TypeDefs--------------------------|
	enum EXPLOSION_EFFECT { EXPLOSION_FIREBALL };


    struct ParticleType
	{
		EXPLOSION_EFFECT type;
		Coord position;
		float rotation;
		float darken;
		float angularVelocity;
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
	Explosion();
	Explosion(const Explosion&);
	virtual ~Explosion();

    // Initialization and shutdown
	virtual bool  Initialize();
	virtual bool  Shutdown();
    
    // Performs logic functions for the object
    virtual bool  Logic();
    
    // Renders camera
    bool virtual Draw();

	// Start the explosion
	void virtual Explode();

    // Setters
    void SetParticleDeviation(Coord particleDeviation) { m_particleDeviation = particleDeviation; }
    void SetParticleVelocity(Coord particleVelocity) { m_particleVelocity = particleVelocity; }
    void SetParticleVelocityVariation(Coord particleVelocityVariation) { m_particleVelocityVariation = particleVelocityVariation; }
    void SetParticleSize(float particleSize) { m_particleSize = particleSize; }
    void SetParticleSpawnFrequency(float particleSpawnFrequency) { m_particleSpawnFrequency = particleSpawnFrequency; }
    void SetParticleLifetime(float particleLifetime) { m_particleLifetime = particleLifetime; }
    void SetParticleFadeout(float particleFadeout) { m_particleFadeout = particleFadeout; }
    void SetMaxParticles(int maxParticles) { m_maxParticles = maxParticles; }
    
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

	void EmitParticles();
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
    int m_maxParticles;

    // Particle management data members
    float m_accumulatedTime;
    std::list<ParticleType> m_particles;

	// Fireball effect
	Graphic* m_fireball;
	int m_numFireballs;
    Coord m_fireballVelocity;
    Coord m_fireballVelocityVariation;
    float m_fireballFadeout;
    float m_fireballLifetime;
	float m_fireballRotationVariation;
    float m_fireballTintR, m_fireballTintG, m_fireballTintB, m_fireballAlpha;
    float m_fireballTintRVar, m_fireballTintGVar, m_fireballTintBVar, m_fireballAlphaVar;
	float m_fireballDarken;
};