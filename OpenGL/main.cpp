#include "Application.h"

int main() {
	BaseApplication* app = new Application(1280, 720, "OpenGL");

	if(app->Startup() == true) {
		while(app->Update() == true) {
			app->Draw();
		}

		app->Shutdown();
	}

	delete app;
	return 0;
}