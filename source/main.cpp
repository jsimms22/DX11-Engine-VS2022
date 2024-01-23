#include "../headers/ErrorLogger.h"
#include "../headers/main.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	//HRESULT hr = E_INVALIDARG;
	HRESULT hr = S_OK;
	if (FAILED(hr)) { ErrorLogger::Log(E_INVALIDARG, "Test Message"); }
	if (SUCCEEDED(hr)) { MessageBoxA(nullptr, "SUCCESS", "SUCCESS", NULL); }



	return 0;
}
