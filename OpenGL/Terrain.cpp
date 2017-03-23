#include "Terrain.h"

Terrain::Terrain() {
}

Terrain::~Terrain() {
	delete m_grass;
	delete m_stone;
	delete m_snow;
	delete m_sand;
}

void Terrain::init(unsigned int rows, unsigned int cols) {

	// Create Texture
	m_grass = new Texture("../bin/textures/grass.png");
	m_stone = new Texture("../bin/textures/stone.png");
	m_snow = new Texture("../bin/textures/snow.png");
	m_sand = new Texture("../bin/textures/sand.png");

	// Load in shaders
	m_shader.CreateShaderProgram("../shaders/TextureTerrain.vert", "../shaders/TextureTerrain.frag");

	// Set terrain width and length
	this->m_cols = cols + 1;
	this->m_rows = rows + 1;

	aoVertices = new Vertex[m_rows * m_cols];

	// Generate The Terrain
	GenerateGrid();
}

void Terrain::GenerateGrid() {
	
	int randNum = rand() % RAND_MAX;

	float* perlinData = new float[m_rows * m_cols];
	for(unsigned int r = 0; r < m_rows; ++r) {
		for(unsigned int c = 0; c < m_cols; ++c) {
			float coordX = (float)c / (m_rows - 1);
			float coordY = (float)r / (m_cols - 1);

			aoVertices[r * m_cols + c].texCoord = vec2(coordX, coordY);
			
			float scale = (1.0f / m_cols) * 3;
			int octaves = 6;

			float amplitude = 1.0f;
			float persistence = 0.3f;
			perlinData[r * m_cols + c] = 0;

			for(int i = 0; i < octaves; ++i) {
				float freq = powf(2, (float)i);
				float perlinSample = perlin(vec2((float)r + randNum, (float)c + randNum) * scale * freq) * 0.5f + 0.5f;

				perlinData[r * m_cols + c] += perlinSample * amplitude;
				amplitude *= persistence;
			}

			aoVertices[r * m_cols + c].position = vec4((float)c, perlinData[r * m_cols + c] * 10, (float)r, 1);
		}
	}

	// Add Normals onto terrain
	for(GLuint i = 0; i < m_rows; ++i) {
		for(GLuint j = 0; j < m_cols; ++j) {

			int posCurr =	i * m_cols + j;
			int posUp =		i * m_cols + (j - 1);
			int posDown =	i * m_cols + (j + 1);
			int posLeft =	(i + 1) * m_cols + j;
			int posRight =	(i - 1) * m_cols + j;

			if ((i == 0 && j == 0) || (i == m_rows-1 && j == 0) || (i == 0 && j == m_cols-1) || (i == m_rows-1 && j == m_cols-1)) {
				// Corners

				vec3 neighbourY = (posCurr % m_cols == 0) ? (vec3)aoVertices[posDown].position : (vec3)aoVertices[posUp].position;
				vec3 neighbourX = (posRight > 0) ? (vec3)aoVertices[posRight].position : (vec3)aoVertices[posLeft].position;
				vec3 a = (vec3)aoVertices[posCurr].position - neighbourY;
				vec3 b = (vec3)aoVertices[posCurr].position - neighbourX;

				vec4 normal = normalize(vec4(cross(a, b), 0));

				if (i == 0 && j == 0 || i == m_rows - 1 && j == m_cols - 1) {
					aoVertices[posCurr].normal = -normal;
				} else {
					aoVertices[posCurr].normal = normal;
				}
			}else if ((i == 0 && j > 0 && j < m_cols - 1) || (i > 0 && i < m_rows-1 && j == m_cols-1)) {
				// Right & bottom border 

				vec3 neighbourY = (vec3)aoVertices[posUp].position;
				vec3 neighbourX = (vec3)aoVertices[posLeft].position;

				vec3 a = (vec3)aoVertices[posCurr].position - neighbourY;
				vec3 b = (vec3)aoVertices[posCurr].position - neighbourX;

				vec4 normal = normalize(vec4(cross(a,b), 0));

				aoVertices[posCurr].normal = normal;
			} else if ((i > 0 && i < m_rows - 1 && j == 0) || (i == m_rows -1 && j > 0 && j < m_cols-1)) {
				// Left & top border

				vec3 neighbourY = (vec3)aoVertices[posDown].position;
				vec3 neighbourX = (vec3)aoVertices[posRight].position;

				vec3 a = (vec3)aoVertices[posCurr].position - neighbourY;
				vec3 b = (vec3)aoVertices[posCurr].position - neighbourX;

				vec4 normal = normalize(vec4(cross(a, b), 0));

				aoVertices[posCurr].normal = normal;
			} else {
				// If vertex is inside
				vec3 zero = vec3(0);

				vec3 up = (posCurr % m_cols == 0) ? zero : (vec3)aoVertices[posUp].position;
				vec3 down = (posDown % m_cols == 0) ? zero : (vec3)aoVertices[posDown].position;
				vec3 left = (posLeft >= m_rows * m_cols) ? zero : (vec3)aoVertices[posLeft].position;
				vec3 right = (posRight < 0) ? zero : (vec3)aoVertices[posRight].position;

				vec3 normal1 = glm::cross(up, left);
				vec3 normal2 = glm::cross(right, up);
				vec3 normal3 = glm::cross(down, right);
				vec3 normal4 = glm::cross(left, down);

				vec3 total = normal1 + normal2 + normal3 + normal4;
				aoVertices[i * m_cols + j].normal = vec4(normalize(vec4(total, 0)));
			}
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

	glEnableVertexAttribArray(1); // Normal
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
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	unsigned int indexCount = (m_rows - 1) * (m_cols - 1) * 6;
	
	m_shader.UseProgram();
	m_shader.SetMat4("projectionViewWorldMatrix", camera.GetProjectionView());
	
	m_shader.SetVec2("textureRepeat", m_textureRepeatAmount);

	m_shader.SetInt("perlinTexture", 0);
	m_shader.SetInt("grass", 1);
	m_shader.SetInt("stone", 2);
	m_shader.SetInt("snow", 3);
	m_shader.SetInt("sand", 4);
	
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
	
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

void Terrain::TotalTextureRepeat(uvec2 value) {
	m_textureRepeatAmount = value;
}