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
	int i(0);

	/*First we create an array of the FontType structure. The size of the array 
	is set to 95 as that is the number of characters in the texture and hence the 
	number of indexes in the fontdata.txt file.*/

	// Create the font spacing buffer.
	m_Font = new FontType[95];
	if(!m_Font)
	{
		return false;
	}

	// Load in the xml file
    tinyxml2::XMLDocument doc;
    doc.LoadFile(filename);

	// Font attributes
	// Get font name
	m_name = new char[strlen(doc.FirstChildElement("Font")->Attribute("family"))+1];
	m_name = strcpy(m_name,doc.FirstChildElement("Font")->Attribute("family"));
	// Get font style
	m_name = new char[strlen(doc.FirstChildElement("Font")->Attribute("style"))+1];
	m_name = strcpy(m_name,doc.FirstChildElement("Font")->Attribute("style"));
	// Get font size
	m_size = atoi(doc.FirstChildElement("Font")->Attribute("size"));
	// Get font height
	m_fontHeight = atoi(doc.FirstChildElement("Font")->Attribute("height"));


	// Read in each character's information
	tinyxml2::XMLElement* character(0);
	while (doc.FirstChildElement("Font")->FirstChildElement("Char"));
	{
		// Get the element to process
		character = doc.FirstChildElement("Font")->FirstChildElement("Char");

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
		m_Font[i].right = m_Font[i].left + atoi(strtok(NULL," "));
		m_Font[i].top = atoi(strtok(NULL," "));
		m_Font[i].bottom = m_Font[i].top + atoi(strtok(NULL," "));

		// Calculate U and V coordinates
		m_Font[i].uLeft = (float)m_Font[i].left / (float)m_width;
		m_Font[i].uRight = (float)m_Font[i].right / (float)m_width;
		m_Font[i].vTop = (float)m_Font[i].top / (float)m_height;
		m_Font[i].vBottom = (float)m_Font[i].bottom / (float)m_height;

		// Get character code
		m_Font[i].code = character->Attribute("code")[0];

		// Remove this character for the next round of processing
		doc.FirstChildElement("Font")->DeleteChild(character);

		// Increment array index
		i++;
	}

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
void Font::BuildVertexArray(void* vertices, char* sentence, float drawX, float drawY)
{
	VertexType* vertexPtr;
	int numLetters, index, i, letter;

	// Coerce the input vertices into a VertexType structure.
	vertexPtr = (VertexType*)vertices;

	// Get the number of letters in the sentence.
	numLetters = (int)strlen(sentence);

	// Initialize the index to the vertex array.
	index = 0;

	// Draw each letter onto a quad.
	for(i=0; i<numLetters; i++)
	{
		letter = ((int)sentence[i]) - ' ';

		// If the letter is a space then just move over three pixels.
		//if(letter == 0)
		//{
		//	drawX = drawX + 3.0f;
		//}
		//else
		//{
		// First triangle in quad.
		vertexPtr[index].position = D3DXVECTOR3(drawX, drawY, 0.0f);  // Top left.
		vertexPtr[index].texture = D3DXVECTOR2(m_Font[letter].uLeft,m_Font[letter].vTop);
		index++;

		vertexPtr[index].position = D3DXVECTOR3((drawX + m_Font[letter].width), (drawY - m_Font[letter].height), 0.0f);  // Bottom right.
		vertexPtr[index].texture = D3DXVECTOR2(m_Font[letter].uRight,m_Font[letter].vBottom);
		index++;

		vertexPtr[index].position = D3DXVECTOR3(drawX, (drawY - m_Font[letter].height), 0.0f);  // Bottom left.
		vertexPtr[index].texture = D3DXVECTOR2(m_Font[letter].uLeft,m_Font[letter].vBottom);
		index++;

		// Second triangle in quad.
		vertexPtr[index].position = D3DXVECTOR3(drawX, drawY, 0.0f);  // Top left.
		vertexPtr[index].texture = D3DXVECTOR2(m_Font[letter].uLeft,m_Font[letter].vTop);
		index++;

		vertexPtr[index].position = D3DXVECTOR3(drawX + m_Font[letter].width, drawY, 0.0f);  // Top right.
		vertexPtr[index].texture = D3DXVECTOR2(m_Font[letter].uRight,m_Font[letter].vTop);
		index++;

		vertexPtr[index].position = D3DXVECTOR3((drawX + m_Font[letter].width), (drawY - m_Font[letter].height), 0.0f);  // Bottom right.
		vertexPtr[index].texture = D3DXVECTOR2(m_Font[letter].uRight,m_Font[letter].vBottom);
		index++;

		// Update the x location for drawing by the size of the letter and one pixel.
		drawX = drawX + m_Font[letter].width;
		//}
	}

	return;
}