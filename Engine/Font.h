// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Font
//		Holds the font information
#pragma once


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
#include "Texture.h"
#include "tinyxml2.h"
using namespace std;

// |----------------------------------------------------------------------------|
// |						        Class: Font									|
// |----------------------------------------------------------------------------|
class Font : public Texture
{

private:

	//|---------------------------------Type Defs------------------------------|

	struct FontType
	{
		int left, right, top, bottom;
		float uLeft, uRight, vTop, vBottom;
		int offsetX, offsetY;
		int width, height;
		char code;
	};
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:

	//|-------------------------------Public Functions--------------------------|
	
    // Constructors and Destructors
	Font();
	Font(const Font&);
	virtual ~Font();
	
    // Initialization and shutdown
	virtual bool Initialize(ID3D11Device* device, char* fontFilename, WCHAR* textureFilename);
    virtual void Shutdown();

	// Builds the array of triangles that will render the characte sentence
	void BuildVertexArray(void*, char*, float, float);

private:

	//|-------------------------------Private Functions--------------------------|

	// Loads the given font from file
	bool LoadFontData(char*);

	// Releases the font data
	void ReleaseFontData();

	//|-----------------------------Private Data Members------------------------|
	FontType* m_Font;
	char* m_name;
	int m_size;
	int m_fontHeight;
	char* m_style;
};