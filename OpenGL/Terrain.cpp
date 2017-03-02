#include "Terrain.h"

Terrain::Terrain() {
}

Terrain::~Terrain() {
	delete m_texture;
}

void Terrain::init(unsigned int rows, unsigned int cols) {
	m_texture = new Texture("../bin/textures/wy.png");

	shader.CreateShaderProgram("../shaders/TextureTerrain.vert", "../shaders/TextureTerrain.frag");

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

			aoVertices[r * m_cols + c].position = vec4((float)c, 0, (float)r, 1);
			aoVertices[r * m_cols + c].textPos = vec2(coordX, coordY);
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
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Terrain::Draw(Camera & camera) {

	shader.UseProgram();
	shader.SetMat4("projectionViewWorldMatrix", camera.GetProjectionView());
	shader.SetInt("diffuse", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture->GetTextureData());

	unsigned int indexCount = (m_rows - 1) * (m_cols - 1) * 6;

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}
