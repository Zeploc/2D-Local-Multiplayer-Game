//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Level.cpp
// Description    	:    Plane Mesh
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// This Includes //
#include "FrameBuffer.h"

// OpenGL Library //
#include <SOIL.h>

// Engine Includes //
#include "Utils.h"
#include "Shader.h"
#include "Time.h"
#include "Camera.h"

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
FrameBuffer::FrameBuffer()
{
	m_fWidth = 1;
	m_fHeight = 1;
	m_iIndicies = 6;
	Colour = { 1.0f, 0.3f, 1.0f, 1.0f };
	TextureSource = "";
	bHasTexture = false;
	UVCoords = { 0, 1, 0, 1 };
	BindFrameBuffer();
	m_eShape = Utils::PLANE;
	program = Shader::Programs["FrameBuffer"];
	SetInitialStates();
}

/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
FrameBuffer::~FrameBuffer()
{
}

/************************************************************
#--Description--#: 	Binds plane with sepcified attributes
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void FrameBuffer::BindFrameBuffer()
{


	glGenTextures(1, &renderTexture);
	glBindTexture(GL_TEXTURE_2D, renderTexture);
	glTexImage2D(GL_TEXTURE_2D,
		0, GL_RGB,
		1280, 720,
		0, //border
		GL_RGB, //format
		GL_UNSIGNED_BYTE, //data type
		NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	//Attach texture to framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, //target buffer
		GL_COLOR_ATTACHMENT0,//attachment, could be
							 //GL_DEPTH_ATTACHMENT or
							 //GL_STENCIL_ATTACHMENT
		GL_TEXTURE_2D, //texture target type
		renderTexture,//texture
		0); // level


	GLuint rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, // must be
		GL_DEPTH24_STENCIL8, //use as depth - stencil buffer
		1280, 720); //viewport width and height;

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, //target
		GL_DEPTH_STENCIL_ATTACHMENT, //attachment
		GL_RENDERBUFFER, //renderbufferTarget
		rbo); // render buffer

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER)
		!= GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	GLfloat Texturedvertices[] = {
		// Positions						// Colors									// Tex Coords
		-1.0f,1.0f, 0.f,		Colour.r, Colour.g, Colour.b, Colour.a,		0, 0,	// Top Left
		1.0f,1.0f, 0.f,		Colour.r, Colour.g, Colour.b, Colour.a,		1, 0, // Top Right
		1.0f,-1.0f, 0.f,		Colour.r, Colour.g, Colour.b, Colour.a,		1, 1, // Bottom Right
		-1.0f,-1.0f, 0.f,		Colour.r, Colour.g, Colour.b, Colour.a,		0, 1, // Bottom Left
	};

	GLuint indices[] = {
		0, 1, 2, // First Triangle
		0, 2, 3 // Second Triangle
	};


	GLuint vbo;
	GLuint ebo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Texturedvertices), Texturedvertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


}

/************************************************************
#--Description--#: 	Rebinds the vao with the colour (not texture)
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void FrameBuffer::Rebind()
{
	BindFrameBuffer();
}


/************************************************************
#--Description--#:	Render Current Mesh to the screen
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void FrameBuffer::Render()
{
	//if (bHasTexture)
	//{
	//	glUseProgram(program);
	//	glEnable(GL_BLEND);
	//}
	//else
	//{
	//	glUseProgram(program);
	//	glDisable(GL_BLEND);
	//}
	//glFrontFace(GL_CW);

	//// ABOVE CALLED FROM DERIVED RENDER
	//glUniform1i(glGetUniformLocation(program, "bIsTex"), bHasTexture);
	//glUniform1i(glGetUniformLocation(program, "bFog"), false);
	//if (bHasTexture)
	//{
	//	glActiveTexture(GL_TEXTURE0);
	//	glBindTexture(GL_TEXTURE_2D, texture);

	//}
	//if (bCullFace) glEnable(GL_CULL_FACE);
	//else glDisable(GL_CULL_FACE);
	//

	//Camera::GetInstance()->SetMVP(Newtransform, program);
	//glBindVertexArray(vao);
	//glDrawElements(GL_TRIANGLES, m_iIndicies, GL_UNSIGNED_INT, 0);

	//glBindVertexArray(0);
	//glBindTexture(GL_TEXTURE_2D, 0);
	//glDisable(GL_CULL_FACE);

	glUseProgram(program);
	
	glActiveTexture(GL_TEXTURE0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindVertexArray(vao);

	glBindTexture(GL_TEXTURE_2D, renderTexture);
	glUniform1i(glGetUniformLocation(program, "tex"), 0);
	glUniform1i(glGetUniformLocation(program, "dTime"), Time::dCurrentTime);

	

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, m_iIndicies, GL_UNSIGNED_INT, 0);
	
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}


