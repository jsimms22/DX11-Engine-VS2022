#pragma once
#include "AdapterReader.h"
#include "Shaders.h"
#include <array>

namespace graphics
{
	class Graphics
	{
	public:
		bool Initialize(HWND _hwnd, int _width, int _height);
		void RenderFrame();

	private:
		bool InitializeDirectX(HWND _hwnd, int _width, int _height);
		bool InitializeShaders();

		Microsoft::WRL::ComPtr<ID3D11Device> m_device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;

		//Shader
		VertexShader m_vertexShader;
		//Microsoft::WRL::ComPtr<ID3D10Blob> m_vertex_shader_buffer;
	};
}