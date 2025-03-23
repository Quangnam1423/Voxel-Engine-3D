#include "Shader.h"

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;


	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);

		std::stringstream fragmentStream, vertexStream;

		vertexStream << vertexShaderFile.rdbuf();
		fragmentStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();

	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE__SUCCESSFULLY_READ: " << e.what() << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");



	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");


	// create shaderProgram in gpu and bind vertexShader and fragmentShader into shaderProgram
	m_id = glCreateProgram();
	glAttachShader(m_id, vertex);
	glAttachShader(m_id, fragment);
	glLinkProgram(m_id);
	checkCompileErrors(m_id, "PROGRAM");


	//delete vertexShader and fragmentShader in GPU's memory after bind successfully
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
}

void Shader::setBool(const std::string& name, bool value)
{
}

void Shader::setInt(const std::string& name, int value)
{
}

void Shader::setFloat(const std::string& name, float value)
{
}

void Shader::setVec2(const std::string& name, const glm::vec2& value)
{
}

void Shader::setVec2(const std::string& name, float x, float y)
{
}

void Shader::setVec3(const std::string& name, const glm::vec3& value)
{
}

void Shader::setVec3(const std::string& name, float x, float y, float z)
{
}

void Shader::setVec4(const std::string& name, const glm::vec4& value)
{
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w)
{
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat)
{
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat)
{
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat)
{
}

void Shader::use()
{
	glUseProgram(m_id);
}

GLuint Shader::getId()
{
    return GLuint();
}

void Shader::checkCompileErrors(GLuint shader, std::string type)
{
}
