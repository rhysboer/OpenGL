#include "Terrain.h"

Terrain::Terrain() {
}

Terrain::~Terrain() {
	delete m_grass;
}

void Terrain::init(unsigned int rows, unsigned int cols) {

	// Lights
	m_sun = new Light();
	m_sun->LookAt(vec3(1, 0, 0), vec3(0), vec3(0, 1, 0));
	m_sun->SetOrtho(vec2(-10, 10), vec2(-10, 10), vec2(-10, 10));
	m_sun->SetDirection(vec3(1, 2.5f, 1));

	// Create Texture
	m_grass = new Texture("../bin/textures/grass.png");
	m_stone = new Texture("../bin/textures/stone.png");
	m_snow = new Texture("../bin/textures/snow.png");
	m_sand = new Texture("../bin/textures/sand.png");

	// Load in shaders
	m_shader.CreateShaderProgram("../shaders/TextureTerrain.vert", "../shaders/TextureTerrain.frag");

	// Set terrain width and length
	this->m_cols = cols;
	this->m_rows = rows;

	// Generate The Terrain
	GenerateGrid();

	// Generate Depth Buffer
	GenerateDepthBuffer();
}

void Terrain::GenerateGrid() {

	// Generate Vertices
	Vertex* aoVertices = new Vertex[m_rows * m_cols];
	for (unsigned int r = 0; r < m_rows; ++r) {
		for (unsigned int c = 0; c < m_cols; ++c) {
			float coordX = (float)c / (m_rows - 1);
			float coordY = (float)r / (m_cols - 1);

			// aoVertices[r * m_cols + c].position = vec4((float)c - 15, 0, (float)r -15, 1);
			aoVertices[r * m_cols + c].texCoord = vec2(coordX, coordY);

			// Perlin Test

			//float* perlinData = new float[m_rows * m_cols];
			float perlinData = 0;
			float scale = (1.0f / m_cols) * 3;
			int octaves = 6;

			float amplitude = 1.0f;
			float persistence = 0.3f;
			//perlinData[r * m_cols + c] = 0;

			for (int i = 0; i < octaves; ++i) {
				float freq = powf(2, (float)i);
				float perlinSample = perlin(vec2((float)r, (float)c) * scale * freq) * 0.5f + 0.5f;

				perlinData += perlinSample * amplitude;
				amplitude *= persistence;
			}

			aoVertices[r * m_cols + c].position = vec4((float)c - 15, perlinData * 10, (float)r - 15, 1);
		} 
	}

	// Height Map
	float* perlinData = new float[m_rows * m_cols];
	float scale = (1.0f / m_cols) * 3;
	int octaves = 6;

	//for(int x = 0; x < m_rows; ++x) {
	//	for(int y = 0; y < m_cols; ++y) {
	//
	//		float amplitude = 1.0f;
	//		float persistence = 0.3f;
	//		perlinData[x * m_cols + y] = 0;
	//
	//		for(int i = 0; i < octaves; ++i) {
	//			float freq = powf(2, (float)i);
	//			float perlinSample = perlin(vec2((float)x, (float)y) * scale * freq) * 0.5f + 0.5f;
	//
	//			perlinData[x * m_cols + y] += perlinSample * amplitude;
	//			amplitude *= persistence;
	//		}
	//	}
	//}

	// Add Normals
	for(GLuint i = 1; i < m_rows - 1; ++i) {
		for(GLuint j = 1; j < m_cols - 1; ++j) {
			vec3 up =		(vec3)aoVertices[(i - 1) * m_cols + j].position; //up
			vec3 upRight =	(vec3)aoVertices[(i - 1) * m_cols + (j + 1)].position; //upRight
			vec3 down =		(vec3)aoVertices[(i + 1) * m_cols + j].position; //down
			vec3 downLeft =	(vec3)aoVertices[(i + 1) * m_cols + (j - 1)].position; //downLeft
			vec3 left =		(vec3)aoVertices[i * m_cols + (j - 1)].position; //left
			vec3 right =	(vec3)aoVertices[i * m_cols + (j + 1)].position; //right
			
			vec3 normal1 = glm::cross(up, left);
			vec3 normal2 = glm::cross(upRight, up);
			vec3 normal3 = glm::cross(right, upRight);
			vec3 normal4 = glm::cross(down, right);
			vec3 normal5 = glm::cross(downLeft, down);
			vec3 normal6 = glm::cross(left, downLeft);
			
			vec3 sum = normal1 + normal2 + normal3 + normal4 + normal5 + normal6;
			
			aoVertices[i * m_cols + j].normal = (glm::length2(sum) == 0) ? vec4(sum, 0) : vec4(glm::normalize(sum), 0);
		}
	}

	unsigned int* auiIndices = new unsigned int[(m_rows - 1) * (m_cols - 1) * 6]; // DELETE
	unsigned int index = 0;

	// Create Index buffer
	for (unsigned int r = 0; r < (m_rows - 1); ++r) {
		for (unsigned int c = 0; c < (m_cols - 1); ++c) {
	
			// triangle 1
			auiIndices[index++] = r * m_cols + c;					
			auiIndices[index++] = (r + 1) * m_cols + c;				
			auiIndices[index++] = (r + 1) * m_cols + (c + 1);       
	
			// triangle 2
			auiIndices[index++] = r * m_cols + c;					
			auiIndices[index++] = (r + 1) * m_cols + (c + 1);		
			auiIndices[index++] = r * m_cols + (c + 1);				
		}
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Generate perlin texture
	glGenTextures(1, &m_perlinTexture);
	glBindTexture(GL_TEXTURE_2D, m_perlinTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, m_rows, m_cols, 0, GL_RED, GL_FLOAT, perlinData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// End

	// Terrain Arrays
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (m_rows * m_cols) * sizeof(Vertex), aoVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (m_rows - 1) * (m_cols - 1) * 6 * sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // Position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(1); // Texture Coord
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));

	glEnableVertexAttribArray(2); // Texture Coord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4) * 2));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] auiIndices;
	delete[] aoVertices;
}

