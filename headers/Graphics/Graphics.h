#pragma once
#include "AdapterReader.h"

namespace graphics
{
	class Graphics
	{
	public:
		bool Initialize(HWND _hwnd, int _width, int _height);
		void RenderFrame();

	private:
		bool InitializeDirectX(HWND _hwnd, int _width, int _height);

		Microsoft::WRL::ComPtr<ID3D11Device> m_device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
	};
}