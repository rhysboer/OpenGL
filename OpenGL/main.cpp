#include "Application.h"
#include "Time.h"
#include "InputManager.h"

int main() {
	BaseApplication* app = new Application(1280, 720, "OpenGL");

	bool run = true;
	Time* time = Time::GetInstance();

	if(app->Startup() == true) {

		InputManager::Init(app->GetWindow());

		while(run == true) {
			// Delta Time
			time->Update(glfwGetTime());
			// Update Loop
			run = app->Update();
			// Draw Loop
			app->Draw();

			// Update Inputs
			InputManager::PollEvents();

			glfwSwapBuffers(app->GetWindow());
		}
		app->Shutdown();
	}

	delete app;
	delete time;
	return 0;
}