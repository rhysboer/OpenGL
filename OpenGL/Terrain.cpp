#include "Terrain.h"

Terrain::Terrain() {

	/*const char* vsSource = "#version 410\n \
							layout(location=0) in vec4 position; \
							layout(location=1) in vec4 color; \
							out vec4 vColor; \
							uniform mat4 projectionViewWorldMatrix; \
							void main() { vColor = colour; gl_Position = projectionViewWorldMatrix * position; }";

	const char* fsSource = "#version 410\n \
							in vec4 vColour; \
							out vec4 fragColor \
							void main() { fragColor = vColour; }";

	int success = GL_FALSE;
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertexShader);

	glShaderSource(fragmentShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertexShader);

	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertexShader);
	glAttachShader(m_programID, fragmentShader);
	glLinkProgram(m_programID);

	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if(success == GL_FALSE) {
		int infoLogLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infolog = new char[infoLogLength];

		glGetProgramInfoLog(m_programID, infoLogLength, 0, infolog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infolog);
		delete[] infolog;
	}




	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);*/
}


Terrain::~Terrain() {
}

void Terrain::Draw(Camera & camera) {
}

void Terrain::GenerateGrid(unsigned int rows, unsigned int cols) {

	//// defining index count based off quad count (2 triangle per quad)
	//unsigned int* auiIndices = new unsigned int[(rows - 1) * (cols - 1) * 6]; // DELETE
	//unsigned int index = 0;

	//Vertex* aoVertices = new Vertex[rows * cols];
	//for(unsigned int r = 0; r < rows; ++r) {
	//	for(unsigned int c = 0; c < cols; ++c) {

	//		// triangle 1
	//		auiIndices[index++] = r * cols + c;
	//		auiIndices[index++] = (r + 1) * cols + c;
	//		auiIndices[index++] = (r + 1) * cols + (c + 1);

	//		// triangle 2
	//		auiIndices[index++] = r * cols + c;
	//		auiIndices[index++] = (r + 1) * cols + (c + 1);
	//		auiIndices[index++] = r * cols + (c + 1);

	//		aoVertices[r*cols + c].position = vec4((float)c, 0, (float)r, 1);

	//		vec3 colour = vec3(sinf((c / (float)(cols - 1)) * (r / (float)(rows - 1))));
	//		aoVertices[r*cols + c].colour = vec4(colour, 1);
	//	}
	//}

	//// create and bind buffers to a vertex array object
	//glGenBuffers(1, &m_VBO);
	//glGenBuffers(1, &m_IBO);

	//glGenVertexArrays(1, &m_VAO);
	//glBindVertexArray(m_VAO);

	//glBindVertexArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//// fill index buffer
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, (rows - 1) * (cols - 1) * 6 * sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	//glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	//glBufferData(GL_ARRAY_BUFFER, (rows * cols) * sizeof(Vertex), aoVertices, GL_STATIC_DRAW);

	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));

	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//delete[] aoVertices;
}
