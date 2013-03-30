// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Singleton
//      Based on example class by Henry Fortuna. Singleton design pattern.
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <assert.h>


// |----------------------------------------------------------------------------|
// |							 Class: Singleton								|
// |----------------------------------------------------------------------------|
template <typename T> class Singleton
{

public:

	//|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
	Singleton()
	{
	    // Sets up the one and only instance
		assert(!ms_Singleton);

		ms_Singleton = static_cast<T*>(this);
	}
	Singleton(const Singleton&)
    {
	    // This should always fail, just putting it here for completeness.
		assert(!ms_Singleton);
		ms_Singleton = static_cast<T*>(this);
    }
	~Singleton()
	{
	    // Destroys the one and only instance
		assert(ms_Singleton);
		ms_Singleton = 0;
	}

	// Returns the singleton
	static T& GetSingleton()
	{
		assert(ms_Singleton);
		return (*ms_Singleton);
	}

	// Returns a pointer to the singleton
	static T* GetRef()
	{
		return ms_Singleton;
	}

private:

	//|-----------------------------Private Data Members-------------------------|

	// The one and only instance of this class
	static T * ms_Singleton;

};


// Static reference initialization
template <typename T> T * Singleton <T>::ms_Singleton = 0;