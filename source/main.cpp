#include "../headers/Engine.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	//HRESULT hr = E_INVALIDARG;
	//HRESULT hr = S_OK;
	//if (FAILED(hr)) { ErrorLogger::Log(E_INVALIDARG, "Test Message"); }
	//if (SUCCEEDED(hr)) { MessageBoxA(nullptr, "SUCCESS", "SUCCESS", NULL); }

	Engine engine;
	engine.Initialize(hInstance,"Test Window","MyWindowClass",800,600);

	while (engine.ProcessMessages()) { 
		engine.Update();
		engine.RenderFrame();
	}

	return 0;
}
