#pragma once
#include "gl_core_4_4.h"
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"
#include "GLM\gtx\norm.hpp"
#include "GLFW\glfw3.h"

#include "ShaderLoader.h"
#include "Camera.h"
#include "Time.h"

// GUI
#include "imgui.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

struct Particle {
	vec3 position;
	vec3 velocity;
	vec4 colour;

	float size;
	float lifetime;
	float lifespan;
};

struct ParticleVertex {
	vec4 position;
	vec4 colour;
};

class ParticleEmitter {
public:
	ParticleEmitter();
	virtual ~ParticleEmitter();

	void Initialise(unsigned int a_maxParticles, unsigned int a_emitRate, float a_lifetimeMin, float a_lifetimeMax, float a_velocityMin, float a_velocityMax, float a_startSize, float a_endSize, const vec4& a_startColour, const vec4& a_endColour);
	void Draw(Camera camera);

	void Emit();

	void Update(const mat4 cameraView);

private:
	// Shader
	ShaderLoader m_shader = ShaderLoader();

	bool m_isEnabled = true;
	bool m_isPaused = false;

	Particle* m_particles;

	unsigned int m_firstDead;
	unsigned int m_maxParticles;

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;
	ParticleVertex* m_vertexData;

	vec3 m_position;

	float m_emitTimer;
	float m_emitRate;

	float m_lifespanMin;
	float m_lifespanMax;

	float m_velocityMin;
	float m_velocityMax;

	float m_startSize;
	float m_endSize;

	vec4 m_startColour;
	vec4 m_endColour;
};

