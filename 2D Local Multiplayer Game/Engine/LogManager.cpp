//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    LogManager.cpp
// Description    	:    Manages Log messages
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// This Includes //
#include "LogManager.h"

// Library Includes //
#include <iostream>

// Static Variables //
std::shared_ptr<LogManager> LogManager::m_pLogManager;

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
LogManager::LogManager()
{
	LoadingMessage = std::make_shared<UIText>(UIText({ Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2 }, 0, { 0.7f, 0.7f, 0.7f, 1.0f }, "Log Message", "Resources/Fonts/Roboto-Medium.ttf", 30, Utils::CENTER));;
}

/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
LogManager::~LogManager()
{
}

void LogManager::Init()
{
	DisplayLogMessage("Loading Game");
}

void LogManager::Render()
{
	LoadingMessage->DrawUIElement();
}

void LogManager::DisplayLogMessage(std::string _Message)
{
	std::cout << _Message << std::endl;
	LoadingMessage->sText = _Message;
	glutPostRedisplay();
}

/************************************************************
#--Description--#:  Retrieves static instance pointer to this class
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		Returns static pointer to self
************************************************************/
std::shared_ptr<LogManager> LogManager::GetInstance()
{
	if (!m_pLogManager) // null or doesn't exist
	{
		m_pLogManager = std::shared_ptr<LogManager>(new LogManager());
	}
	return m_pLogManager;
}

/************************************************************
#--Description--#:  Destroys static instance pointer to this class
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
void LogManager::DestoryInstance()
{
	m_pLogManager = nullptr;
}