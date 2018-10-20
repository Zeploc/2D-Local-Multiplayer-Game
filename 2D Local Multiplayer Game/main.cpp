//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    main.cpp
// Description		:    main implementation of the program
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //
#include <iostream>
#include <time.h>
//#include <vld.h>

// OpenGL Library Includes //
#include <glew.h>
#include <freeglut.h>
#include <fmod.hpp>
#include <soil\SOIL.h>
#include <glm/common.hpp>
#include <glm/gtc\type_ptr.hpp>
#include <glm/gtc\type_ptr.hpp>
#include <glm/gtc\matrix_transform.hpp>

// Engine Includes //
#include "Engine\Input.h"
#include "Engine\Camera.h"
#include "Engine\Shader.h"
#include "Engine\ShaderLoader.h"
#include "Engine\Entity.h"
#include "Engine\UIText.h"
#include "Engine\Scene.h"
#include "Engine\SceneManager.h"
#include "Engine\SoundManager.h"
#include "Engine\Time.h"
#include "Engine/LogManager.h"

#include <Box2D.h>

// Local Includes //
#include "LevelManager.h"

// make sure the winsock lib is included...
#pragma comment(lib,"ws2_32.lib")

// Static Function Prototypes //

// Types //
using namespace std;

#define SI Input::GetInstance()
#define CAM Camera::GetInstance() 
#define SM SceneManager::GetInstance()

// Prototypes //
void renderScene(void);
void changeSize(int w, int h);
void Update();
void Init();
void OnExit();

bool bLoading = true;

float CurrentTimer = 0.0f;
float TickRate = 60.0f;
double dPrevTime = 0.0f;

