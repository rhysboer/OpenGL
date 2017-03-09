#include "Application.h"
#include "Time.h"

int main() {
	BaseApplication* app = new Application(1280, 720, "OpenGL");

	bool run = true;
	Time* time = Time::GetInstance();

	if(app->Startup() == true) {
		while(run == true) {
			// Delta Time
			time->Update(glfwGetTime());
			// Update Loop
			run = app->Update();
			// Draw Loop
			app->Draw();
		}

		app->Shutdown();
	}

	delete app;
	delete time;
	return 0;
}