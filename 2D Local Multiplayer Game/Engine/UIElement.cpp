//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    UIElement.cpp
// Description    	:    main implementation for UIElement
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //

// OpenGL Library Includes //

// Engine Includes //

// Local Includes //

// This Includes //
#include "UIElement.h"

// Static Variables //

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
UIElement::UIElement(glm::vec2 _Position, float _fRotation, glm::vec4 _Colour)
	: position(_Position), fRotation(_fRotation), Colour(_Colour)
{
}

/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
UIElement::~UIElement()
{
}

/************************************************************
#--Description--#:	Overridable render UI Element to the screen
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void UIElement::DrawUIElement()
{

}

/************************************************************
#--Description--#: 	Base Update called every frame to check before called derived Update
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void UIElement::BaseUpdate()
{
	if (!bActive)
		return;
	Update();
}

/************************************************************
#--Description--#: 	Updated every frame
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void UIElement::Update()
{
}

/************************************************************
#--Description--#:  Sets position
#--Author--#: 		Alex Coultas
#--Parameters--#:	New position to set to
#--Return--#: 		NA
************************************************************/
void UIElement::SetPosition(glm::vec2 _NewPosition)
{
	position = _NewPosition;
}

/************************************************************
#--Description--#:  Rotates UI Element
#--Author--#: 		Alex Coultas
#--Parameters--#:	angle to rotate by
#--Return--#: 		NA
************************************************************/
void UIElement::Rotate(float fAngle)
{
	fRotation += fAngle;
}

/************************************************************
#--Description--#:  Sets UI Element rotation
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes in new rotation
#--Return--#: 		NA
************************************************************/
void UIElement::SetRotation(float _fRotation)
{
	fRotation = _fRotation;
}

/************************************************************
#--Description--#:  Set whether the UI Element is active
#--Author--#: 		Alex Coultas
#--Parameters--#:	Bool wheather it set active
#--Return--#: 		NA
************************************************************/
void UIElement::SetActive(bool _bIsActive)
{
	bActive = _bIsActive;
}

/************************************************************
#--Description--#:  Retreives UI Element Position
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		Vector 2 of current position
************************************************************/
glm::vec2 UIElement::GetPosition()
{
	return position;// +(glm::vec2)Camera::GetInstance()->GetCameraPosition();
}
