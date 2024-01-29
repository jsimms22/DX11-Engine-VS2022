#include "../../headers/Graphics/Shaders.h"

namespace graphics
{
	bool VertexShader::Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& _device, std::wstring _shaderPath)
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
}

