#define TINYOBJLOADER_IMPLEMENTATION
#include "OBJLoader.h"

OBJLoader::OBJLoader() {
	// Vertex Shader
	const char* vsSource = "#version 410\n \
							layout(location=0) in vec4 position; \
							layout(location=1) in vec4 normal; \
							out vec4 vPosition; \
							out vec4 vColour; \
							out vec4 vNormal; \
							uniform mat4 projectionViewWorldMatrix; \
							void main() { \
								vPosition = position; \
								vNormal = normal; \
								gl_Position = projectionViewWorldMatrix * position; \
							}";

	// Fragment Shader
	const char* fsSource = "#version 410\n \
							vec4 ambientLight = vec4(0.50f, 0.5f, 0.5f, 1); \
							in vec4 vPosition; \
							in vec4 vNormal; \
							out vec4 fragColor; \
							uniform vec3 lightDirection; \
							uniform vec3 lightColor; \
							uniform vec3 cameraPos; \
							uniform float specPow; \
							void main() { \
								float d = max(0, dot(normalize(vNormal.xyz), lightDirection)); \
								vec3 E = normalize(cameraPos - vPosition.xyz); \
								vec3 R = reflect(-lightDirection, vNormal.xyz); \
								float s = max(0, dot(E,R)); \
								s = pow(s, specPow); \
								fragColor = vNormal * ambientLight; \
							}";

	//vec4(vNormal.xyz * d + lightColor * s, 1); \

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
	glDeleteShader(vertexShader);
}

OBJLoader::~OBJLoader() {
}

void OBJLoader::Draw(Camera camera) {

	// Camera World View
	glUseProgram(m_programID);
	unsigned int projectionViewUniform = glGetUniformLocation(m_programID, "projectionViewWorldMatrix");
	glUniformMatrix4fv(projectionViewUniform, 1, false, glm::value_ptr(camera.GetProjectionView()));

	// light Direction
	vec3 lightDirection = vec3(sin(glfwGetTime()), cos(glfwGetTime()), 0);
	unsigned int light = glGetUniformLocation(m_programID, "lightDirection");
	glUniform3f(light, lightDirection.x, lightDirection.y, lightDirection.z);

	// Light Color
	vec4 lightColor = Colors::White;
	unsigned int color = glGetUniformLocation(m_programID, "lightColor");
	glUniform3f(color, lightColor.x, lightColor.y, lightColor.z);

	// Camera Position
	vec3 pos = camera.GetPosition();
	unsigned int cameraPos = glGetUniformLocation(m_programID, "cameraPos");
	glUniform3f(cameraPos, pos.x, pos.y, pos.z);

	// Specular Power
	glUniform1f(glGetUniformLocation(m_programID, "specPow"), 128.0f);

	for(auto& gl : m_glInfo) { 
		glBindVertexArray(gl.m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, gl.m_faceCount * 3);
 }
}

void OBJLoader::LoadObject(tinyobj::attrib_t & attribs, std::vector<tinyobj::shape_t>& shapes) {
	m_glInfo.resize(shapes.size());
	// grab each shape 
	int shapeIndex = 0; 
	for (auto& shape : shapes) { 
	// setup OpenGL data 
		glGenVertexArrays(1, &m_glInfo[shapeIndex].m_VAO); 
		glGenBuffers(1, &m_glInfo[shapeIndex].m_VBO); 
		glBindVertexArray(m_glInfo[shapeIndex].m_VAO);
		m_glInfo[shapeIndex].m_faceCount = shape.mesh.num_face_vertices.size(); 
		// collect triangle vertices 
		std::vector<OBJVertex> vertices; 
		int index = 0; 
		for (auto face : shape.mesh.num_face_vertices) 
		{ 
			for (int i = 0; i < 3; ++i) { 
				tinyobj::index_t idx = shape.mesh.indices[index + i]; 

				OBJVertex v = { 0 }; 

				// positions
				v.x = attribs.vertices[3 * idx.vertex_index + 0]; 
				v.y = attribs.vertices[3 * idx.vertex_index + 1];
				v.z = attribs.vertices[3 * idx.vertex_index + 2];

				// normals 
				if (attribs.normals.size() > 0) { 
					v.nx = attribs.normals[3 *idx.normal_index + 0];
					v.ny = attribs.normals[3 *idx.normal_index + 1];
					v.nz = attribs.normals[3 *idx.normal_index + 2];
				} 
				// texture coordinates 
				if (attribs.texcoords.size() > 0) { 
					v.u = attribs.texcoords[2*idx.texcoord_index+0];
					v.v = attribs.texcoords[2*idx.texcoord_index+1];
				} 
				
				vertices.push_back(v);
			} 

			index += face;
		} // bind vertex data 

		glBindBuffer(GL_ARRAY_BUFFER, m_glInfo[shapeIndex].m_VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(OBJVertex), vertices.data(), GL_STATIC_DRAW); 

		glEnableVertexAttribArray(0); // position 
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OBJVertex), 0);

		glEnableVertexAttribArray(1); // normal data 
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(OBJVertex), (void*)12);

		glEnableVertexAttribArray(2); // texture data 
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(OBJVertex), (void*)24);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		shapeIndex++;
	} 
}
