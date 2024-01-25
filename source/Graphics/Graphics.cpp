#include "../../headers/Graphics/Graphics.h"

namespace graphics
{
	bool Graphics::Initialize(HWND _hwnd, int _width, int _height) 
	{
		if (!(InitializeDirectX(_hwnd, _width, _height))) { return false; }
		// Here we can initialize shaders, scenes, etc
		return true;
	}

	bool Graphics::InitializeDirectX(HWND _hwnd, int _width, int _height)
	{
		std::vector<adapter::AdapterData> adapters = adapter::AdapterReader().GetAdapters();

		//HRESULT hr = D3D11CreateDeviceAndSwapChain()
		return true;
	}
}