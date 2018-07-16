//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    Camera.h
// Description		:    Log Manager
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //
#include <memory>

// Engine Includes //
#include "UIText.h"

#pragma once
class LogManager
{
public:

	void Init();
	void Render();

	void DisplayLogMessage(std::string _Message);

	std::shared_ptr<UIText> LoadingMessage;

	// Singleton
public:
	static std::shared_ptr<LogManager> GetInstance();
	static void DestoryInstance();
	~LogManager(); // Shared pointer has to be able to call destructor so can't be private

private:
	static std::shared_ptr<LogManager> m_pLogManager;
	LogManager();
	LogManager(LogManager const&);              // Don't Implement
	void operator=(LogManager const&); // Don't implement
};

