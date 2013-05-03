// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Font
//		Holds the font information


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "Font.h"


// |----------------------------------------------------------------------------|
// |						   Default Constructor								|
// |----------------------------------------------------------------------------|
Font::Font() :
	m_Font(0),
	m_name(0),
	m_size(0),
	m_fontHeight(0),
	m_style(0),
	Texture()
{
}

	
// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
Font::Font(const Font& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
Font::~Font()
{
}


// |----------------------------------------------------------------------------|
// |						      Initialize									|
// |----------------------------------------------------------------------------|
bool Font::Initialize(ID3D11Device* device, char* fontFilename, WCHAR* textureFilename) 
{
	DebugLog ("Font::Initialize() called.", DB_GRAPHICS, 1);
	bool result;

	// Initialize the parent class
	result = Texture::Initialize(device,textureFilename);
	if(!result)
	{
		DebugLog("Couldn't initialize font's texture.");
		return false;
	}

	// Load in the text file containing the font data.
	result = LoadFontData(fontFilename);
	if(!result)
	{
		DebugLog("Couldn't load font xml file.");
		return false;
	}

	return true;
}


// |----------------------------------------------------------------------------|
// |						      Shutdown										|
// |----------------------------------------------------------------------------|
void Font::Shutdown()
{
	// Release the font data.
	ReleaseFontData();

	// Shutdown parent
	Texture::Shutdown();

	return;
}


// |----------------------------------------------------------------------------|
// |							 LoadFontData									|
// |----------------------------------------------------------------------------|
bool Font::LoadFontData(char* filename)
{
	DebugLog ("Font::LoadFontData() called.", DB_GRAPHICS, 1);
	int i(0);

	/*First we create an array of the FontType structure. The size of the array 
	is set to 95 as that is the number of characters in the texture and hence the 
	number of indexes in the fontdata.txt file.*/

	// Create the font spacing buffer.
	m_Font = new FontType[95];
	if(!m_Font)
	{
		DebugLog ("Could not create font array.", DB_GRAPHICS, 1);
		return false;
	}

	// Load in the xml file
    tinyxml2::XMLDocument doc;
    doc.LoadFile(filename);

	// Check for parsing errors
	if(doc.Error())
	{
		DebugLog ("Error parsing font xml.", DB_GRAPHICS, 1);
		return false;
	}
	DebugLog ("Font xml parsed.", DB_GRAPHICS, 5);

	// Font attributes
	// Get font name
	m_name = new char[strlen(doc.FirstChildElement("Font")->Attribute("family"))+1];
	m_name = strcpy(m_name,doc.FirstChildElement("Font")->Attribute("family"));
	// Get font style
	m_style = new char[strlen(doc.FirstChildElement("Font")->Attribute("style"))+1];
	m_style = strcpy(m_style,doc.FirstChildElement("Font")->Attribute("style"));
	// Get font size
	m_size = atoi(doc.FirstChildElement("Font")->Attribute("size"));
	// Get font height
	m_fontHeight = atoi(doc.FirstChildElement("Font")->Attribute("height"));
	DebugLog ("Font summary stored.", DB_GRAPHICS, 5);


	// Read in each character's information
	tinyxml2::XMLElement* character(0);
	DebugLog ("Reading font characters...", DB_GRAPHICS, 10);
	while (!doc.FirstChildElement("Font")->NoChildren())
	{

		// Get the element to process
		character = doc.FirstChildElement("Font")->FirstChildElement("Char");
		
		DebugLog (character->Attribute("code"), DB_GRAPHICS, 10);

		// Get character width
		m_Font[i].width = atoi(character->Attribute("width"));
		m_Font[i].height = m_fontHeight;

		// Get character offset
		char* offset = new char[strlen(character->Attribute("offset"))+1];
		offset = strcpy(offset,character->Attribute("offset"));
		m_Font[i].offsetX = atoi(strtok(offset," "));
		m_Font[i].offsetY = atoi(strtok(NULL," "));

		// Get character rectangle
		char* rect = new char[strlen(character->Attribute("rect"))+1];
		rect = strcpy(rect,character->Attribute("rect"));
		m_Font[i].left = atoi(strtok(rect," "));
		m_Font[i].top = atoi(strtok(NULL," "));
		m_Font[i].tWidth = atoi(strtok(NULL," "));
		m_Font[i].right = m_Font[i].left + m_Font[i].tWidth;
		m_Font[i].tHeight = atoi(strtok(NULL," "));
		m_Font[i].bottom = m_Font[i].top + m_Font[i].tHeight;

		// Calculate texture coordinates
		m_Font[i].uLeft = (float)((double)m_Font[i].left / (double)m_width);
		m_Font[i].uRight = (float)((double)m_Font[i].right / (double)m_width);
		m_Font[i].vTop = (float)((double)m_Font[i].top / (double)m_height);
		m_Font[i].vBottom = (float)((double)m_Font[i].bottom / (double)m_height);

		// Get character code
		m_Font[i].code = character->Attribute("code")[0];

		// Remove this character for the next round of processing
		doc.FirstChildElement("Font")->DeleteChild(character);
		
		//DebugLog (character->Attribute("code"), DB_GRAPHICS, 10);

		// Increment array index
		i++;
	}

	DebugLog ("Font character information stored.", DB_GRAPHICS, 5);
	return true;
}


// |----------------------------------------------------------------------------|
// |							ReleaseFontData									|
// |----------------------------------------------------------------------------|
void Font::ReleaseFontData()
{
	// Release the font data array.
	if(m_Font)
	{
		delete [] m_Font;
		m_Font = 0;
	}

	return;
}


// |----------------------------------------------------------------------------|
// |							BuildVertexArray								|
// |----------------------------------------------------------------------------|
void Font::BuildVertexArray(VertexType* vertices, char* sentence, float drawX, float drawY)
{
	DebugLog ("Font::BuildVertexArray() called.", DB_GRAPHICS, 2);
	int numLetters, index, i, letter;

	// Get the number of letters in the sentence.
	numLetters = (int)strlen(sentence);

	// Initialize the index to the vertex array.
	index = 0;

	// Draw each letter onto a quad.
	for(i=0; i<numLetters; i++)
	{
		letter = ((int)sentence[i]) - ' ';

		// First triangle in quad.

		// Top left
		vertices[index].position = D3DXVECTOR3(
			drawX + m_Font[letter].offsetX, 
			drawY - m_Font[letter].offsetY, 
			0.0f);
		vertices[index].texture = D3DXVECTOR2(m_Font[letter].uLeft,m_Font[letter].vTop);
		index++;

		// Bottom right
		vertices[index].position = D3DXVECTOR3(
			drawX + m_Font[letter].offsetX + m_Font[letter].tWidth, 
			drawY - m_Font[letter].offsetY - m_Font[letter].tHeight
			, 0.0f);
		vertices[index].texture = D3DXVECTOR2(m_Font[letter].uRight,m_Font[letter].vBottom);
		index++;

		// Bottom left
		vertices[index].position = D3DXVECTOR3(
			drawX + m_Font[letter].offsetX, 
			drawY - m_Font[letter].offsetY - m_Font[letter].tHeight, 
			0.0f);  
		vertices[index].texture = D3DXVECTOR2(m_Font[letter].uLeft,m_Font[letter].vBottom);
		index++;

		// Second triangle in quad.

		// Top left
		vertices[index].position = D3DXVECTOR3(
			drawX + m_Font[letter].offsetX, 
			drawY - m_Font[letter].offsetY, 
			0.0f);
		vertices[index].texture = D3DXVECTOR2(m_Font[letter].uLeft,m_Font[letter].vTop);
		index++;

		// Top right
		vertices[index].position = D3DXVECTOR3(
			drawX + m_Font[letter].offsetX + m_Font[letter].tWidth, 
			drawY - m_Font[letter].offsetY, 
			0.0f);  
		vertices[index].texture = D3DXVECTOR2(m_Font[letter].uRight,m_Font[letter].vTop);
		index++;

		// Bottom right
		vertices[index].position = D3DXVECTOR3(
			drawX + m_Font[letter].offsetX + m_Font[letter].tWidth, 
			drawY - m_Font[letter].offsetY - m_Font[letter].tHeight
			, 0.0f);
		vertices[index].texture = D3DXVECTOR2(m_Font[letter].uRight,m_Font[letter].vBottom);
		index++;

		// Update the x location for drawing by the size of the letter and one pixel.
		drawX = drawX + m_Font[letter].width;
		
	}

	return;
}