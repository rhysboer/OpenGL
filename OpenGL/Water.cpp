#include "Water.h"

Water::Water() {
}

Water::~Water() {
	delete m_waterTexture;
}

void Water::Init(uvec2 size) {
	// Water Textures
	m_waterTexture = new Texture("../bin/textures/sand.png");
	
	// Water Shaders
	m_shader.CreateShaderProgram("../shaders/Water.vert", "../shaders/Water.frag");

	m_size = size;

	BuildMesh();
}

void Water::BuildMesh() {

	// Generate Vertices
	WaterVertex* aoVertices = new WaterVertex[m_size.x * m_size.y];
	for(unsigned int r = 0; r < m_size.x; ++r) {
		for(unsigned int c = 0; c < m_size.y; ++c) {
			float coordX = (float)c / (m_size.x - 1);
			float coordY = (float)r / (m_size.y - 1);

			aoVertices[r * m_size.y + c].position = vec4((float)c, 0, (float)r, 1);
			aoVertices[r * m_size.y + c].texCoord = vec2(coordX, coordY);
		}
	}

	// Height Map
	float* perlinData = new float[m_size.x * m_size.y];
	float scale = (1.0f / m_size.y) * 3;
	int octaves = 6;

	for(unsigned int x = 0; x < m_size.x; ++x) {
		for(unsigned int y = 0; y < m_size.y; ++y) {

			float amplitude = 1.0f;
			float persistence = 0.3f;
			perlinData[x * m_size.y + y] = 0;

			for(int i = 0; i < octaves; ++i) {
				float freq = powf(2, (float)i);
				float perlinSample = perlin(vec2((float)x, (float)y) * scale * freq) * 0.5f + 0.5f;

				perlinData[x * m_size.y + y] += perlinSample * amplitude;
				amplitude *= persistence;
			}
		}
	}

	// Add Normals
	for(GLuint i = 1; i < m_size.x - 1; ++i) {
		for(GLuint j = 1; j < m_size.y - 1; ++j) {
			vec3 up = (vec3)aoVertices[(i - 1) * m_size.y + j].position; //up
			vec3 upRight = (vec3)aoVertices[(i - 1) * m_size.y + (j + 1)].position; //upRight
			vec3 down = (vec3)aoVertices[(i + 1) * m_size.y + j].position; //down
			vec3 downLeft = (vec3)aoVertices[(i + 1) * m_size.y + (j - 1)].position; //downLeft
			vec3 left = (vec3)aoVertices[i * m_size.y + (j - 1)].position; //left
			vec3 right = (vec3)aoVertices[i * m_size.y + (j + 1)].position; //right

			vec3 normal1 = glm::cross(up, left);
			vec3 normal2 = glm::cross(upRight, up);
			vec3 normal3 = glm::cross(right, upRight);
			vec3 normal4 = glm::cross(down, right);
			vec3 normal5 = glm::cross(downLeft, down);
			vec3 normal6 = glm::cross(left, downLeft);

			vec3 sum = normal1 + normal2 + normal3 + normal4 + normal5 + normal6;

			aoVertices[i * m_size.y + j].normal = (glm::length2(sum) == 0) ? vec4(sum, 0) : vec4(glm::normalize(sum), 0);
		}
	}

	unsigned int* auiIndices = new unsigned int[(m_size.x - 1) * (m_size.y - 1) * 6]; // DELETE
	unsigned int index = 0;

	// Create Index buffer
	for(unsigned int r = 0; r < (m_size.x - 1); ++r) {
		for(unsigned int c = 0; c < (m_size.y - 1); ++c) {

			// triangle 1
			auiIndices[index++] = r * m_size.y + c;
			auiIndices[index++] = (r + 1) * m_size.y + c;
			auiIndices[index++] = (r + 1) * m_size.y + (c + 1);

			// triangle 2
			auiIndices[index++] = r * m_size.y + c;
			auiIndices[index++] = (r + 1) * m_size.y + (c + 1);
			auiIndices[index++] = r * m_size.y + (c + 1);
		}
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (m_size.x * m_size.y) * sizeof(WaterVertex), aoVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (m_size.x - 1) * (m_size.y - 1) * 6 * sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // Position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(WaterVertex), 0);

	glEnableVertexAttribArray(1); // Texture Coord
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(WaterVertex), (void*)(sizeof(vec4)));

	glEnableVertexAttribArray(2); // Texture Coord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(WaterVertex), (void*)(sizeof(vec4) * 2));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] auiIndices;
	delete[] aoVertices;
}

void Water::Draw(Camera & camera) {
	m_shader.UseProgram();
	m_shader.SetMat4("projectionViewWorldMatrix", camera.GetProjectionView());
	m_shader.SetFloat("time", (float)glfwGetTime());

	// Wave Settings
	m_shader.SetFloat("waveHeight", m_waveHeight);
	m_shader.SetFloat("waveSpeed", m_waveSpeed);

	// Texture
	m_shader.SetInt("waterTexture", 0);
	m_shader.SetInt("repeatCount", m_repeatCount);
	m_shader.SetFloat("scrollSpeed", m_textureScrollSpeed);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_waterTexture->GetTextureData());

	unsigned int indexCount = (m_size.x - 1) * (m_size.y - 1) * 6;

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}
