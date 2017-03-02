#include "ShaderLoader.h"

ShaderLoader::ShaderLoader() {
}

ShaderLoader::~ShaderLoader() {
	glDeleteProgram(m_programID);
	m_programID = 0;
}

void ShaderLoader::UseProgram() {
	glUseProgram(m_programID);
}

void ShaderLoader::CreateShaderProgram(const char * vertexShaderPath, const char * fragmentShaderPath) {
	if(m_programID != 0) {
		glDeleteProgram(m_programID);
		m_programID = 0;
	}

	unsigned int vertexShader = CreateShader(vertexShaderPath, GL_VERTEX_SHADER);
	unsigned int fragmentShader = CreateShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
	
	if(vertexShader == 0 || fragmentShader == 0) {
		glDeleteProgram(m_programID);
		m_programID = 0;
		return;
	}

	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertexShader);
	glAttachShader(m_programID, fragmentShader);
	glLinkProgram(m_programID);

	int success = GL_FALSE;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);

	if(success == GL_FALSE) {
		int infoLogLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* infoLog = new char[infoLogLength];

		glGetProgramInfoLog(m_programID, infoLogLength, 0, infoLog);
		std::cout << "Failed to link shader program: \n" << infoLog << '\n';

		delete[] infoLog;

		glDeleteProgram(m_programID);
		m_programID = 0;
		return;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderLoader::SetFloat(const char * name, const float& value) {
	if(m_programID != 0) {
		glUseProgram(m_programID);
		glUniform1f(glGetUniformLocation(m_programID, name), value);
	}
}

void ShaderLoader::SetVec2(const char * name, const vec2& value) {
	if(m_programID != 0) {
		glUseProgram(m_programID);
		glUniform2f(glGetUniformLocation(m_programID, name), value.x, value.y);
	}
}

void ShaderLoader::SetVec3(const char * name, const vec3& value) {
	if(m_programID != 0) {
		glUseProgram(m_programID);
		glUniform3f(glGetUniformLocation(m_programID, name), value.x, value.y, value.z);
	}
}

void ShaderLoader::SetVec4(const char * name, const vec4& value) {
	if(m_programID != 0) {
		glUseProgram(m_programID);
		glUniform4f(glGetUniformLocation(m_programID, name), value.x, value.y, value.z, value.w);
	}
}

void ShaderLoader::SetMat4(const char * name, const mat4& value) {
	if(m_programID != 0) {
		glUseProgram(m_programID);
		glUniformMatrix4fv(glGetUniformLocation(m_programID, name), 1, false, glm::value_ptr(value));
	}
}

unsigned int ShaderLoader::CreateShader(const char * path, GLenum shaderType) {
	if(path == nullptr)
		return 0;

	ostringstream source;
	ifstream shaderFile;
	shaderFile.open(path, ios::out);

	if(shaderFile.is_open() && shaderFile.fail() == false) {
		source << shaderFile.rdbuf();

		std::string shaderString = source.str();
		const char* shaderSource = shaderString.c_str();
		shaderFile.close();

		unsigned int shader = glCreateShader(shaderType);

		glShaderSource(shader, 1, (const char**)&shaderSource, 0);
		glCompileShader(shader);

		return shader;
	}

	return 0;
}
