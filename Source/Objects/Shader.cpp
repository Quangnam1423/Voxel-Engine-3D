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
	glDeleteProgram(m_id);
}

void Shader::setBool(const std::string& name, bool value)
{
	use();
	glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value)
{
	use();
	glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value)
{
	use();
	glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value)
{
	use();
	glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string& name, float x, float y)
{
	use();
	glUniform2f(glGetUniformLocation(m_id, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value)
{
	use();
	glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z)
{
	use();
	glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value)
{
	use();
	glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w)
{
	use();
	glUniform4f(glGetUniformLocation(m_id, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat)
{
	use();
	glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat)
{
	use();
	glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat)
{
	use();
	glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
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
	int sucess;;
	char inforLog[512];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &sucess);
		if (!sucess)
		{
			glGetShaderInfoLog(shader, 512, NULL, inforLog);
			std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << inforLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &sucess);
		if (!sucess)
		{
			glGetProgramInfoLog(shader, 512, NULL, inforLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << inforLog << std::endl;
		}
	}
}
