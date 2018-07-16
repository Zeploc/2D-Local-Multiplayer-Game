//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    Text.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //
#include <string>
#include <map>
#include <vector>

// OpenGL Library Includes //
#include <glew.h>
#include <freeglut.h>
#include <glm\common.hpp>

// Engine Includes //
#include "ShaderLoader.h"
#include "Utils.h"

#pragma once
class Text
{
public:
	struct Character
	{
		GLuint TextureID;	//Texture ID
		glm::ivec2 Size;	// Size of glyph
		glm::ivec2 Bearing;	// Position of glyph
		GLuint Advance;		// How far to move for the next character
	};
	struct cFont
	{
		std::map<GLchar, Character> Characters;
		std::string sPathName;
		GLuint VAO;
		GLuint VBO;
		int fPSize;
	};
	
	static std::vector<cFont> Fonts;
	
	static void Render(std::string Text, std::string Font, int iSize, glm::vec2 Position, glm::vec3 colour, Utils::EANCHOR _Anchor);


};

