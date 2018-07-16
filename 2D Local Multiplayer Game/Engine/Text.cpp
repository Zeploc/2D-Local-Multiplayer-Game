//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Text.cpp
// Description    	:    main implementation for Text
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //
#include <map>

// OpenGL Library Includes //
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

// Engine Includes //
#include "Camera.h"
#include "Shader.h"

// Local Includes //

// This Includes //
#include "Text.h"

// Static Variables //
std::vector<Text::cFont> Text::Fonts;

/************************************************************
#--Description--#:  Render text given attrbiutes
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes text, font, size, position, colour and draw anchor
#--Return--#: 		NA
************************************************************/
void Text::Render(std::string Text, std::string Font, int iSize, glm::vec2 Position, glm::vec3 colour, Utils::EANCHOR _Anchor)
{
	cFont TextFont;
	for (auto it : Fonts)
	{
		if (it.sPathName == Font && it.fPSize == iSize)
		{
			TextFont = it;
			break;
		}
	}
	if (TextFont.sPathName != Font || TextFont.fPSize != iSize)
	{
		TextFont = Shader::AddFont(Font, iSize);
	}
	int iTextWidth = 0;
	for (auto i = Text.begin(); i != Text.end(); ++i)
	{
		iTextWidth += (TextFont.Characters[*i].Advance >> 6);
	}
	glm::vec2 NewPos = Utils::GetTextAncoredPosition(Position, glm::vec2(iTextWidth, iSize), _Anchor);
	int YOffset = TextFont.Characters[0].Bearing.y / 2;
	if (YOffset == 0)
		YOffset = (int)((float)iSize * 0.35f);
	glm::vec2 textPos = glm::vec2(NewPos.x, (GLfloat)Camera::GetInstance()->SCR_HEIGHT - NewPos.y - YOffset);// - TextFont.Characters[0].Size.y / 2);
	// Enable blending
	glCullFace(GL_BACK); // Cull the Back faces
	glFrontFace(GL_CW); // Front face is Clockwise order
	glEnable(GL_CULL_FACE); // Turn on the back face culling
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Activate corresponding render state
	//glUseProgram(Shader::Textprogram);
	glUniform3f(glGetUniformLocation(Shader::Programs["TextUIprogram"], "textColor"), colour.x, colour.y, colour.z);
	glm::mat4 proj = glm::ortho(0.0f, (GLfloat)Camera::GetInstance()->SCR_WIDTH, 0.0f, (GLfloat)Camera::GetInstance()->SCR_HEIGHT);
	glUniformMatrix4fv(glGetUniformLocation(Shader::Programs["TextUIprogram"], "proj"), 1, GL_FALSE, glm::value_ptr(proj));
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(TextFont.VAO);

	// Iterate through the Characters
	for (std::string::const_iterator c = Text.begin(); c != Text.end(); c++)
	{
		Character ch = TextFont.Characters[*c];
		GLfloat xpos = textPos.x + ch.Bearing.x;// *scale;
		GLfloat ypos = textPos.y - (ch.Size.y - ch.Bearing.y);// *scale;
		GLfloat w = (GLfloat)ch.Size.x;// *scale;
		GLfloat h = (GLfloat)ch.Size.y;// *scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos, ypos + h, 0.0, 0.0 },{ xpos + w, ypos + h, 1.0, 0.0 },{ xpos + w, ypos, 1.0, 1.0 },
			{ xpos, ypos + h, 0.0, 0.0 },{ xpos + w, ypos, 1.0, 1.0 },{ xpos, ypos, 0.0, 1.0 },
		};
		// Render the glyph texture over the quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		glBindBuffer(GL_ARRAY_BUFFER, TextFont.VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for the next glyph
		textPos.x += (ch.Advance >> 6);// *scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}


