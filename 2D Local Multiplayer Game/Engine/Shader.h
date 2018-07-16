//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    Shader.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //
#include <string>
#include <map>
#include <memory>

// OpenGL Library Includes //
#include <glew.h>
#include <freeglut.h>
#include <glm/common.hpp>

// Engine Includes //
#include "Text.h"

class ModelObject;

#pragma once
class Shader
{
public:
	Shader();
	~Shader();
	static void CleanUp();

	static void AddProgram(std::string VertexShaderPath, std::string FragmentShaderPath, std::string ShaderName);

	/*static GLuint program;
	static GLuint Textureprogram;
	static GLuint LitTextureprogram;
	static GLuint TextUIprogram;
	static GLuint UIprogram;
	static GLuint CubeMapProgram;
	static GLuint ModelProgram;
	static GLuint ModelProgramLit;
	static GLuint ReflectionProgram;*/
	
	static std::map<std::string, std::shared_ptr<ModelObject>> Models;
	static std::map<const char *, GLuint> Textures;
	static std::map<std::string, GLuint> Programs;
	
	/*static GLuint BindPyramidArray(float fWidth, float fHeight, float fDepth, glm::vec4 Colour);
	static GLuint BindPyramidArray(float fWidth, float fHeight, float fDepth, glm::vec4 Colour, const char *  TextureSource, GLuint& Texture, glm::vec4 UVCoords = glm::vec4(0, 1, 0, 1));

	static GLuint BindSphereArray(float fWidth, float fHeight, float fDepth, glm::vec4 Colour, int& IndiceCount);
	static GLuint BindSphereArray(float fWidth, float fHeight, float fDepth, glm::vec4 Colour, const char *  TextureSource, GLuint& Texture, int& IndiceCount, glm::vec4 UVCoords = glm::vec4(0, 1, 0, 1));
	*/
	static GLuint BindArray(float fWidth, float fHeight, glm::vec4 Colour);
	/*
	static GLuint BindArray(float fWidth, float fHeight, glm::vec4 Colour, const char *  TextureSource, GLuint& Texture, glm::vec2 v2FrameCounts, Utils::AnimInfo& Anim);
	static GLuint BindArray(float fWidth, float fHeight, glm::vec4 Colour, const char *  TextureSource, GLuint& Texture, glm::vec4 UVCoords = glm::vec4(0, 1, 0, 1));
	static GLuint BindArray(float fWidth, float fHeight, glm::vec4 Colour, const char *  TextureSource, GLuint& Texture, int iNum, bool bHorizontal);*/
	static GLuint BindUITextureArray(float fWidth, float fHeight, glm::vec4 Colour, const char *  TextureSource, GLuint& Texture, int _DrawMode);
		
	static Text::cFont AddFont(std::string fontPath, int iPSize);

	static GLuint CreateBuffer(const char * TextureSource, GLuint & Texture, bool bAA, bool bHasNormals = false);
private:
};

