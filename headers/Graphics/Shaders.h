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
		bool Initialize(Microsoft::WRL::ComPtr<ID3D11Device> &_device, std::wstring _shaderPath, D3D11_INPUT_ELEMENT_DESC* _desc, UINT _numElements);
		ID3D11VertexShader* GetShader();
		ID3D10Blob* GetBuffer();
		ID3D11InputLayout* GetInputLayout();

	private:
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_shader = nullptr;
		Microsoft::WRL::ComPtr<ID3D10Blob> m_shaderBuffer = nullptr;
		//Input Assembler
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	};

}