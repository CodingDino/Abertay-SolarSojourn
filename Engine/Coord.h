// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//  
// Coord
//      Coord is a coordinate set (x,y,z) which measures the position of 
//      something in the game world. The data members for this class will be 
//      public, like a struct.
#pragma once

// |----------------------------------------------------------------------------|
// |                          Class Definition: Coord                           |
// |----------------------------------------------------------------------------|
class Coord {

public:
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~   Constructors   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    Coord () : x(0), y(0), z(0) {}
    Coord (const float newx, const float newy, const float newz) : x(newx), y(newy), z(newz){}
    Coord (const Coord& old_coord) : x(old_coord.x), y(old_coord.y), z(old_coord.z) {}
    
    //~~~~~~~~~~~~~~~~~~~~~~   Operator Overloading   ~~~~~~~~~~~~~~~~~~~~~~~~~//
    Coord operator+(const Coord& rhs);
    Coord operator+(const float& rhs);
    Coord operator+=(const Coord& rhs);
    Coord operator+=(const float& rhs);
    Coord operator-(const Coord& rhs);
    Coord operator-(const float& rhs);
    Coord operator-=(const Coord& rhs);
    Coord operator-=(const float& rhs);
    Coord operator*(const float& rhs);
    Coord operator*=(const float& rhs);
    Coord operator/(const float& rhs);
    Coord operator/=(const float& rhs);
    Coord operator=(const Coord& rhs);
    Coord operator=(const float& rhs);
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~   Data Members   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    float x, y, z;

};
