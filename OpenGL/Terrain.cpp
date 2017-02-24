#include "Terrain.h"

Terrain::Terrain() {
}

Terrain::~Terrain() {
	delete m_texture;
}

void Terrain::init(unsigned int rows, unsigned int cols) {
	const char* vsSource = "#version 410\n \
							layout(location=0) in vec4 position; \
							layout(location=1) in vec4 colour; \
							out vec4 vColour; \
							uniform mat4 projectionViewWorldMatrix; \
							void main() { vColour = colour; gl_Position = projectionViewWorldMatrix * position; }";

	const char* fsSource = "#version 410\n \
							in vec4 vColour; \
							out vec4 fragColor; \
							void main() { fragColor = vColour; }";

	this->m_rows = rows;
	this->m_cols = cols;

	GenerateGrid();

	int success = GL_FALSE;
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertexShader);

	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(fragmentShader);

	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertexShader);
	glAttachShader(m_programID, fragmentShader);
	glLinkProgram(m_programID);

	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		int infoLogLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infolog = new char[infoLogLength];

		glGetProgramInfoLog(m_programID, infoLogLength, 0, infolog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infolog);
		delete[] infolog;
	}

	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
}

void Terrain::GenerateGrid() {
	Vertex* aoVertices = new Vertex[m_rows * m_cols];
	for(unsigned int r = 0; r < m_rows; ++r) {
		for(unsigned int c = 0; c < m_cols; ++c) {
			aoVertices[r * m_cols + c].position = vec4((float)c, 0, (float)r, 1);
	
			vec3 colour = vec3( sinf( (c / (float)(m_cols - 1)) * ( r / (float)(m_rows - 1))) );
			aoVertices[ r * m_cols + c ].colour = vec4( colour, 1 );
		} 
	}
	
	// Generate Buffers
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);
	glGenVertexArrays(1, &m_VAO);
	
	
	glBindVertexArray(m_VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (m_rows * m_cols) * sizeof(Vertex), aoVertices, GL_STATIC_DRAW);
	
	// defining index count based off quad count (2 triangle per quad)
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
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (m_rows - 1) * (m_cols - 1) * 6 * sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	delete[] aoVertices;
}

void Terrain::Draw(Camera & camera) {
	glUseProgram(m_programID);
	unsigned int projectionViewUniform = glGetUniformLocation(m_programID, "projectionViewWorldMatrix");
	glUniformMatrix4fv(projectionViewUniform, 1, false, glm::value_ptr(camera.GetProjectionView()));
	glBindVertexArray(m_VAO);
	unsigned int indexCount = (m_rows - 1) * (m_cols - 1) * 6;
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}