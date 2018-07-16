//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    Camera.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//


#pragma once
class Time
{
public:
	Time();
	~Time();

	static void Update();

	static double dCurrentTime;
	static double dTimeDelta;
	static double dFPS;
private:
	static double dPrevTime;
};


