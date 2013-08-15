//*************************************************************************************************
// Title: SumRenderManager.h
// Author: Gael Huber
// Description: Render manager. Keeps track of various effects, renderable objects, and scene
//	graphs.
//*************************************************************************************************
#include "SumRenderManager.h"

//*************************************************************************************************
// Initialize the singleton instance of this class to 0
//*************************************************************************************************
template <> RenderManager* Singleton<RenderManager>::singleton = 0;

//*************************************************************************************************
// Constructor
//*************************************************************************************************
RenderManager::RenderManager()
	:	_renderContext(0),
		_renderWindow(0),
		_renderViewport(0),
		_effectsManager(0)
{

}

//*************************************************************************************************
// Destructor
//*************************************************************************************************
RenderManager::~RenderManager()
{ }

//*************************************************************************************************
// Initialize render manager
//*************************************************************************************************
void RenderManager::startUp()
{
	// Get width and height
	Configuration* config = ConfigurationManager::getSingletonPtr()->getConfiguration("Engine");
	SUINT width = config->retrieveValue("width").toUInt();
	SUINT height = config->retrieveValue("height").toUInt();

	// Initialize the three primary components
	_renderWindow = new RenderWindow(width, height);
	_renderContext = new RenderContext(_renderWindow->clientHandle(), _renderWindow->clientWidth(), _renderWindow->clientHeight());
	_renderViewport = new RenderViewport();
	_renderViewport->configure(_renderContext, _renderWindow);

	// Initialize the effects manager
	_effectsManager = new EffectsManager();
	_effectsManager->startUp(_renderContext->d3dDevice());
	InputLayouts::InitAll(_renderContext->d3dDevice());

	// TEMP
	//_renderable = new Renderable("box", "box");
	_camera = 0;

	// Calculate light direction
	_dirLight.ambient = Float4(0.2f, 0.2f, 0.2f, 1.0f);
	_dirLight.diffuse = Float4(0.5f, 0.5f, 0.5f, 1.0f);
	_dirLight.specular = Float4(0.5f, 0.5f, 0.5f, 1.0f);
	_dirLight.direction = Float3(0.57735f, 0.57735f, 0.57735f);

	_pointLight.ambient = Float4(0.3f, 0.3f, 0.3f, 1.0f);
	_pointLight.diffuse = Float4(0.7f, 0.7f, 0.7f, 1.0f);
	_pointLight.specular = Float4(0.7f, 0.7f, 0.7f, 1.0f);
	_pointLight.att = Float3(0.0f, 0.1f, 0.0f);
	_pointLight.range = 25.0f;
	_pointLight.position = Float3(0.0f, 5.0f, 0.0f);

	_material.ambient = Float4(0.48f, 0.77f, 0.46f, 1.0f);
	_material.diffuse = Float4(0.48f, 0.77f, 0.46f, 1.0f);
	_material.specular = Float4(0.2f, 0.2f, 0.2f, 16.0f);
}

//*************************************************************************************************
// Shut down the render manager
//*************************************************************************************************
void RenderManager::shutDown()
{
	SafeDelete(_effectsManager);

	SafeDelete(_renderContext);
	SafeDelete(_renderWindow);
	SafeDelete(_renderViewport);
}

//*************************************************************************************************
// Update the manager
//*************************************************************************************************
void RenderManager::update()
{
	// TODO: Prune the scene and update draw list

	// TODO: Update any effects

	// Render the scene
	renderScene();
}

//*************************************************************************************************
// Render the current scene
//*************************************************************************************************
void RenderManager::renderScene()
{
	// Clear the viewports
	_renderViewport->clearViewport(_renderContext);

	// Draw the scene

	// Set draw contexts
	ID3D11DeviceContext* context = _renderContext->d3dImmediateContext();
	context->IASetInputLayout(InputLayouts::PosNormal);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Only bother drawing the world if we have an attached camera
	if(_camera)
	{
		// Prep matrix variables for effect
		Matrix viewProj = _camera->viewProj();
		
		BasicEffect* effect = static_cast<BasicEffect*>(_effectsManager->getEffectByName("basic"));
		effect->setViewProj(viewProj);
		effect->setDirLight(&_dirLight);
		effect->setPointLight(&_pointLight);
		effect->setEyePosW(_camera->position());
			
		// Get the active technique
		ID3DX11EffectTechnique* activeTech = effect->light1Tech();

		// Set vertex buffers
		SUINT stride = sizeof(Vertex);
		SUINT offset = 0;

		// Iterate through the current list of renderables
		List<Renderable*>::Iterator endItr = _renderList.end();
		for(List<Renderable*>::Iterator itr = _renderList.begin(); itr != endItr; ++itr)
		{
			Renderable* renderable = *itr;
			Matrix world = renderable->world();
			Matrix worldInvTranspose = MatrixInverseTranspose(world);
			effect->setWorld(renderable->world());
			effect->setWorldInvTranspose(worldInvTranspose);
		
			Mesh* currMesh = renderable->mesh();
			context->IASetVertexBuffers(0, 1, currMesh->vertexBufferPtr(), &stride, &offset);
			context->IASetIndexBuffer(currMesh->indexBuffer(), DXGI_FORMAT_R32_UINT, 0);
			
			effect->setMaterial(_material);

			// Technique description
			D3DX11_TECHNIQUE_DESC techDesc;
			activeTech->GetDesc(&techDesc);
			for(SUINT p = 0; p < techDesc.Passes; ++p)
			{
				activeTech->GetPassByIndex(p)->Apply(0, context);

				// Draw indices
				context->DrawIndexed(currMesh->indexCount(), 0, 0);
			}
		}
	}

	// Present the swap chain
	HR(_renderContext->swapChain()->Present(0, 0));
}

//*************************************************************************************************
// Register a camera with the rendering system
//*************************************************************************************************
void RenderManager::registerCamera(Camera* camera)
{
	// Set this camera to be the default camera
	_camera = camera;
}

//***
// Register a renderable with the render list
//**************
void RenderManager::registerRenderable(Renderable* renderable)
{
	_renderList.push_back(renderable);
}

