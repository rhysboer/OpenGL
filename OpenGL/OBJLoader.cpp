#define TINYOBJLOADER_IMPLEMENTATION
#include "OBJLoader.h"

OBJLoader::OBJLoader() {
	shader.CreateShaderProgram("../shaders/PhongLight.vert", "../shaders/PhongLight.frag");
	// shader.CreateShaderProgram("../shaders/PhongLight.vert", "../shaders/PhongLight.frag");


	//shadow.CreateShaderProgram("../shaders/GensShadow.vert", "../shaders/GensShadow.frag");

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



	// OUTLINE CODE

	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	
	glGenTextures(1, &m_fboDepth);
	glBindTexture(GL_TEXTURE_2D, m_fboDepth);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, 1280, 720, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_fboDepth, 0);
	
	glDrawBuffer(GL_NONE);
	
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(status != GL_FRAMEBUFFER_COMPLETE) {
		printf("FRAMEBUFFER ERROR! you dun goofed\n");
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

OBJLoader::~OBJLoader() {
}

void OBJLoader::Draw(Camera camera) {

	//glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	//glViewport(0, 0, 1024, 1024);
	//glClear(GL_DEPTH_BUFFER_BIT);
	//
	//shadow.UseProgram();
	//
	//vec3 lightDir = glm::normalize(vec3(1, 1, 0)); //sin(glfwGetTime()) * 2, cos(glfwGetTime()) + 2.5f, 1)
	//mat4 lightProjection = glm::ortho<float>(-25, 25, -25, 25, -25, 25);
	//mat4 lightView = glm::lookAt(lightDir, vec3(0), vec3(0, 1, 0));
	//m_lightMatrix = lightProjection * lightView;
	//
	//mat4 lightMatrix = textureSpaceOffset * m_lightMatrix;
	//
	//shadow.SetMat4("lightMatrix", m_lightMatrix);
	//
	//// Draw Bunny
	//a_terrain.Draw(camera, shadow);
	//for(auto& gl : m_glInfo) {
	//	glBindVertexArray(gl.m_VAO);
	//	glDrawArrays(GL_TRIANGLES, 0, gl.m_faceCount * 3);
	//}
	//
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glViewport(0, 0, 1280, 720);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//
	//shader.UseProgram();
	//shader.SetMat4("projectionViewWorldMatrix", camera.GetProjectionView());
	//shader.SetVec3("lightDir", lightDir);
	//shader.SetMat4("lightMatrix", lightMatrix);
	//shader.SetInt("shadowMap", 0);



	
	shader.SetMat4("projectionViewWorldMatrix", camera.GetProjectionView());
	shader.SetVec3("lightDirection", vec3(sin(glfwGetTime()), cos(glfwGetTime()), 0));
	shader.SetVec3("lightColor", (vec3)Colors::Red);
	shader.SetVec3("cameraPos", camera.GetPosition());
	shader.SetFloat("specPow", 128.0f);
	shader.SetVec4("offsetPosition", vec4(0, 5, 0, 0));
	

	//shader.SetMat4("projectionViewWorldMatrix", camera.GetProjectionView());
	//
	//shader.UseProgram();
	//
	///////////////////////////////
	//glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	//glViewport(0, 0, 1280, 720);
	//glClear(GL_DEPTH_BUFFER_BIT);
	//
	//for(auto& gl : m_glInfo) {
	//	glBindVertexArray(gl.m_VAO);
	//	glDrawArrays(GL_TRIANGLES, 0, gl.m_faceCount * 3);
	//}
	//
	///////////////////////////////
	//
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glViewport(0, 0, 1280, 720);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//
	//shader.SetInt("depthTexture", 0);
	//
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, m_fboDepth);





	// Normal Code

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, m_fboDepth);
	
	//a_terrain.Draw(camera, shader);
	
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
