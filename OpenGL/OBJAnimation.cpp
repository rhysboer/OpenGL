#include "OBJAnimation.h"

OBJAnimation::OBJAnimation() {
	shader.CreateShaderProgram("../shaders/Morphing.vert", "../shaders/Default.frag");
}

OBJAnimation::~OBJAnimation() {
}

bool OBJAnimation::LoadOBJs(const char * path1, const char * path2) {
	std::string error;

	tinyobj::attrib_t attribs[2];
	std::vector<tinyobj::shape_t> shapes[2];
	std::vector<tinyobj::material_t> materials[2];

	// Load Objects
	tinyobj::LoadObj(&attribs[0], &shapes[0], &materials[0], &error, path1);
	tinyobj::LoadObj(&attribs[1], &shapes[1], &materials[1], &error, path2);

	for(int i = 0; i < shapes[0].size(); ++i) {

		GLInfo gl;

		gl.m_VBO1 = CreateVertexBuffer(attribs[0], shapes[0][i]);
		gl.m_VBO2 = CreateVertexBuffer(attribs[0], shapes[0][i]);

		gl.m_faceCount = shapes[0][i].mesh.num_face_vertices.size();

		glGenVertexArrays(1, &gl.m_VAO);
		glBindVertexArray(gl.m_VAO);

		// Bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, gl.m_VBO1);

		// Position
		glEnableVertexAttribArray(0); 
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OBVertex), 0);

		// Normal
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(OBVertex), (void*)12);

		// Texture Data
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(OBVertex), (void*)24);

		
		// Second VBO
		glBindBuffer(GL_ARRAY_BUFFER, gl.m_VBO2);

		// Position 2
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(OBVertex), 0);

		// Normal 2
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(OBVertex), (void*)12);

		glBindVertexArray(0);

		m_meshes.push_back(gl);
	}

	return false;
}

void OBJAnimation::Draw(Camera camera) {
	shader.UseProgram();

	shader.SetMat4("projectionViewModel", camera.GetProjectionView());
	shader.SetFloat("keyTime", cosf(glfwGetTime() * 3) * 0.5f + 0.5f);

	for(auto& gl : m_meshes) {
		glBindVertexArray(gl.m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, gl.m_faceCount * 3);
	}
}

// Generate Vertex Buffer
unsigned int OBJAnimation::CreateVertexBuffer(const tinyobj::attrib_t & attribs, const tinyobj::shape_t & shape) {

	std::vector<OBVertex> vertices;

	int index = 0;
	for(auto face : shape.mesh.num_face_vertices) {
		for(int i = 0; i < 3; ++i) {
			tinyobj::index_t idx = shape.mesh.indices[index + i];

			OBVertex v = { 0 };

			// Position
			v.x = attribs.vertices[3 * idx.vertex_index + 0];
			v.y = attribs.vertices[3 * idx.vertex_index + 1];
			v.z = attribs.vertices[3 * idx.vertex_index + 2];

			// Normals
			if(attribs.normals.size() > 0) {
				v.nx = attribs.normals[3 * idx.normal_index + 0];
				v.ny = attribs.normals[3 * idx.normal_index + 1];
				v.nz = attribs.normals[3 * idx.normal_index + 3];
			}

			// Texture Coords
			if(attribs.texcoords.size() > 0) {
				v.u = attribs.texcoords[2 * idx.texcoord_index + 0];
				v.v = attribs.texcoords[2 * idx.texcoord_index + 1];
			}

			vertices.push_back(v);
		}

		index += face;
	}

	// Bind vertex data
	unsigned int buffer = 0;

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(OBVertex), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 1);

	return buffer;
}