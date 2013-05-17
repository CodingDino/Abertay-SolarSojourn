// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// AudioSample
//      Holds one audio sample, plays and sets its volume


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "AudioSample.h"


// |----------------------------------------------------------------------------|
// |                               Initialize                                   |
// |----------------------------------------------------------------------------|
bool AudioSample::Initialize(const char* name)
{
	return SoundManager::GetRef()->LoadWaveFile(name,&m_soundBuffer);
}


// |----------------------------------------------------------------------------|
// |                                Shutdown                                    |
// |----------------------------------------------------------------------------|
void AudioSample::Shutdown()
{
	m_soundBuffer->Release();
	m_soundBuffer = 0;
}