// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Text
//      Contains data for a single text object, including texture and rendering 
//		method.
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Graphic.h"
#include "Sentence.h"
#include "Font.h"


// |----------------------------------------------------------------------------|
// |                               Class: Text			                        |
// |----------------------------------------------------------------------------|
class Text : public Graphic
{

public:

    //|-------------------------------Public Functions--------------------------|
    
    // Constructors and Destructors
    Text();
    Text(const Text&);
    virtual ~Text();
    
    // Initialization and shutdown
    virtual bool Initialize();
    virtual void Shutdown();

	// Getter and Setter functions
	char* GetText();
	void SetText(const char*); // Rebuilds the buffer from Font.
	void SetColor(float r, float g, float b);
    void SetFont(std::string name) { m_texture = AssetManager::GetRef()->GetFont(name); }


protected:

    //|------------------------------Protected Functions------------------------|
    
    // Performs the transforms on the graphic
    virtual D3DXMATRIX PerformTransforms(Coord position);

protected:

    //|----------------------------Protected Data Members-----------------------|

	// Screen location information
	Coord m_previousPosition;

	// String to be rendered
	char* m_string;

};