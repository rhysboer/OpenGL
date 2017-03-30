#pragma once
#include "Camera.h"
#include "InputManager.h"
#include "Time.h"
#include "imgui.h"

class FlyCamera : public Camera{
public:
	FlyCamera();
	~FlyCamera();

	virtual void Update() override;

private:
	// For Camera Movenebt
	vec3 GetMouseCameraMovement();
	void UpdateMousePosition();

	// Mouse
	vec3 oldPos = vec3(0);
	vec3 currPos = vec3(0);
};

