//*************************************************************************************************
// Title: SumRenderWindow.cpp
// Author: Gael Huber
// Description: Maintains a physical window for the client to attach the render context.
//*************************************************************************************************
#include "SumD3D11RenderWindow.h"

namespace SumEngine
{
	//*************************************************************************************************
	// Default constructor
	//*************************************************************************************************
	D3D11RenderWindow::D3D11RenderWindow()
		:	_swapChain(0),
			_dxgiFactory(0)
	{ }

	//*************************************************************************************************
	// Constructor
	// @param
	//	hInstance The application instance
	// @param
	//	device The D3D11 Device used to create this window and the swap chain of the render target
	// @param
	//	dxgiFactory Used to create the swap chain for this window
	//*************************************************************************************************
	D3D11RenderWindow::D3D11RenderWindow(HINSTANCE hInstance, D3D11Device& device, IDXGIFactory1* dxgiFactory)
		:	_swapChain(0),
			_dxgiFactory(dxgiFactory),
			_hInstance(hInstance),
			_device(device)

	{ }

	//*************************************************************************************************
	// Destructor 
	//*************************************************************************************************
	D3D11RenderWindow::~D3D11RenderWindow()
	{
		// Destroy the swapchain
		ReleaseCOM(_swapChain);
	}

	//*************************************************************************************************
	// Initializes the window
	// @param
	//	name The name of the window
	// @param
	//	width The width of the window resolution
	// @param
	//	height The window height
	// @param
	//	fullscreen The window will be created in fullscreen if true
	//*************************************************************************************************
	void D3D11RenderWindow::create(const String& name, SUINT width, SUINT height, SBOOL fullscreen)
	{
		// Create the window class
		WNDCLASS wc;
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WindowEventHandler::WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = _hInstance;
		wc.hIcon = LoadIcon(0, IDI_APPLICATION);
		wc.hCursor = LoadCursor(0, IDC_ARROW);
		wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
		wc.lpszMenuName = 0;
		wc.lpszClassName = name;

		RegisterClass(&wc);

		// Compute inner window size
		RECT r = {0, 0, width, height};
		AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, false);
		SLONG iWidth = r.right - r.left;
		SLONG iHeight = r.bottom - r.top;
		
		// Create the window
		_handle = CreateWindow(
			wc.lpszClassName,
			name,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			iWidth,
			iHeight,
			0,
			0,
			_hInstance,
			0
			);
		if(!_handle)
		{
			MessageBox(0, "CreateWindow failed.", 0, 0);
		}

		// Save variables
		_name = name;
		_width = width;
		_height = height;
		_isFullscreen = fullscreen;

		// Display the window
		ShowWindow(_handle, SW_SHOW);
		UpdateWindow(_handle);

		// Create the swap chain
		_createSwapChain();
	}

	//*************************************************************************************************
	// Destroy the window
	//*************************************************************************************************
	void D3D11RenderWindow::destroy()
	{
		// TODO
	}

	//*************************************************************************************************
	// Change the window position
	// @param
	//	x The x position of the window's top-left corner
	// @param
	//	y The y position of the window's top-left corner
	//*************************************************************************************************
	void D3D11RenderWindow::setPosition(SUINT x, SUINT y)
	{
		// TODO
	}

	//*************************************************************************************************
	// Change the window's fullscreen parameter and adjust as necessary
	// @param
	//	fullscreen Set the window to fullscreen if true, windowed if false
	//*************************************************************************************************
	void D3D11RenderWindow::setFullscreen(SBOOL fullscreen)
	{
		// TODO
	}

	//*************************************************************************************************
	// Swap the buffers for the window
	//*************************************************************************************************
	void D3D11RenderWindow::swapBuffers()
	{
		// If the device exists
		if(_device.isNull() == false)
		{
			_swapChain->Present(0, 0);
		}
	}

	//*************************************************************************************************
	// Create the device swap chain
	//*************************************************************************************************
	void D3D11RenderWindow::_createSwapChain()
	{
		// Populate the swap chain description
		_swapChainDescription.BufferDesc.Width = _width;
		_swapChainDescription.BufferDesc.Height = _height;
		_swapChainDescription.BufferDesc.RefreshRate.Numerator = 60;
		_swapChainDescription.BufferDesc.RefreshRate.Denominator = 1;
		_swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		_swapChainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		_swapChainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		// TODO: Add support for MSAA
		_swapChainDescription.SampleDesc.Count = 1;
		_swapChainDescription.SampleDesc.Quality = 0;

		_swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		_swapChainDescription.BufferCount = 1;
		_swapChainDescription.OutputWindow = _handle;
		_swapChainDescription.Windowed = !_isFullscreen;
		_swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		_swapChainDescription.Flags = 0;

		// Get the DXGI device
		IDXGIDevice1* dxgiDevice = 0;
		_device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&dxgiDevice);

		// Create the swap chain
		_dxgiFactory->CreateSwapChain(dxgiDevice, &_swapChainDescription, &_swapChain);
		ReleaseCOM(dxgiDevice);

		// Get the back buffer of the swap chain
		_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&_backBuffer);
		D3D11_TEXTURE2D_DESC backBufferDesc;
		_backBuffer->GetDesc(&backBufferDesc);

		// Create the render target view
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
		ZeroMemory(&renderTargetViewDesc, sizeof(renderTargetViewDesc));
		renderTargetViewDesc.Format = backBufferDesc.Format;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;
		_device->CreateRenderTargetView(_backBuffer, &renderTargetViewDesc, &_renderTargetView);

		// Create depth stencil texture
		D3D11_TEXTURE2D_DESC depthStencilDesc;
		depthStencilDesc.Width = _width;
		depthStencilDesc.Height = _height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		
		// TODO: Add MSAA support
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;

		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;

		// Create the depth stencil view
		ID3D11Texture2D* depthStencil = 0;
		_device->CreateTexture2D(&depthStencilDesc, 0, &depthStencil);

		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		ZeroMemory(&depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;
		_device->CreateDepthStencilView(depthStencil, &depthStencilViewDesc, &_depthStencilView);
	}

	//*************************************************************************************************
	// Get an attribute of the render window
	// @param
	//	attribute A pointer to the desired class type
	// @param 
	//	data Pointer to the data being retrieved
	//*************************************************************************************************
	void D3D11RenderWindow::getAttribute(SUINT attribute, void* data)
	{
		if(attribute == D3D11_RENDER_TARGET_VIEW)
		{
			*static_cast<ID3D11RenderTargetView**>(data) = _renderTargetView;
		}
		else if(attribute == D3D11_DEPTH_STENCIL_VIEW)
		{
			*static_cast<ID3D11DepthStencilView**>(data) = _depthStencilView;
		}
	}

	//*************************************************************************************************
	// Get the render target view
	// @return
	//	ID3D11RenderTargetView* The render target view associated with this window
	//*************************************************************************************************
	ID3D11RenderTargetView* D3D11RenderWindow::getRenderTargetView()
	{
		return _renderTargetView;
	}

	//*************************************************************************************************
	// Get the depth stencil view
	// @return
	//	ID3D11DepthStencilView* The depth stencil view associated with this window
	//*************************************************************************************************
	ID3D11DepthStencilView* D3D11RenderWindow::getDepthStencilView()
	{
		return _depthStencilView;
	}

}	// Namespace