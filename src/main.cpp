#include "main.hpp"

using namespace std;

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	unique_ptr<Application> app(new Application());
	app->init();
	app->loop();
	app->detroy();
}
