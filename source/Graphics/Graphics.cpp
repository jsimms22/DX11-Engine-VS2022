#include "../../headers/Graphics/Graphics.h"

namespace graphics
{
	std::wstring FindShaderFolderMacro() {
		std::wstring shaderFolder = L"";
#pragma region DetermineShaderPath
		if (IsDebuggerPresent() == TRUE) {
	#ifdef _DEBUG
		#ifdef _WIN64 
			shaderFolder = L"bin\\x64\\Debug\\";
		#else 
			shaderFolder = L"bin\\Win32\\Debug\\";
		#endif
	#else 
		#ifdef _WIN64
			shaderFolder = L"bin\\x64\\Release\\";
		#else
			shaderFolder = L"bin\\Win32\\Release\\";
		#endif
	#endif
		}

		return shaderFolder;
	}

	bool Graphics::Initialize(HWND _hwnd, int _width, int _height) 
	{
		if (!(InitializeDirectX(_hwnd, _width, _height))) { return false; }

		if (!InitializeShaders()) { return false; }
		// Here we can initialize shaders, scenes, etc

		return true;
	}

	void Graphics::RenderFrame()
	{
		float bgcolor[] = { 0.0f, 0.0f, 1.0f, 1.0f }; // { red, green, blue, alpha }
		this->m_deviceContext->ClearRenderTargetView(this->m_renderTargetView.Get(), bgcolor);
		this->m_swapChain->Present(1, NULL);
	}

	bool Graphics::InitializeDirectX(HWND _hwnd, int _width, int _height)
	{
		std::vector<adapter::AdapterData> adapters = adapter::AdapterReader::AdapterReader().GetAdapters();

		if (adapters.size() < 1) {
			ErrorLogger::Log("No IDXGI Adapters found.");
			return false;
		}

		DXGI_SWAP_CHAIN_DESC scd;
		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

		scd.BufferDesc.Width = _width;
		scd.BufferDesc.Height = _height;
		scd.BufferDesc.RefreshRate.Numerator = 60;
		scd.BufferDesc.RefreshRate.Denominator = 1;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		scd.SampleDesc.Count = 1;
		scd.SampleDesc.Quality = 0;

		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.BufferCount = 1;
		scd.OutputWindow = _hwnd;
		scd.Windowed = true;

		scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		HRESULT hr = D3D11CreateDeviceAndSwapChain(
			adapters[0].m_ptrAdapter,			//IDXG Adapter
			D3D_DRIVER_TYPE_UNKNOWN,			// Unspecified Hardware Driver Type
			NULL,								// For Softwate Drive Type
			NULL,								// Flags for runtime layers
			NULL,								// Feature levels array
			0,									// Number of indices for the feature levels array
			D3D11_SDK_VERSION,					// Our SDK version
			&scd,								// Pointer to our swapchain description
			this->m_swapChain.GetAddressOf(),	// pointer to our swapchain
			this->m_device.GetAddressOf(),		// Pointer to our device
			NULL,								// Supported feature level of the device
			this->m_deviceContext.GetAddressOf());// Device context

		if (FAILED(hr)) {
			ErrorLogger::Log(hr, "Failed to create device and swapchain.");
			return false;
		}

		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
		hr = this->m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
		if (FAILED(hr)) {
			ErrorLogger::Log(hr, "GetBuffer failed.");
			return false;
		}

		hr = this->m_device->CreateRenderTargetView(backBuffer.Get(), NULL, this->m_renderTargetView.GetAddressOf());
		if (FAILED(hr)) {
			ErrorLogger::Log(hr, "Failed to create render target view.");
			return false;
		}

		this->m_deviceContext->OMSetRenderTargets(1, this->m_renderTargetView.GetAddressOf(), nullptr);

		return true;
	}

	bool Graphics::InitializeShaders()
	{
		//char shaderFolder[MAX_PATH];
		//std::wstring shaderFolder;
		//wchar_t shaderFolder[MAX_PATH];
		if (!m_vertexShader.Initialize(this->m_device,
			FindShaderFolderMacro() +
			//GetModuleFileNameA(NULL, shaderFolder, MAX_PATH) + 
			L"vertexshader.cso")) {
			return false;
		}
		
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0}
			// useful MACRO D3C11_APPEND_ALIGNED_ELEMENT for data offset
		};

		UINT layoutSize = ARRAYSIZE(layout);

		HRESULT hr = this->m_device->CreateInputLayout(layout, layoutSize, m_vertexShader.GetBuffer()->GetBufferPointer(),
			m_vertexShader.GetBuffer()->GetBufferSize(), this->m_inputLayout.GetAddressOf());
		if (FAILED(hr)) {
			ErrorLogger::Log(hr, "Failed to create input layout.");
			return false;
		}
		return false;
	}
}