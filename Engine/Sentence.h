// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Sentence
//      Contains model information for set of text
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Model.h"
#include "Font.h"


// |----------------------------------------------------------------------------|
// |                           Class: TextModel                                 |
// |----------------------------------------------------------------------------|
class Sentence : public Model
{

public:

    //|-------------------------------Public Functions--------------------------|
    
    // Constructors and Destructors
	Sentence();
	Sentence(const Sentence&);
	virtual ~Sentence();
	
    // Initialization and shutdown
	virtual bool Initialize() {return Initialize(100);}
	virtual bool Initialize(int maxLength);

    // Updates the buffers based on the supplied string and font
    virtual bool UpdateBuffers(char* string, Font* font);
	
protected:

    //|------------------------------Protected Functions------------------------|

    // Populates buffers with data
    virtual bool PopulateBuffers(VertexType*& vertices, unsigned long*& indices);
	
protected:

    //|----------------------------Protected Data Members-----------------------|
	int m_maxLength;
};