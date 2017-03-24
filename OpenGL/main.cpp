#include "Application.h"
#include "Time.h"
#include "InputManager.h"

//Imgui
#include "imgui_impl_glfw_gl3.h"
#include "imgui.h"

void SetUpImgui(GLFWwindow* window);

int main() {
	BaseApplication* app = new Application(1280, 720, "OpenGL 3D Engine");

	// Setup GUI
	SetUpImgui(app->GetWindow());

	bool run = true;
	Time* time = Time::GetInstance();

	// Hide Console
	FreeConsole();

	if(app->Startup() == true) {
		// Setup input manager
		InputManager::Init(app->GetWindow());

		// Main Game Loop
		while(run == true) {
			ImGui_ImplGlfwGL3_NewFrame();

			// Update Delta Time
			time->Update((float)glfwGetTime());

			// Update Loop
			run = app->Update();
			// Draw Loop
			app->Draw();

			// GUI Draw
			ImGui::Render();

			// Update Inputs
			InputManager::PollEvents();

			glfwSwapBuffers(app->GetWindow());
		}
	}

	app->Shutdown();

	delete app;
	delete time;
	return 0;
}

void SetUpImgui(GLFWwindow* window) {
	ImGui_ImplGlfwGL3_Init(window, true);
}