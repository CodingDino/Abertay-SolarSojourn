// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Coord
//      Coord is a coordinate set (x,y,z) which measures the position of 
//      something in the game world. The data members for this class will be 
//      public, like a struct.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Coord.h"


// |----------------------------------------------------------------------------|
// |								  Utility			                        |
// |----------------------------------------------------------------------------|
std::string Coord::ToString() {
    std::string string = "";
	string += "(";
	string += std::to_string(static_cast<long long>(x));
	string += ",";
	string += std::to_string(static_cast<long long>(y));
	string += ",";
	string += std::to_string(static_cast<long long>(z));
	string += ")";
	return string;
}


// |----------------------------------------------------------------------------|
// |                           Operator Overloading                             |
// |----------------------------------------------------------------------------|
Coord Coord::operator+(const Coord& rhs) {
    Coord result;
    result.x = x + rhs.x;
    result.y = y + rhs.y;
    result.z = z + rhs.z;
    return result;
}

Coord Coord::operator+(const float& rhs) {
    Coord result;
    result.x = x + rhs;
    result.y = y + rhs;
    result.z = z + rhs;
    return result;
}

Coord Coord::operator+=(const Coord& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Coord Coord::operator+=(const float& rhs) {
    x += rhs;
    y += rhs;
    z += rhs;
    return *this;
}

Coord Coord::operator-(const Coord& rhs) {
    Coord result;
    result.x = x - rhs.x;
    result.y = y - rhs.y;
    result.z = z - rhs.z;
    return result;
}

Coord Coord::operator-(const float& rhs) {
    Coord result;
    result.x = x - rhs;
    result.y = y - rhs;
    result.z = z - rhs;
    return result;
}

Coord Coord::operator-=(const Coord& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

Coord Coord::operator-=(const float& rhs) {
    x -= rhs;
    y -= rhs;
    z -= rhs;
    return *this;
}

Coord Coord::operator*(const float& rhs) {
    Coord result;
    result.x = x * rhs;
    result.y = y * rhs;
    result.z = z * rhs;
    return result;
}

Coord Coord::operator*=(const float& rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

Coord Coord::operator/(const float& rhs) {
    Coord result;
    result.x = x / rhs;
    result.y = y / rhs;
    result.z = z / rhs;
    return result;
}

Coord Coord::operator/=(const float& rhs) {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

Coord Coord::operator=(const Coord& rhs) {
    if (this != &rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
    }
    return *this;
}

Coord Coord::operator=(const float& rhs) {
    x = rhs;
    y = rhs;
    z = rhs;
    return *this;
}

bool Coord::operator==(const Coord& rhs) {
    if (x == rhs.x && y == rhs.y && z == rhs.z)
        return true;
    return false;
}