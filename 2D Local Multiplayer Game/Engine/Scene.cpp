//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Scene.cpp
// Description    	:    main implementation for Scene
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //

// OpenGL Library Includes //

// Engine Includes //
#include "Input.h"
#include "Camera.h"
#include "UIText.h"
#include "Shader.h"
#include "Plane.h"
#include "UIButton.h"

// Local Includes //

// This Includes //
#include "Scene.h"

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
Scene::Scene(std::string sSceneName)
	: SceneName(sSceneName)
{

}

/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
Scene::~Scene()
{
	DeleteScene();
}

/************************************************************
#--Description--#:	Delete all entities in scene
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Scene::DeleteScene()
{
	for (auto it : Entities)
	{
		it = nullptr;
	}
	for (auto it : UIElements)
	{
		it = nullptr;
	}
}

/************************************************************
#--Description--#:	Render Scene to the screen
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Scene::RenderScene()
{
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	for (unsigned int i = 0; i < Entities.size(); i++)
	{
		//if (it->transform.Scale.x < 0)	// || it->transform.Scale.y < 0 || it->transform.Scale.z < 0)
		//{
		//	glCullFace(GL_FRONT);		// Switches to front culling if scale is negative
		//}
		//else glCullFace(GL_BACK);		// Cull the Back faces as per normal
		Entities[i]->DrawEntity();
	}
	glDisable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);
	for (auto it : UIElements)
	{
		it->DrawUIElement();
	}
}

/************************************************************
#--Description--#:	Add entity to scene
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Entity to add
#--Return--#: 		NA
************************************************************/
void Scene::AddEntity(std::shared_ptr<Entity> _Entity)
{
	Entities.push_back(_Entity);
}

/************************************************************
#--Description--#:	Add entity to scene
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Entity parameters to add
#--Return--#: 		NA
************************************************************/
std::shared_ptr<Entity> Scene::AddEntity(Utils::Transform _Transform, float _fWidth, float _fHeight, Utils::EANCHOR _Anchor, glm::vec4 _Colour)
{
	std::shared_ptr<Entity> NewEnt = std::make_shared<Entity>(_Transform,  _Anchor);
	std::shared_ptr<Plane> Newmesh = std::make_shared<Plane>(_fWidth, _fHeight, _Colour);
	NewEnt->AddMesh(Newmesh);
	Entities.push_back(NewEnt);
	return NewEnt;
}

/************************************************************
#--Description--#:	Add entity to scene
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Entity parameters to add
#--Return--#: 		NA
************************************************************/
std::shared_ptr<Entity> Scene::AddEntity(Utils::Transform _Transform, float _fWidth, float _fHeight, Utils::EANCHOR _Anchor, glm::vec4 _Colour, const char * TextureSource, int iCount, bool bHorizontal)
{
	std::shared_ptr<Entity> NewEnt = std::make_shared<Entity>(_Transform, _Anchor);
	std::shared_ptr<Plane> Newmesh = std::make_shared<Plane>(_fWidth, _fHeight, _Colour, TextureSource, iCount, bHorizontal);
	NewEnt->AddMesh(Newmesh);
	Entities.push_back(NewEnt);
	return NewEnt;
}

/************************************************************
#--Description--#:	Destroys entity
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Entity to destroy
#--Return--#: 		NA
************************************************************/
void Scene::DestroyEntity(std::shared_ptr<Entity> _Entity)
{
	if (_Entity)
	{
		if (_Entity.use_count() > 1)
		{
			std::cout << "Entity still has " << std::to_string(_Entity.use_count() - 1) << std::endl;
		}
		_Entity->OnDestroy();
	}
	for (auto it = Entities.begin(); it != Entities.end(); ++it)
	{
		if (*it == _Entity || *it == nullptr)
		{
			Entities.erase(it);
			//*it = nullptr;
			break;
		}
	}
	_Entity.reset();
}

/************************************************************
#--Description--#:	Adds UI element
#--Author--#: 		Alex Coultas
#--Parameters--#: 	UI Element to add
#--Return--#: 		NA
************************************************************/
void Scene::AddUIElement(std::shared_ptr<UIElement> Element)
{
	UIElements.push_back(Element);
}

/************************************************************
#--Description--#:	Adds UI Text element
#--Author--#: 		Alex Coultas
#--Parameters--#: 	UI Text Element to add
#--Return--#: 		NA
************************************************************/
void Scene::AddUITextElement(std::shared_ptr<UIText> Element)
{
	UIElements.push_back(Element);
}

/************************************************************
#--Description--#:	Adds UI Text element
#--Author--#: 		Alex Coultas
#--Parameters--#: 	UI Text Element paramters to add
#--Return--#: 		NA
************************************************************/
void Scene::AddUITextElement(glm::vec2 _Position, float _fRotation, glm::vec4 _Colour, std::string _sText, std::string font, int iPSize, Utils::EANCHOR _Anchor)
{
	std::shared_ptr<UIText> NewElement = std::make_shared<UIText>(_Position, _fRotation, _Colour, _sText, font, iPSize, _Anchor);
	UIElements.push_back(NewElement);
}

/************************************************************
#--Description--#:	Destroys UI Text element
#--Author--#: 		Alex Coultas
#--Parameters--#: 	UI Text Element paramters to destroy
#--Return--#: 		NA
************************************************************/
void Scene::DestroyUIElement(std::shared_ptr<UIElement> _Element)
{
	for (auto it = UIElements.begin(); it != UIElements.end(); ++it)
	{
		if (*it == _Element)
		{
			*it == nullptr;
			UIElements.erase(it);
			break;
		}
	}
	_Element = nullptr;
}

/************************************************************
#--Description--#: 	Updated every frame
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Scene::Update()
{
	if (Entities.size() != 0)
	{
		unsigned int iEndPos = Entities.size() - 1;
		for (unsigned int i = 0; i <= iEndPos; i++)
		{
			if (Entities[i])
				Entities[i]->Update();
			if (iEndPos >= Entities.size())
			{
				iEndPos = Entities.size() - 1;
				i--;
			}
			if (Entities[iEndPos] != Entities.back()) // if current last value is not equal to the back of the vector
			{
				iEndPos = Entities.size() - 1;
				//i--;
			}
		}
	}
	/*for (auto it : Entities)
	{
		if (it)
			it->Update();
	}*/
	if (UIElements.size() != 0)
	{
		unsigned int iEndPos = UIElements.size() - 1;
		for (unsigned int i = 0; i <= iEndPos; i++)
		{
			if (UIElements[i])
				UIElements[i]->Update();
			if (iEndPos >= UIElements.size())
			{
				iEndPos = UIElements.size() - 1;
				i--;
			}
			if (UIElements[iEndPos] != UIElements.back()) // if current last value is not equal to the back of the vector
			{
				iEndPos = UIElements.size() - 1;
				i--;
			}
		}
	}
	/*for (auto it : UIElements)
	{
		if (it) it->Update();
	}*/
	//UIButton::bButtonPressedThisFrame = false;
}

/************************************************************
#--Description--#: 	== operator overloading
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Comparing scene
#--Return--#: 		NA
************************************************************/
bool Scene::operator==(const Scene & rhs) const
{
	if (SceneName == rhs.SceneName) return true;
	return false;
}
