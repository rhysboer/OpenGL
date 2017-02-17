#include "Application.h"

Application::Application(int width, int height, const char* name) : BaseApplication::BaseApplication(width, height, name) {
}

Application::~Application() {
}

// Start Up
const bool Application::Startup() {
	if(window == nullptr) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	if(ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		glfwDestroyWindow(window);
		glfwTerminate();
		return false;
	}

	// Camera
	camera.SetLookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	camera.SetPerspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.0f);

	// Background color
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glEnable(GL_DEPTH_TEST);


	/////
	Start();
	GenerateGrid(10,10);

	m_sunMat = glm::translate(m_sunMat, vec3(0));
	m_earthLocal = glm::translate(m_earthLocal, vec3(5, 0, 0));
	m_moonLocal = glm::translate(m_moonLocal, vec3(2, 0, 0));

	// Delta Time
	currentTime = (float)glfwGetTime();

	Gizmos::create();
	return true;
}

// Update
const bool Application::Update() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Gizmos::clear();
	Gizmos::addTransform(glm::mat4(1));

	currentTime = (float)glfwGetTime();

	if(glfwWindowShouldClose(window) == (int)true || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		return false;
	}

	// Rotate Planets
	m_sunMat = glm::rotate(m_sunMat, -0.01f, vec3(0, 1, 0));
	m_earthLocal = glm::rotate(m_earthLocal, -0.01f, vec3(0, 1, 0));
	m_moonLocal = glm::rotate(m_moonLocal, 1.0f, vec3(0, 1, 0));

		
	m_earthMat = m_sunMat * m_earthLocal;
	m_moonMat = m_earthMat * m_moonLocal;

	Gizmos::addSphere(vec3(m_sunMat[3]), 1.f, 25, 25, Colors::red, &m_sunMat);
	Gizmos::addSphere(vec3(m_earthMat[3]), 0.5f, 20, 20, Colors::green, &m_earthMat);
	Gizmos::addSphere(vec3(m_moonMat[3]), 0.2f, 10, 10, Colors::purple, &m_moonMat);

	// Grid
	for(int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? Colors::white : Colors::black);
		Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? Colors::white : Colors::black);
	}


	// Camera Movement
	Input();


	// Delta Time
	deltaTime = currentTime - previousTime;
	previousTime = currentTime;

	return true;
}

void Application::Draw() {
	Gizmos::draw(camera.GetProjectionView());

	/////////////////
	glUseProgram(m_programID);
	unsigned int projectionViewUniform = glGetUniformLocation(m_programID, "projectionViewWorldMatrix");
	glUniformMatrix4fv(projectionViewUniform, 1, false, glm::value_ptr(camera.GetProjectionView()));
	glBindVertexArray(m_VAO);
	unsigned int indexCount = (m_rows - 1) * (m_cols - 1) * 6;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	/////////////////

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Application::Shutdown() {
	Gizmos::destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Application::GenerateGrid(unsigned int rows, unsigned int cols) {

	m_rows = rows;
	m_cols = cols;

	// defining index count based off quad count (2 triangle per quad)
	unsigned int* auiIndices = new unsigned int[(rows - 1) * (cols - 1) * 6]; // DELETE
	unsigned int index = 0;

	Vertex* aoVertices = new Vertex[rows * cols];
	for(unsigned int r = 0; r < rows; ++r) {
		for(unsigned int c = 0; c < cols; ++c) {

			// triangle 1
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);

			// triangle 2
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);
			auiIndices[index++] = r * cols + (c + 1);

			aoVertices[r*cols + c].position = vec4((float)c, 0, (float)r, 1);

			vec3 colour = vec3(sinf((c / (float)(cols - 1)) * (r / (float)(rows - 1))));
			aoVertices[r*cols + c].colour = vec4(colour, 1);
		}
	}

	// create and bind buffers to a vertex array object
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// fill index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (rows - 1) * (cols - 1) * 6 * sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (rows * cols) * sizeof(Vertex), aoVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete[] aoVertices;
}

void Application::Start() {

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

	int success = GL_FALSE;
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertexShader);

	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
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
	glDeleteShader(vertexShader);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void Application::Input() {
	// FORWARD
	if(glfwGetKey(window, GLFW_KEY_W)) {
		camera.Move(vec3(0, 0, -3) * deltaTime);
	}
	
	// BACKWARDS
	if(glfwGetKey(window, GLFW_KEY_S)) {
		camera.Move(vec3(0, 0, 3) * deltaTime);
	}
	
	// LEFT
	if(glfwGetKey(window, GLFW_KEY_A)) {
		camera.Move(vec3(-3, 0, 0) * deltaTime);
	}
	
	// RIGHT
	if(glfwGetKey(window, GLFW_KEY_D)) {
		camera.Move(vec3(3, 0, 0) * deltaTime);
	}
	
	// UP
	if(glfwGetKey(window, GLFW_KEY_E)) {
		camera.Move(vec3(0, 3, 0) * deltaTime);
	}
	
	// DOWN
	if(glfwGetKey(window, GLFW_KEY_Q)) {
		camera.Move(vec3(0, -3, 0) * deltaTime);
	}
}
