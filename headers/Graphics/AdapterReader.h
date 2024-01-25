#pragma once
#include "../ErrorLogger.h"
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>

namespace adapter
{
	class AdapterData
	{
	public:
		AdapterData(IDXGIAdapter* _ptrAdapter);
		IDXGIAdapter* m_ptrAdapter = nullptr;
		DXGI_ADAPTER_DESC m_description;
	};

	class AdapterReader
	{
	public:
		static std::vector<AdapterData> GetAdapters();
	private:
		static std::vector<AdapterData> m_adapters;
	};
}