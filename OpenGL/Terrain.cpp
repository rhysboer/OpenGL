#include "Terrain.h"

Terrain::Terrain() {
}

Terrain::~Terrain() {
	delete m_texture;
}

void Terrain::init(unsigned int rows, unsigned int cols) {
	m_texture = new Texture("../bin/textures/wy.png");

	shader.CreateShaderProgram("../shaders/Shadow.vert", "../shaders/Shadow.frag");

	this->m_cols = cols;
	this->m_rows = rows;

	GenerateGrid();
}

void Terrain::GenerateGrid() {
	Vertex* aoVertices = new Vertex[m_rows * m_cols];
	for (unsigned int r = 0; r < m_rows; ++r) {
		for (unsigned int c = 0; c < m_cols; ++c) {
			float coordX = (float)c / (m_rows - 1);
			float coordY = (float)r / (m_cols - 1);

			aoVertices[r * m_cols + c].position = vec4((float)c - 25, 0, (float)r -25, 1);
			aoVertices[r * m_cols + c].textPos = vec2(coordX, coordY);
		} 
	}

	for(GLuint i = 1; i < m_rows; ++i) {
		for(GLuint j = 1; j < m_cols; ++j) {
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

}

void Terrain::Draw(Camera & camera) {

	shader.UseProgram();
	shader.SetMat4("projectionViewWorldMatrix", camera.GetProjectionView());
	shader.SetInt("diffuse", 0);

	// For Shadows
	shader.SetVec3("lightDir", vec3(sin(glfwGetTime()), 1, 0));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture->GetTextureData());

	unsigned int indexCount = (m_rows - 1) * (m_cols - 1) * 6;

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}
