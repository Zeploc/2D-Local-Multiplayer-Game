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
	DestroyedEntities.push_back(_Entity);
	_Entity->SetActive(false);
	_Entity->OnDestroy();
	
	// Find entity in entities
	for (auto it = Entities.begin(); it != Entities.end(); ++it)
	{
		if (*it == _Entity || *it == nullptr)
		{
			// Remove from entities list
			Entities.erase(it);
			break;
		}
	}
	// Reset all but this option?
	//EntDetroy.reset();
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
	UIElementsToBeDestroyed.push_back(_Element);
	_Element->SetActive(false);		
}

/************************************************************
#--Description--#: 	Updated every frame
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Scene::Update()
{
	for (int i = 0; i < Entities.size(); i++)
	{
		if (Entities[i])
			Entities[i]->BaseUpdate();
	}
	/*for (auto& Ent : Entities)
	{
		if (Ent)
			Ent->BaseUpdate();
	}	*/
	//if (Entities.size() != 0)
	//{
	//	unsigned int iEndPos = Entities.size() - 1;
	//	for (unsigned int i = 0; i <= iEndPos; i++)
	//	{
	//		if (Entities[i])
	//			Entities[i]->Update();
	//		if (iEndPos >= Entities.size())
	//		{
	//			iEndPos = Entities.size() - 1;
	//			i--;
	//		}
	//		if (Entities[iEndPos] != Entities.back()) // if current last value is not equal to the back of the vector
	//		{
	//			iEndPos = Entities.size() - 1;
	//			//i--;
	//		}
	//	}
	//}
	/*for (auto it : Entities)
	{
		if (it)
			it->Update();
	}*/
	for (int i = 0; i < UIElements.size(); i++)
	{
		if (UIElements[i])
			UIElements[i]->BaseUpdate();
	}

	/*for (auto& UIElem : UIElements)
	{
		if (UIElem)
			UIElem->BaseUpdate();
	}*/
	//UIButton::bButtonPressedThisFrame = false;
	

	for (auto& UIDestroy : UIElementsToBeDestroyed)
	{
		for (auto it = UIElements.begin(); it != UIElements.end(); ++it)
		{
			if (*it == UIDestroy)
			{
				UIElements.erase(it);
				break;
			}
		}
		UIDestroy.reset();
	}
	if (!UIElementsToBeDestroyed.empty()) UIElementsToBeDestroyed.clear();
}

void Scene::OnLoadScene()
{
	if (!bIsPersistant)
	{
		for (auto& EntDestroy : DestroyedEntities)
		{
			Entities.push_back(EntDestroy);
		}
		DestroyedEntities.clear();
		for (auto& Ent : Entities)
		{
			Ent->Reset();
		}
	}
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
