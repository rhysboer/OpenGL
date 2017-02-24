#include "Terrain.h"

Terrain::Terrain() {
}

Terrain::~Terrain() {
	delete m_texture;
}

void Terrain::init(unsigned int rows, unsigned int cols) {

	//////////// TERRAIN CODE

	//const char* vsSource = "#version 410\n \
	//						layout(location=0) in vec4 position; \
	//						layout(location=1) in vec4 colour; \
	//						out vec4 vColour; \
	//						uniform mat4 projectionViewWorldMatrix; \
	//						void main() { vColour = colour; gl_Position = projectionViewWorldMatrix * position; }";
	//
	//const char* fsSource = "#version 410\n \
	//						in vec4 vColour; \
	//						out vec4 fragColor; \
	//						void main() { fragColor = vColour; }";
	//
	//this->m_rows = rows;
	//this->m_cols = cols;
	//
	//GenerateGrid();
	//
	//int success = GL_FALSE;
	//unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//
	//glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
	//glCompileShader(vertexShader);
	//
	//glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
	//glCompileShader(fragmentShader);
	//
	//m_programID = glCreateProgram();
	//glAttachShader(m_programID, vertexShader);
	//glAttachShader(m_programID, fragmentShader);
	//glLinkProgram(m_programID);
	//
	//glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	//if (success == GL_FALSE) {
	//	int infoLogLength = 0;
	//	glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	//	char* infolog = new char[infoLogLength];
	//
	//	glGetProgramInfoLog(m_programID, infoLogLength, 0, infolog);
	//	printf("Error: Failed to link shader program!\n");
	//	printf("%s\n", infolog);
	//	delete[] infolog;
	//}
	//
	//glDeleteShader(fragmentShader);
	//glDeleteShader(vertexShader);


	///////////////// TEXTURE CODE

	
	m_texture = new Texture("../bin/textures/wy.png");

	const char* vsSource = "#version 410\n \
							layout(location=0) in vec4 position; \
							layout(location=1) in vec2 texCoord; \
							out vec2 vTexCoord; \
							uniform mat4 projectionViewWorldMatrix; \
							void main() { \
							vTexCoord = texCoord; \
							gl_Position= projectionViewWorldMatrix * position;\ }";
	
	const char* fsSource = "#version 410\n \
							in vec2 vTexCoord; \
							out vec4 fragColor; \
							uniform sampler2D diffuse; \
							void main() { \
							fragColor = texture(diffuse,vTexCoord);\ }";

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(fragmentShader);

	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertexShader);
	glAttachShader(m_programID, fragmentShader);
	glLinkProgram(m_programID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	this->m_cols = cols;
	this->m_rows = rows;

	GenerateGrid();
}

