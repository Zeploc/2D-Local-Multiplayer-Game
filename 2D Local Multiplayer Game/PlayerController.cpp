//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Player Controller.cpp
// Description    	:    Controller for individual player
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// This Includes //
#include "PlayerController.h"



PlayerController::PlayerController(int PlayerID)
	: Entity({ {0, 0, 0} ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER)
{
	m_iPlayerID = PlayerID;
}


PlayerController::~PlayerController()
{

}

void PlayerController::Update()
{
	Entity::Update();


}
