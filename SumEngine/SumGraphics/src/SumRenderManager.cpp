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
	_mesh = ResourceManager::getSingletonPtr()->getResourceById<Mesh>("box", "mesh");
	Matrix p = MatrixPerspectiveFovLH(0.25f * S_PI, _renderWindow->aspectRatio(), 1.0f, 1000.0f);
	StoreFloat4x4(&_proj, p);
	Matrix i = MatrixIdentity();
	StoreFloat4x4(&_view, i);
	StoreFloat4x4(&_world, i);
	
	_eyePosW = Float3(0.0f, 0.0f, 0.0f);
	_theta = 1.5f * S_PI;
	_phi = 0.25f * S_PI;
	_radius = 5.0f;
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
	// Update the camera
	SFLOAT x = _radius * sinf(_phi) * cosf(_theta);
	SFLOAT z = _radius * sinf(_phi) * sinf(_theta);
	SFLOAT y = _radius * cosf(_phi);
	_eyePosW = Float3(x, y, z);
	
	Vector pos = VectorSet(x, y, z, 1.0f);
	Vector target = VectorZero();
	Vector up = VectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	Matrix v = MatrixLookAtLH(pos, target, up);
 	StoreFloat4x4(&_view, v);

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
	context->IASetInputLayout(InputLayouts::Pos);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Camera
	Matrix world = LoadFloat4x4(&_world);
	Matrix view = LoadFloat4x4(&_view);
	Matrix proj = LoadFloat4x4(&_proj);
	Matrix worldViewProj = MatrixMultiply(view, proj);
	//worldViewProj = MatrixMultiply(world, worldViewProj);
	PrimitiveEffect* effect = static_cast<PrimitiveEffect*>(_effectsManager->getEffectByName("primitive"));
	effect->viewProj()->SetMatrix(reinterpret_cast<float*>(&worldViewProj));
	effect->world()->SetMatrix(reinterpret_cast<float*>(&world));

	// Set vertex buffers
	SUINT stride = sizeof(Vertex);
	SUINT offset = 0;
	context->IASetVertexBuffers(0, 1, _mesh->vertexBufferPtr(), &stride, &offset);
	context->IASetIndexBuffer(_mesh->indexBuffer(), DXGI_FORMAT_R32_UINT, 0);

	// Technique description
	D3DX11_TECHNIQUE_DESC techDesc;
	effect->technique()->GetDesc(&techDesc);
	for(SUINT p = 0; p < techDesc.Passes; ++p)
	{
		effect->technique()->GetPassByIndex(p)->Apply(0, context);

		// Draw indices
		context->DrawIndexed(_mesh->indexCount(), 0, 0);
	}

	// Present the swap chain
	HR(_renderContext->swapChain()->Present(0, 0));
}