void Terrain::Draw(Camera & camera) {

	// Wire Frame
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	GenerateShadowMap();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 1280, 720);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shader.UseProgram();
	m_shader.SetMat4("projectionViewWorldMatrix", camera.GetProjectionView());
	m_shader.SetVec2("textureRepeat", m_textureRepeatAmount);
	m_shader.SetInt("perlinTexture", 0);
	
	m_shader.SetInt("grass", 1);
	m_shader.SetInt("stone", 2);
	m_shader.SetInt("snow", 3);
	m_shader.SetInt("sand", 4);

	// For Shadows
	m_shader.SetVec3("lightDir", vec3(2, 0, 0));
	m_shader.SetInt("shadowMap", 5);
	m_shader.SetMat4("lightMatrix", m_sun->GetTextureSpaceOffset() * m_sun->GetViewMatrix());

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, m_fboDepth);



	// Set Perlin Texture in Vert Shader
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_perlinTexture);

	// Set Grass Texture
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_grass->GetTextureData());

	// Set Stone Texture
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_stone->GetTextureData());

	// Set Snow Texture
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_snow->GetTextureData());

	// Set Sand Texture
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, m_sand->GetTextureData());

	unsigned int indexCount = (m_rows - 1) * (m_cols - 1) * 6;

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

void Terrain::TotalTextureRepeat(uvec2 value) {
	m_textureRepeatAmount = value;
}

// Generate Texture & stuff
void Terrain::GenerateDepthBuffer() {

	// Load in shaders
	m_shadowShader.CreateShaderProgram("../shaders/GenTerrainShadow.vert", "../shaders/GenTerrainShadow.frag");

	// Frame Buffer
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	// Depth Texture
	glGenTextures(1, &m_fboDepth);
	glBindTexture(GL_TEXTURE_2D, m_fboDepth);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_fboDepth, 0);

	glDrawBuffer(GL_NONE);

	// Error Check
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return;
}

// Generate Shadow Map ( In Draw )
void Terrain::GenerateShadowMap() {
	
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glViewport(0, 0, 1024, 1024);
	glClear(GL_DEPTH_BUFFER_BIT);

	// Set Shadow variables
	m_shadowShader.SetMat4("lightMatrix", m_sun->GetViewMatrix());
	m_shadowShader.UseProgram();

	// Draw Terrain
	unsigned int indexCount = (m_rows - 1) * (m_cols - 1) * 6;

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}
