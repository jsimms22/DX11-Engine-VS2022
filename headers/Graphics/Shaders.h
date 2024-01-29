#pragma once
#include "../ErrorLogger.h"
#include <d3d11.h>
#include <wrl/client.h>
#include <d3dcompiler.h>

namespace graphics
{
	class VertexShader
	{
	public:
		bool Initialize(Microsoft::WRL::ComPtr<ID3D11Device> &_device, std::wstring _shaderPath);
		ID3D11VertexShader* GetShader();
		ID3D10Blob* GetBuffer();
	private:
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_shader = nullptr;
		Microsoft::WRL::ComPtr<ID3D10Blob> m_shaderBuffer = nullptr;
	};

}