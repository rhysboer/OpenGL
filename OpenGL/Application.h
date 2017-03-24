#pragma once
#include <iostream>

// Base
#include "BaseApplication.h"
#include "AIE\Gizmos.h"
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"
#include "Colors.h"
#include "FlyCamera.h"
#include "Time.h"
#include "ParticleEmitter.h"
#include "PostProcessing.h"

// Object Loading / Animation
#include "tiny_obj_loader.h"
#include "OBJLoader.h"
#include "OBJAnimation.h"

// Quanternion
#include <GLM\gtc\quaternion.hpp>
#include <GLM\gtx\quaternion.hpp>

// Terrain Mesh
#include "Terrain.h"
#include "Water.h"

// Managers
#include "InputManager.h"
#include "LightManager.h"

// GUI
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

class Application : public BaseApplication {
public:
	Application(int width, int height, const char* name);
	~Application();

	const bool Update();
	void Draw();

	const bool Startup();
	void Shutdown();

private:
	// New Terrain
	Terrain m_terrain = Terrain();

	// Camera
	FlyCamera m_camera;

	// CUBE
	mat4 m_cubeMat = mat4(1);
	vec3 m_position[2];
	quat m_rotation[2];

	mat4 m_sunMat = mat4(1);
	mat4 m_earthMat = mat4(1);
	mat4 m_earthLocal = mat4(1);
	mat4 m_moonMat = mat4(1);
	mat4 m_moonLocal = mat4(1);

	// Rotation Matrices
	mat4 m_sunRotation = mat4(1);
	mat4 m_earthRotation = mat4(1);
	mat4 m_moonRotation = mat4(1);

	// Obj loader
	OBJLoader* m_objLoader = nullptr;
	// Animation
	OBJAnimation* m_animation = nullptr;
	// Particle Effect Emitter
	ParticleEmitter* m_particleEmitter = nullptr;
	// Post Processing Effect
	PostProcessing* m_effects = nullptr;
};

