#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter() : m_particles(nullptr), m_firstDead(0), m_maxParticles(0), m_position(0,0,0), m_VAO(0), m_VBO(0), m_IBO(0), m_vertexData(nullptr){

}

ParticleEmitter::~ParticleEmitter() {
	delete[] m_particles;
	delete[] m_vertexData;

	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
}

void ParticleEmitter::Initialise(unsigned int a_maxParticles, unsigned int a_emitRate, float a_lifetimeMin, float a_lifetimeMax, float a_velocityMin, float a_velocityMax, float a_startSize, float a_endSize, const vec4& a_startColour, const vec4& a_endColour) {
	// Load in shader
	m_shader.CreateShaderProgram("../shaders/Particle.vert", "../shaders/Particle.frag");
	
	// Emit Timers
	m_emitTimer		= 0.0f;
	m_emitRate		= 1.0f / a_emitRate;

	// Variables
	m_startColour	= a_startColour;
	m_endColour		= a_endColour;
	m_startSize		= a_startSize;
	m_endSize		= a_endSize;
	m_velocityMin	= a_velocityMin;
	m_velocityMax	= a_velocityMax;
	m_lifespanMin	= a_lifetimeMin;
	m_lifespanMax	= a_lifetimeMax;
	m_maxParticles	= a_maxParticles;

	// Particle Array
	m_particles		= new Particle[m_maxParticles];
	m_firstDead		= 0;

	// 4 particles per quad
	m_vertexData	= new ParticleVertex[m_maxParticles * 4];


	// Index Buffer for particles
	unsigned int* indexData = new unsigned int[m_maxParticles * 6];
	for(unsigned int i = 0; i < m_maxParticles; ++i) {
		indexData[i * 6 + 0] = i * 4 + 0;
		indexData[i * 6 + 1] = i * 4 + 1;
		indexData[i * 6 + 2] = i * 4 + 2;

		indexData[i * 6 + 3] = i * 4 + 0;
		indexData[i * 6 + 4] = i * 4 + 2;
		indexData[i * 6 + 5] = i * 4 + 3;
	}

	// Create Opengl buffers
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_maxParticles * 4 * sizeof(ParticleVertex), m_vertexData, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_maxParticles * 6 * sizeof(unsigned int), indexData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // Position;
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), 0);

	glEnableVertexAttribArray(1); // Colour
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), (void*)sizeof(vec4)); // ((char*)0) + 16

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] indexData;
}

void ParticleEmitter::Draw(Camera camera) {

	m_shader.SetMat4("projectionView", camera.GetProjectionView());
	
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_firstDead * 4 * sizeof(ParticleVertex), m_vertexData);

	// draw particles 
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_firstDead * 6,GL_UNSIGNED_INT, 0);

}

// Emit Particles
void ParticleEmitter::Emit() {
	if(m_firstDead >= m_maxParticles)
		return;

	// Revive first dead particle
	Particle& particle = m_particles[m_firstDead++];

	// Set Position
	particle.position = m_position;

	// Random lifespan
	particle.lifetime = 0.0f;
	particle.lifespan = (rand() / (float)RAND_MAX) * (m_lifespanMax - m_lifespanMin) + m_lifespanMin;

	// Set Size & Colour
	particle.colour = m_startColour;
	particle.size = m_startSize;

	// Random velocity & direction
	float velocity = (rand() / (float)RAND_MAX) * (m_velocityMax - m_velocityMin) + m_velocityMin;
	particle.velocity.x = (rand() / (float)RAND_MAX) * 2 - 1;
	particle.velocity.y = (rand() / (float)RAND_MAX) * 2 - 1;
	particle.velocity.z = (rand() / (float)RAND_MAX) * 2 - 1;
	particle.velocity = glm::normalize(particle.velocity) * velocity;
}

void ParticleEmitter::Update(mat4 cameraView) {

	m_emitTimer += Time::DeltaTime();
	while(m_emitTimer > m_emitRate) {
		Emit();

		m_emitTimer -= m_emitRate;
	}

	unsigned int quad = 0;

	for(unsigned int i = 0; i < m_firstDead; i++) {
		Particle* particle = &m_particles[i];

		particle->lifetime += Time::DeltaTime();
		if(particle->lifetime >= particle->lifespan) {

			// Swap last alive with this one
			*particle = m_particles[m_firstDead - 1];
			m_firstDead--;
		} else {
			// Update Particle Variables
			particle->position += particle->velocity * Time::DeltaTime();
			particle->size = glm::mix(m_startSize, m_endSize, particle->lifetime / particle->lifespan);
			particle->colour = glm::mix(m_startColour, m_endColour, particle->lifetime / particle->lifespan);
			
			// Create Quad
			float halfSize = particle->size * 0.5f;
			
			m_vertexData[quad * 4 + 0].position	= vec4(halfSize, halfSize, 0, 1);
			m_vertexData[quad * 4 + 0].colour	= particle->colour;
			
			m_vertexData[quad * 4 + 1].position = vec4(-halfSize, halfSize, 0, 1);
			m_vertexData[quad * 4 + 1].colour = particle->colour;
			
			m_vertexData[quad * 4 + 2].position = vec4(-halfSize, -halfSize, 0, 1);
			m_vertexData[quad * 4 + 2].colour = particle->colour;
			
			m_vertexData[quad * 4 + 3].position = vec4(halfSize, -halfSize, 0, 1);
			m_vertexData[quad * 4 + 3].colour = particle->colour;
			
			// Create Billboard
			vec3 zAxis = glm::normalize(vec3(cameraView[3]) - particle->position);
			vec3 xAxis = glm::cross(vec3(cameraView[1]), zAxis);
			vec3 yAxis = glm::cross(zAxis, xAxis);
			
			mat4 billboard(vec4(xAxis, 0), vec4(yAxis, 0), vec4(zAxis, 0), vec4(0, 0, 0, 1));
			
			m_vertexData[quad * 4 + 0].position = billboard * m_vertexData[quad * 4 + 0].position + vec4(particle->position, 0);
			m_vertexData[quad * 4 + 1].position = billboard * m_vertexData[quad * 4 + 1].position + vec4(particle->position, 0);
			m_vertexData[quad * 4 + 2].position = billboard * m_vertexData[quad * 4 + 2].position + vec4(particle->position, 0);
			m_vertexData[quad * 4 + 3].position = billboard * m_vertexData[quad * 4 + 3].position + vec4(particle->position, 0);
			
			++quad;
		}
	}
}