void Terrain::GenerateGrid() {
	//Vertex* aoVertices = new Vertex[m_rows * m_cols];
	//for(unsigned int r = 0; r < m_rows; ++r) {
	//	for(unsigned int c = 0; c < m_cols; ++c) {
	//		aoVertices[r * m_cols + c].position = vec4((float)c, 0, (float)r, 1);
	//
	//		vec3 colour = vec3( sinf( (c / (float)(m_cols - 1)) * ( r / (float)(m_rows - 1))) );
	//		aoVertices[ r * m_cols + c ].colour = vec4( colour, 1 );
	//	} 
	//}
	//
	//// Generate Buffers
	//glGenBuffers(1, &m_VBO);
	//glGenBuffers(1, &m_IBO);
	//glGenVertexArrays(1, &m_VAO);
	//
	//
	//glBindVertexArray(m_VAO);
	//
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	//glBufferData(GL_ARRAY_BUFFER, (m_rows * m_cols) * sizeof(Vertex), aoVertices, GL_STATIC_DRAW);
	//
	//// defining index count based off quad count (2 triangle per quad)
	//unsigned int* auiIndices = new unsigned int[(m_rows - 1) * (m_cols - 1) * 6]; // DELETE
	//unsigned int index = 0;
	//
	//for (unsigned int r = 0; r < (m_rows - 1); ++r) {
	//	for (unsigned int c = 0; c < (m_cols - 1); ++c) {
	//
	//		// triangle 1
	//		auiIndices[index++] = r * m_cols + c;
	//		auiIndices[index++] = (r + 1) * m_cols + c;
	//		auiIndices[index++] = (r + 1) * m_cols + (c + 1);
	//
	//		// triangle 2
	//		auiIndices[index++] = r * m_cols + c;
	//		auiIndices[index++] = (r + 1) * m_cols + (c + 1);
	//		auiIndices[index++] = r * m_cols + (c + 1);
	//	}
	//}
	//
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));
	//
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, (m_rows - 1) * (m_cols - 1) * 6 * sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);
	//
	//glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//
	//delete[] aoVertices;







	///////// TEXTURE CODE
	//float vertexData[] = { 
	//	-5, 0, 5, 1, 0, 1, // 0
	//	5, 0, 5, 1, 1, 1, // 1
	//	5, 0, -5, 1, 1, 0//, // 2
	//	//-5, 0, -5, 1, 0, 0,  // 3
	//};
	//
	//unsigned int indexData[] = { 
	//	0, 1, 2
	//	//0, 2, 3,
	//};
	//
	//glGenVertexArrays(1, &m_VAO);
	//glBindVertexArray(m_VAO);
	//
	//glGenBuffers(1, &m_VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, vertexData, GL_STATIC_DRAW);
	//
	//glGenBuffers(1, &m_IBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indexData, GL_STATIC_DRAW); // * Index Buffer Size
	//
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	//
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, ((char*)0) + 16);
	//
	//glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);




	/////////// TESTING CODE
	//float vertexData[] = {
	//	-5, 0, 5, 1, 0, 1, // 0
	//	5, 0, 5, 1, 1, 1, // 1
	//	5, 0, -5, 1, 1, 0, // 2
	//	-5, 0, -5, 1, 0, 0,  // 3
	//};

	Vertex* aoVertices = new Vertex[m_rows * m_cols];
	for(unsigned int r = 0; r < m_rows; ++r) {
		for(unsigned int c = 0; c < m_cols; ++c) {
			aoVertices[r * m_cols + c].position = vec4((float)c, 0, (float)r, 1);

		} 
	}

	//aoVertices[0].position = vec4(-5, 0, 5, 1);
	//aoVertices[1].position = vec4(5, 0, 5, 1);
	//aoVertices[2].position = vec4(5, 0, -5, 1);
	//aoVertices[3].position = vec4(-5, 0, -5, 1);

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

	//auiIndices[0] = 0;
	//auiIndices[1] = 1;
	//auiIndices[2] = 2;
	//
	//auiIndices[3] = 0;
	//auiIndices[4] = 2;
	//auiIndices[5] = 3;

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (m_rows * m_cols) * sizeof(Vertex), aoVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (m_rows - 1) * (m_cols - 1) * 6 * sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex) * 2, 0);

	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, ((char*)0) + 16);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Terrain::Draw(Camera & camera) {

	glUseProgram(m_programID);
	int loc = glGetUniformLocation(m_programID, "projectionViewWorldMatrix");

	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(camera.GetProjectionView()));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture->GetTextureData());

	loc = glGetUniformLocation(m_programID, "diffuse");
	glUniform1i(loc, 0);

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	/////// TERRAIN
	//glUseProgram(m_programID);
	//unsigned int projectionViewUniform = glGetUniformLocation(m_programID, "projectionViewWorldMatrix");
	//glUniformMatrix4fv(projectionViewUniform, 1, false, glm::value_ptr(camera.GetProjectionView()));
	//glBindVertexArray(m_VAO);
	//unsigned int indexCount = (m_rows - 1) * (m_cols - 1) * 6;
	//glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}
