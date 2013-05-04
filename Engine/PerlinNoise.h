// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//  
// PerlinNoise
//      Perlin Noise generator class
#pragma once


// |----------------------------------------------------------------------------|
// |                        Class Definition: PerlinNoise                       |
// |----------------------------------------------------------------------------|
class PerlinNoise {

public:
    
    //|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
    PerlinNoise();
    PerlinNoise(double _persistence, double _frequency, double _amplitude, int _octaves, int _randomseed);
    
    // Getters
    double GetHeight(double x, double y) const;
    double Persistence() const { return persistence; }
    double Frequency()   const { return frequency;   }
    double Amplitude()   const { return amplitude;   }
    int    Octaves()     const { return octaves;     }
    int    RandomSeed()  const { return randomseed;  }
    
    // Setters
    void Set(double _persistence, double _frequency, double _amplitude, int _octaves, int _randomseed);
    void SetPersistence(double _persistence) { persistence = _persistence; }
    void SetFrequency(  double _frequency)   { frequency = _frequency;     }
    void SetAmplitude(  double _amplitude)   { amplitude = _amplitude;     }
    void SetOctaves(    int    _octaves)     { octaves = _octaves;         }
    void SetRandomSeed( int    _randomseed)  { randomseed = _randomseed;   }

private:
    
    //|-------------------------------Private Functions-------------------------|

    double Total(double i, double j) const;
    double GetValue(double x, double y) const;
    double Interpolate(double x, double y, double a) const;
    double Noise(int x, int y) const;
    
private:

    //|-----------------------------Private Data Members------------------------|

    double persistence, frequency, amplitude;
    int octaves, randomseed;
};