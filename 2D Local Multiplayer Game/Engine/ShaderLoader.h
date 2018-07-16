//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    ShaderLoader.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

#pragma once

// Library Includes //
#include <iostream>

// OpenGL Library Includes //
#include "glew.h"
#include "freeglut.h"


class ShaderLoader
{
	private:

		std::string ReadShader(const char *filename);
		GLuint CreateShader(GLenum shaderType,
			std::string source,
			const char* shaderName);

	public:
		ShaderLoader(void);
		~ShaderLoader(void);
		GLuint CreateProgram(const char* VertexShaderFilename,
			const char* FragmentShaderFilename);

};
