//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    UIImage.cpp
// Description    	:    main implementation for UIImage
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //

// OpenGL Library Includes //
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

// Engine Includes //
#include "Shader.h"

// Local Includes //

// This Includes //
#include "UIImage.h"

// Static Variables //


/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
UIImage::UIImage(glm::vec2 _Position, Utils::EANCHOR _anchor, float _fRotation, glm::vec4 _Colour, int _iWidth, int _iHeight)
	: UIElement(_Position, _fRotation, _Colour), iWidth(_iWidth), iHeight(_iHeight), ImageAnchor(_anchor)
{
	VAO = Shader::BindArray((float)iWidth, (float)iHeight, _Colour);
}

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
UIImage::UIImage(glm::vec2 _Position, Utils::EANCHOR _anchor, float _fRotation, glm::vec4 _Colour, int _iWidth, int _iHeight, const char * TextureSource, int _DrawMode)
	: UIElement(_Position, _fRotation, _Colour), iWidth(_iWidth), iHeight(_iHeight), ImageAnchor(_anchor)
{
	VAO = Shader::BindUITextureArray((float)iWidth, (float)iHeight, _Colour, TextureSource, texture, _DrawMode);
	bHasTexture = true;
}
/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
UIImage::~UIImage()
{
}

/************************************************************
#--Description--#:	Render to the screen
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void UIImage::DrawUIElement()
{	
	if (!bActive)
		return;
	if (bHasTexture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	else
	{
	}
	glEnable(GL_BLEND);
	glUseProgram(Shader::Programs["UIprogram"]);
	glm::mat4 proj = glm::ortho(0.0f, (GLfloat)Camera::GetInstance()->SCR_WIDTH, 0.0f, (GLfloat)Camera::GetInstance()->SCR_HEIGHT);
	glm::vec3 NewPos = glm::vec3(position, 0);
	NewPos.y = Camera::GetInstance()->SCR_HEIGHT - position.y;
	NewPos = Utils::GetAncoredPosition2D(NewPos, glm::vec2(iWidth, iHeight), ImageAnchor);// = glm::vec3(position.x, Camera::GetInstance()->SCR_HEIGHT - position.y, 0);
	
	proj = glm::translate(proj, NewPos);	
	glUniformMatrix4fv(glGetUniformLocation(Shader::Programs["UIprogram"], "proj"), 1, GL_FALSE, glm::value_ptr(proj));
	glUniform1i(glGetUniformLocation(Shader::Programs["UIprogram"], "bIsTex"), bHasTexture);
	glUniform4f(glGetUniformLocation(Shader::Programs["UIprogram"], "Color"), Colour.r, Colour.g, Colour.b, Colour.a);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

/************************************************************
#--Description--#:  Gets position from anchor and current position
#--Author--#: 		Alex Coultas
#--Parameters--#:	Element position, current anchor, with width and height of the object
#--Return--#: 		Returns vector 2 of new position
************************************************************/
glm::vec2 UIImage::GetPositionFromAnchor(glm::vec2 _Position, Utils::EANCHOR _anchor, int _iWidth, int _iHeight)
{
	switch (_anchor)
	{
	case Utils::TOP_LEFT:
		return glm::vec3(_Position.x + _iWidth / 2, _Position.y + _iHeight / 2, 0);
		break;
	case Utils::TOP_RIGHT:
		return glm::vec3(_Position.x - _iWidth / 2, _Position.y + _iHeight / 2, 0);
		break;
	case Utils::TOP_CENTER:
		return glm::vec3(_Position.x, _Position.y + _iHeight / 2, 0);
		break;
	case Utils::CENTER_LEFT:
		return glm::vec3(_Position.x + _iWidth / 2, _Position.y, 0);
		break;
	case Utils::CENTER:
		return glm::vec3(_Position.x, _Position.y, 0);
		break;
	case Utils::CENTER_RIGHT:
		return glm::vec3(_Position.x - _iWidth / 2, _Position.y, 0);
		break;
	case Utils::BOTTOM_LEFT:
		return glm::vec3(_Position.x + _iWidth / 2, _Position.y - _iHeight / 2, 0);
		break;
	case Utils::BOTTOM_CENTER:
		return glm::vec3(_Position.x, _Position.y - _iHeight / 2, 0);
		break;
	case Utils::BOTTOM_RIGHT:
		return glm::vec3(_Position.x - _iWidth / 2, _Position.y - _iHeight / 2, 0);
		break;
	default:
		break;
	}
	return glm::vec3();
}
