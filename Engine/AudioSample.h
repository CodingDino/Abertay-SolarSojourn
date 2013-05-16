// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// AudioSample
//      Holds one audio sample, plays and sets its volume
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "SoundManager.h"


// |----------------------------------------------------------------------------|
// |                            Class: AudioSample                              |
// |----------------------------------------------------------------------------|
class AudioSample
{
public:

    //|-------------------------------Public Functions--------------------------|

    // Constructors and Destructors
	AudioSample() : 
		m_soundBuffer(0),
		m_volume(DSBVOLUME_MAX)
	{}

    // Initiallization and shutdown
    bool Initialize(const char* name);
    void Shutdown();

    // Getter functions
	IDirectSoundBuffer8* GetSoundBuffer() {return m_soundBuffer;}
	LONG GetVolume() {return m_volume;}

	// Setter functions
	void SetVolume(LONG val) {m_volume = val; if (m_soundBuffer) m_soundBuffer->SetVolume(val);}

	// Sound functions
	void PlaySound() {if (m_soundBuffer) m_soundBuffer->Play(0, 0, 0);}
	void PlaySoundLoop() {if (m_soundBuffer) m_soundBuffer->Play(0, 0, DSBPLAY_LOOPING);}
	void StopSound() {if (m_soundBuffer) m_soundBuffer->Stop(); }

protected:

    //|----------------------------Protected Data Members-----------------------|

    // Texture
    IDirectSoundBuffer8* m_soundBuffer;
	
	// Volume sliders
	LONG m_volume;

};