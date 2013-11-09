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
	: _camera(0), _box(0)
{ }

//*************************************************************************************************
// Destructor
//*************************************************************************************************
Simulation::~Simulation()
{
	SafeDelete(_camera);
	SafeDelete(_box);
}

//*************************************************************************************************
// Start up the simulation
//*************************************************************************************************
void Simulation::startUp()
{
	// Cache the render manager
	SumEngine::RenderManager* renderManager = SumEngine::RenderManager::getSingletonPtr();
	PhysicsManager* physicsManager = PhysicsManager::getSingletonPtr();

	// Create the camera
	_camera = new Camera();
	_camera->setLens(0.25f * S_PI, 0.0f, 1.0f, 1000.0f);//renderManager->aspectRatio(), 1.0f, 1000.0f);

	//Vector cPos = VectorSet(0.0f, 0.0f, 5.0f, 1.0f);
	//Vector cTarget = VectorZero();
	//Vector cUp = gVIdentityR1;

	SFLOAT _theta = 1.5f * S_PI;
	SFLOAT _phi = 0.25f * S_PI;
	SFLOAT _radius = 5.0f;
	SFLOAT x = _radius * sinf(_phi) * cosf(_theta);
	SFLOAT z = _radius * sinf(_phi) * sinf(_theta);
	SFLOAT y = _radius * cosf(_phi);
	
	Vector cPos = VectorSet(0.0f, 5.0f, -10.0f, 0.0f);
	Vector cTarget = VectorZero();
	Vector cUp = gVIdentityR1;
	_camera->lookAt(cPos, cTarget, cUp);
	_camera->mapKey(DIK_W, Camera::FORWARD);
	_camera->mapKey(DIK_S, Camera::BACKWARD);
	_camera->mapKey(DIK_A, Camera::LEFT);
	_camera->mapKey(DIK_D, Camera::RIGHT);

	renderManager->registerCamera(_camera);

	// Create entities
	_box = new MovableEntity("box", "box");
	renderManager->registerRenderable(_box->renderable());
	physicsManager->registerPhysicsObject(_box->getPhysicsBody());

	_plane = new MovableEntity("plane", "plane");
	_plane->setPosition(0.0f, -5.0f, 0.0f);
	renderManager->registerRenderable(_plane->renderable());
	physicsManager->registerPhysicsObject(_plane->getPhysicsBody());
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
	_camera->updateInput(dTime);
}