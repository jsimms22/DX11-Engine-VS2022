#include "../../headers/Graphics/Shaders.h"

namespace graphics
{
	bool VertexShader::Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& _device, std::wstring _shaderPath, D3D11_INPUT_ELEMENT_DESC* _layoutDesc, UINT _numElements)
	{
		
		HRESULT hr = D3DReadFileToBlob(_shaderPath.c_str(), this->m_shaderBuffer.GetAddressOf());
		if (FAILED(hr)) {
			std::wstring errorMsg = L"Failed to load shader: ";
			errorMsg += _shaderPath;
			ErrorLogger::Log(hr, errorMsg);
			return false;
		}

		hr = _device->CreateVertexShader(this->m_shaderBuffer.Get()->GetBufferPointer(), this->m_shaderBuffer->GetBufferSize(), NULL, m_shader.GetAddressOf());
		if (FAILED(hr)) {
			std::wstring errorMsg = L"Failed to create vertex shader: ";
			errorMsg += _shaderPath;
			ErrorLogger::Log(hr, errorMsg);
			return false;
		}

		hr = _device->CreateInputLayout(_layoutDesc, _numElements, this->m_shaderBuffer->GetBufferPointer(),
			m_shaderBuffer->GetBufferSize(), this->m_inputLayout.GetAddressOf());
		if (FAILED(hr)) {
			ErrorLogger::Log(hr, "Failed to create input layout.");
			return false;
		}


		return true;
	}

	ID3D11VertexShader* VertexShader::GetShader() 
	{
		return this->m_shader.Get();
	}

	ID3D10Blob* VertexShader::GetBuffer()
	{
		return this->m_shaderBuffer.Get();
	}

	ID3D11InputLayout* VertexShader::GetInputLayout()
	{
		return this->m_inputLayout.Get();
	}
}

