#include "../../headers/Graphics/AdapterReader.h"

namespace adapter
{
	// Since m_adapters is static inside a class, we have to define them before using the static member
	std::vector<AdapterData> AdapterReader::m_adapters;

	std::vector<AdapterData> AdapterReader::GetAdapters()
	{
		if (m_adapters.size() > 0) { return m_adapters; }

		Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;

		// Create a DXGIFactory object
		HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));
		if (FAILED(hr)) { 
			ErrorLogger::Log(hr, "Failed to create DXGIFactory for enumerating adapters.");
			exit(-1);
		}

		IDXGIAdapter* pAdapter;
		UINT index = 0;
		while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter))) {
			m_adapters.push_back(AdapterData(pAdapter));
			index += 1;
		}
		return m_adapters;
	}

	AdapterData::AdapterData(IDXGIAdapter* _ptrAdapter)
	{
		this->m_ptrAdapter = _ptrAdapter;
		HRESULT hr = _ptrAdapter->GetDesc(&this->m_description);
		if (FAILED(hr)) {
			ErrorLogger::Log(hr, "Failed to get description for IXDIAdapter.");
		}
	}
}