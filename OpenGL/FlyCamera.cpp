#include "FlyCamera.h"

FlyCamera::FlyCamera() {
}

FlyCamera::~FlyCamera() {
}

void FlyCamera::Update() {
	UpdateMousePosition();

	float speedModifier = 1;

	if(InputManager::IsKeyDown(GLFW_KEY_LEFT_SHIFT)) {
		speedModifier = 5;
	}


	// FORWARD
	if(InputManager::IsKeyDown(GLFW_KEY_W)) {
		Move(vec3(0, 0, -3) * speedModifier * Time::DeltaTime());
	}

	// BACKWARDS
	if(InputManager::IsKeyDown(GLFW_KEY_S)) {
		Move(vec3(0, 0, 3) * speedModifier * Time::DeltaTime());
	}

	// LEFT
	if(InputManager::IsKeyDown(GLFW_KEY_A)) {
		Move(vec3(-3, 0, 0) * speedModifier * Time::DeltaTime());
	}

	// RIGHT
	if(InputManager::IsKeyDown(GLFW_KEY_D)) {
		Move(vec3(3, 0, 0) * speedModifier * Time::DeltaTime());
	}

	// UP
	if(InputManager::IsKeyDown(GLFW_KEY_E)) {
		Move(vec3(0, 3, 0) * speedModifier * Time::DeltaTime());
	}

	// DOWN
	if(InputManager::IsKeyDown(GLFW_KEY_Q)) {
		Move(vec3(0, -3, 0) * speedModifier * Time::DeltaTime());
	}

	if(InputManager::IsMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {
		vec3 mousePosition = GetMouseCameraMovement();
		if(mousePosition != vec3(0)) {
			Rotate(3.0f * Time::DeltaTime(), mousePosition);
		}
	}
}

void FlyCamera::UpdateMousePosition() {
	double mouseX, mouseY;
	InputManager::MousePosition(mouseX, mouseY);

	oldPos = currPos;
	currPos = vec3((float)mouseX, (float)mouseY, 0);
}

vec3 FlyCamera::GetMouseCameraMovement() {
	vec3 pos = currPos - oldPos;

	if(pos == vec3(0)) {
		return vec3(0);
	}

	vec3 temp = pos;
	pos.y = temp.x;
	pos.x = temp.y;

	return pos;
}
