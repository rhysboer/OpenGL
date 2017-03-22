#define TINYOBJLOADER_IMPLEMENTATION
#include "OBJLoader.h"

OBJLoader::OBJLoader() {
	// Load in shader
	shader.CreateShaderProgram("../shaders/PhongLight.vert", "../shaders/PhongLight.frag");
	postShader.CreateShaderProgram("../shaders/PostProcess.vert", "../shaders/PostProcess.frag");


	//shadow.UseProgram();
	//// Shadow Test
	//glGenFramebuffers(1, &m_fbo);
	//glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	//
	//glGenTextures(1, &m_fboDepth);
	//glBindTexture(GL_TEXTURE_2D, m_fboDepth);
	//
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_fboDepth, 0);
	//
	//glDrawBuffer(GL_NONE);
	//
	//GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	//if(status != GL_FRAMEBUFFER_COMPLETE) {
	//	printf("FRAMEBUFFER ERROR! you dun goofed\n");
	//}
	//
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);


	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	glGenTextures(1, &m_fboTexture);
	glBindTexture(GL_TEXTURE_2D, m_fboTexture);

	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, 1280, 720);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_fboTexture, 0);

	glGenRenderbuffers(1, &m_fboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, m_fboDepth);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 1280, 720);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_fboDepth);

	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Fullscreen quad
	vec2 halfTexel = 1.0f / vec2(1280, 720) * 0.5f;

	float vertexData[] = {
		-1, -1, 0, 1, halfTexel.x, halfTexel.y,
		1, 1, 0, 1, 1 - halfTexel.x, 1 - halfTexel.y,
		-1, 1, 0, 1, halfTexel.x, 1 - halfTexel.y,

		-1, -1, 0, 1, halfTexel.x, halfTexel.y,
		1, -1, 0, 1, 1 - halfTexel.x, halfTexel.y,
		1, 1, 0, 1, 1 - halfTexel.x, 1 - halfTexel.y
	};

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 6, vertexData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, ((char*)0) + 16);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

OBJLoader::~OBJLoader() {
}

void OBJLoader::Draw(Camera camera) {

	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glViewport(0, 0, 1280, 720);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.SetMat4("projectionViewWorldMatrix", camera.GetProjectionView());
	shader.SetVec3("lightDirection", vec3(sin(glfwGetTime()), cos(glfwGetTime()), 0));
	shader.SetVec3("lightColor", (vec3)Colors::Red);
	shader.SetVec3("cameraPos", camera.GetPosition());
	shader.SetFloat("specPow", 128.0f);
	shader.SetVec4("offsetPosition", vec4(0, 5, 0, 0));
	
	for(auto& gl : m_glInfo) { 
		glBindVertexArray(gl.m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, gl.m_faceCount * 3);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 1280, 720);
	glClear(GL_DEPTH_BUFFER_BIT);

	postShader.UseProgram();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_fboTexture);
	postShader.SetInt("target", 0);

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glViewport(0, 0, 1280, 720);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//
	//shader.SetMat4("projectionViewWorldMatrix", camera.GetProjectionView());
	//shader.SetVec3("lightDirection", vec3(sin(glfwGetTime()), cos(glfwGetTime()), 0));
	//shader.SetVec3("lightColor", (vec3)Colors::Red);
	//shader.SetVec3("cameraPos", camera.GetPosition());
	//shader.SetFloat("specPow", 128.0f);
	//shader.SetVec4("offsetPosition", vec4(0, 5, 0, 0));
	//
	//for(auto& gl : m_glInfo) { 
	//	glBindVertexArray(gl.m_VAO);
	//	glDrawArrays(GL_TRIANGLES, 0, gl.m_faceCount * 3);
	//}
}

void OBJLoader::LoadObject(const char* path) {
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materals;
	std::string error;

	bool success = tinyobj::LoadObj(&attribs, &shapes, &materals, &error, path);

	if(success == true) {
		m_glInfo.resize(shapes.size());

		// grab each shape 
		int shapeIndex = 0;
		for(auto& shape : shapes) {
			// setup OpenGL data 
			glGenVertexArrays(1, &m_glInfo[shapeIndex].m_VAO);
			glGenBuffers(1, &m_glInfo[shapeIndex].m_VBO);
			glBindVertexArray(m_glInfo[shapeIndex].m_VAO);
			m_glInfo[shapeIndex].m_faceCount = shape.mesh.num_face_vertices.size();
			// collect triangle vertices 
			std::vector<OBJVertex> vertices;
			int index = 0;
			for(auto face : shape.mesh.num_face_vertices) {
				for(int i = 0; i < 3; ++i) {
					tinyobj::index_t idx = shape.mesh.indices[index + i];

					OBJVertex v = { 0 };

					// positions
					v.x = attribs.vertices[3 * idx.vertex_index + 0];
					v.y = attribs.vertices[3 * idx.vertex_index + 1];
					v.z = attribs.vertices[3 * idx.vertex_index + 2];

					// normals 
					if(attribs.normals.size() > 0) {
						v.nx = attribs.normals[3 * idx.normal_index + 0];
						v.ny = attribs.normals[3 * idx.normal_index + 1];
						v.nz = attribs.normals[3 * idx.normal_index + 2];
					}
					// texture coordinates 
					if(attribs.texcoords.size() > 0) {
						v.u = attribs.texcoords[2 * idx.texcoord_index + 0];
						v.v = attribs.texcoords[2 * idx.texcoord_index + 1];
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
}
