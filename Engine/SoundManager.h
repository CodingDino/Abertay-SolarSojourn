// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// SoundManager
//		The SoundManager encapsulates the DirectSound functionality as well as the 
//		.wav audio loading and playing capabilities.
#pragma once

// |----------------------------------------------------------------------------|
// |								 Linking									|
// |----------------------------------------------------------------------------|
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
 
 
// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>
#include "Singleton.h"
#include "Util.h"

 
// |----------------------------------------------------------------------------|
// |						   Class: SoundManager								|
// |----------------------------------------------------------------------------|
class SoundManager : public Singleton<SoundManager>
{
private:
	
	//|------------------------------Type Declarations--------------------------|

	struct WaveHeaderType
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};
 
public:

	//|-------------------------------Public Functions--------------------------|
	
	// Constructors and Destructors
	SoundManager();
	SoundManager(const SoundManager&);
	~SoundManager();

	// Initialization and shutdown
	bool Initialize();
	void Shutdown();
 
	// Loads/shuts down a wave file
	bool LoadWaveFile(const char* name, IDirectSoundBuffer8** soundPointer);
	void ShutdownWaveFile(IDirectSoundBuffer8** soundPointer);
 
private:

	//|------------------------------Private Functions--------------------------|
	
	// Initializes/shuts down the direct sound portion of the object
	bool InitializeDirectSound();
	void ShutdownDirectSound();
 
private:
	
	//|-----------------------------Private Data Members------------------------|

	IDirectSound8* m_DirectSound;
	IDirectSoundBuffer* m_primaryBuffer;
};