/************************************************************
#--Description--#: 	The main function of the program
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Count of how many arguments and a dynamic array of each argument
#--Return--#: 		Return int
************************************************************/
int main(int argc, char **argv)
{
	srand(unsigned int(time(NULL)));
	// init GLUT and create Window
	CAM->Init(1280, 720, glm::vec3(0, 0, 10), glm::vec3(0, 0, -1), glm::vec3(0, 1.0f, 0.0f));
	CAM->SwitchProjection(Camera::ORTHAGRAPHIC);
	glutInit(&argc, argv);
	//glutInitWindowPosition(0, 0);
	glutInitWindowSize(CAM->SCR_WIDTH, CAM->SCR_HEIGHT);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Game Window");
	//glutFullScreen();

	// OpenGL init
	glewInit();		
	// Settings Initialised
	Init();					

	// register callbacks
	glutDisplayFunc(renderScene);

	// Set close function if window is closed
	glutCloseFunc(OnExit); 

	// here is the idle func registration
	glutIdleFunc(Update);

	// The input function registration
	SI->Init();

	// Window Resize Function
	glutReshapeFunc(changeSize);

	// Enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}

/************************************************************
#--Description--#: 	Renders the elements every frame
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (bLoading)
	{
		LogManager::GetInstance()->Render();
	}
	else
	{
		Camera::GetInstance()->Update();

		SM->RenderCurrentScene();
	}
	glutSwapBuffers();
}

/************************************************************
#--Description--#: 	Updated when the window changes size
#--Author--#: 		Alex Coultas
#--Parameters--#: 	The width and height of the window
#--Return--#: 		NA
************************************************************/
void changeSize(int w, int h)
{
	CAM->SCR_HEIGHT = h;
	CAM->SCR_WIDTH = w;
}

/************************************************************
#--Description--#: 	Update for every frame
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Update()
{
	if (bLoading)
	{
		SoundManager::GetInstance()->InitFMod();
		// Scene setup here
		LevelManager::GetInstance()->Init();
		bLoading = false;
	}
	else
	{

		double dCurrentTime = glutGet(GLUT_ELAPSED_TIME);
		double TimeDelta = (dCurrentTime - dPrevTime) / 1000;
		dPrevTime = glutGet(GLUT_ELAPSED_TIME);
		CurrentTimer += TimeDelta;
		if (CurrentTimer > 1.0f / TickRate)
		{
			SceneManager::GetInstance()->UpdateCurrentScene();
			Time::Update();
			SI->Update(); // HAS TO BE LAST TO HAVE FIRST PRESS AND RELEASE
			CurrentTimer = 0.0f;
		}

		//SceneManager::GetInstance()->UpdateCurrentScene();
		//Time::Update();
		//SI->Update(); // HAS TO BE LAST TO HAVE FIRST PRESS AND RELEASE
	}

	glutPostRedisplay();
}

/************************************************************
#--Description--#: 	Initialises the program
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Init()
{
	Shader::AddProgram("Resources/Shaders/TextureVertexShader.vs", "Resources/Shaders/TextureFragmentShader.fs", "BaseProgram");
	Shader::AddProgram("Resources/Shaders/LitVertexShader.vs", "Resources/Shaders/LitFragmentShader.fs", "LitTextureprogram");
	Shader::AddProgram("Resources/Shaders/Text.vs", "Resources/Shaders/Text.fs", "TextUIprogram");
	Shader::AddProgram("Resources/Shaders/UI.vs", "Resources/Shaders/UI.fs", "UIprogram");
	Shader::AddProgram("Resources/Shaders/CubeMapVertexShader.vs", "Resources/Shaders/CubeMapFragmentShader.fs", "CubeMapProgram");
	Shader::AddProgram("Resources/Shaders/ModelVertexShader.vs", "Resources/Shaders/ModelFragmentShader.fs", "ModelProgram");
	Shader::AddProgram("Resources/Shaders/ModelVertexShaderLit.vs", "Resources/Shaders/ModelFragmentShaderLit.fs", "ModelProgramLit");
	Shader::AddProgram("Resources/Shaders/ReflectionShader.vs", "Resources/Shaders/ReflectionShader.fs", "ReflectionProgram");
	Shader::AddProgram("Resources/Shaders/FogShader.vs", "Resources/Shaders/FogShader.fs", "FogProgram");
	Shader::AddProgram("Resources/Shaders/GeometryShader.vs", "Resources/Shaders/GeometryShader.fs", "GeometryShader", "Resources/Shaders/GeometryShader.gs");
	Shader::AddTessProgram("Resources/Shaders/Tessellation.vs", "Resources/Shaders/Tessellation.fs", "Resources/Shaders/TessControl.tc", "Resources/Shaders/TessEval.te", "TessProgram");
	Shader::AddProgram("Resources/Shaders/FrameBuffer.vs", "Resources/Shaders/FrameBuffer.fs", "FrameBuffer");

	glCullFace(GL_BACK); // Cull the Back faces
	glFrontFace(GL_CW); // Front face is Clockwise order
	glEnable(GL_CULL_FACE); // Turn on the back face culling

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glutSetCursor(GLUT_CURSOR_NONE);

	//glutSetCursor(GLUT_CURSOR_CROSSHAIR);

	glutIgnoreKeyRepeat(1);

	glClearColor(0.8f, 0.8f, 0.8f, 1.0); // clear grey
	LogManager::GetInstance()->Init();

	//// Define the gravity vector.
	//b2Vec2 gravity(0.0f, -10.0f);

	//// Construct a world object, which will hold and simulate the rigid bodies.
	//b2World world(gravity);

	//// Define the ground body.
	//b2BodyDef groundBodyDef;
	//groundBodyDef.position.Set(0.0f, -10.0f);

	//// Call the body factory which allocates memory for the ground body
	//// from a pool and creates the ground box shape (also from a pool).
	//// The body is also added to the world.
	//b2Body* groundBody = world.CreateBody(&groundBodyDef);

	//// Define the ground box shape.
	//b2PolygonShape groundBox;

	//// The extents are the half-widths of the box.
	//groundBox.SetAsBox(50.0f, 10.0f);

	//// Add the ground fixture to the ground body.
	//groundBody->CreateFixture(&groundBox, 0.0f);

	//// Define the dynamic body. We set its position and call the body factory.
	//b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(0.0f, 4.0f);
	//b2Body* body = world.CreateBody(&bodyDef);

	//// Define another box shape for our dynamic body.
	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(1.0f, 1.0f);

	//// Define the dynamic body fixture.
	//b2FixtureDef fixtureDef;
	//fixtureDef.shape = &dynamicBox;

	//// Set the box density to be non-zero, so it will be dynamic.
	//fixtureDef.density = 1.0f;

	//// Override the default friction.
	//fixtureDef.friction = 0.3f;

	//// Add the shape to the body.
	//body->CreateFixture(&fixtureDef);

	//// Prepare for simulation. Typically we use a time step of 1/60 of a
	//// second (60Hz) and 10 iterations. This provides a high quality simulation
	//// in most game scenarios.
	//float32 timeStep = 1.0f / 60.0f;
	//int32 velocityIterations = 6;
	//int32 positionIterations = 2;

	//// This is our little game loop.
	//for (int32 i = 0; i < 60; ++i)
	//{
	//	// Instruct the world to perform a single step of simulation.
	//	// It is generally best to keep the time step and iterations fixed.
	//	world.Step(timeStep, velocityIterations, positionIterations);

	//	// Now print the position and angle of the body.
	//	b2Vec2 position = body->GetPosition();
	//	float32 angle = body->GetAngle();

	//	printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	//}
}

/************************************************************
#--Description--#: 	Runs when the application closes
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void OnExit()
{
	Shader::CleanUp();
	SceneManager::DestoryInstance();
	Camera::DestoryInstance();
	Input::DestoryInstance();
	SoundManager::DestoryInstance();
	Text::Fonts.~vector();
}


