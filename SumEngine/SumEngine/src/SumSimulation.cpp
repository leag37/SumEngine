//*************************************************************************************************
// Title: SumSimulation.cpp
// Author: Gael Huber
// Description: Simulation controller for system.
//*************************************************************************************************
#include "SumSimulation.h"

//*************************************************************************************************
// Constructor
//*************************************************************************************************
Simulation::Simulation()
	: _camera(0)
{ }

//*************************************************************************************************
// Destructor
//*************************************************************************************************
Simulation::~Simulation()
{
	SafeDelete(_camera);
}

//*************************************************************************************************
// Start up the simulation
//*************************************************************************************************
void Simulation::startUp()
{
	// Cache the render manager
	RenderManager* renderManager = RenderManager::getSingletonPtr();

	// Create the camera
	_camera = new Camera();
	_camera->setLens(0.25f * S_PI, renderManager->aspectRatio(), 1.0f, 1000.0f);

	//Vector cPos = VectorSet(0.0f, 0.0f, 5.0f, 1.0f);
	//Vector cTarget = VectorZero();
	//Vector cUp = gVIdentityR1;

	SFLOAT _theta = 1.5f * S_PI;
	SFLOAT _phi = 0.25f * S_PI;
	SFLOAT _radius = 5.0f;
	SFLOAT x = _radius * sinf(_phi) * cosf(_theta);
	SFLOAT z = _radius * sinf(_phi) * sinf(_theta);
	SFLOAT y = _radius * cosf(_phi);
	
	Vector cPos = VectorSet(0.0f, 0.0f, -10.0f, 1.0f);
	Vector cTarget = VectorZero();
	Vector cUp = VectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	_camera->lookAt(cPos, cTarget, cUp);

	renderManager->registerCamera(_camera);
}

//*************************************************************************************************
// Shut down the simulation
//*************************************************************************************************
void Simulation::shutDown()
{

}

//*************************************************************************************************
// Update the simulation
//*************************************************************************************************
void Simulation::update(SFLOAT dTime)
{
	// Get the mouse
	const InputDeviceMouse* mouse = InputManager::getSingletonPtr()->mouse();
	const InputDeviceKeyboard* keyboard = InputManager::getSingletonPtr()->keyboard();

	// Rotate camera based on mouse movement
	_camera->rotateY(Math::ToRadian(mouse->relXf() * -0.25f));
	_camera->pitch(Math::ToRadian(mouse->relYf() * 0.25f));

	// Move the camera based on keyboard
	SFLOAT transX = 0.0f;
	SFLOAT transZ = 0.0f;
	SFLOAT moveBy = 0.10f;
	
	if(keyboard->getKey(DIK_LEFT))
	{
		transX -= moveBy;
	}
	if(keyboard->getKey(DIK_RIGHT))
	{
		transX += moveBy;
	}
	if(keyboard->getKey(DIK_UP))
	{
		transZ += moveBy;
	}
	if(keyboard->getKey(DIK_DOWN))
	{
		transZ -= moveBy;
	}

	_camera->translateX(transX);
	_camera->translateZ(transZ);
}