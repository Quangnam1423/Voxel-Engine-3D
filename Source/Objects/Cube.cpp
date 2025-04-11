#include "Cube.h"
#include "Shader.h"
#include "stb_image.h"

Cube::Cube(const char* texturePath, const char* vertexShaderPath, const char* fragmentShaderPath)
{
	init(texturePath, vertexShaderPath, fragmentShaderPath);
}

Cube::~Cube()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
	delete m_shader;
}

void Cube::draw(const glm::mat4& view, const glm::mat4& projection, const glm::mat4& model)
{
	m_shader->use();
	m_shader->setMat4("view", view);
	m_shader->setMat4("projection", projection);
	m_shader->setMat4("model", model);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	m_shader->setInt("texture1", 0);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindVertexArray(0);
}

void Cube::setShader(Shader* shader)
{
	m_shader = shader;
}

void Cube::init(const char* texturePath, const char* vertexShaderPath, const char* fragmentShaderPath) 
{
	m_shader = new Shader(vertexShaderPath, fragmentShaderPath);
	std::vector<Vertex> m_vertices = {
		// front face
		// positions          // colors           // texture coords
		Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.5f , 0.75f), 1} , // bottom left
		Vertex{glm::vec3(0.5f, -0.5f, -0.5f),glm::vec2(0.75f , 0.75f) , 1},   // bottom right
		Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(0.75f , 0.99f),1} ,   // top right
		Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(0.75f , 0.99f),1} ,  // top right
		Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.5f , 0.99f),1} ,   // top left 
		Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.5f , 0.75f),1} ,  // bottom left

		//behind face
		// positions          // colors           // texture coords
		Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.5f , 0.75f), 1} ,  // bottom left
		Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.75f , 0.75f), 1} , // bottom right
		Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec2(0.75f , 0.99f), 1} , // top right
		Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec2(0.75f , 0.99f), 1} , // top right
		Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec2(0.5f , 0.99f), 1}  , // top left 
		Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.5f,  0.75f), 1} , // bottom left

		//right face
		// positions          // colors           // texture coords
		Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.5f , 0.75f), 1} ,   // bottom left
		Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.75f , 0.75f), 1 } ,   // bottom right
		Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec2(0.75f , 0.99f), 1 },   // top right
		Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec2(0.75f , 0.99f), 1},   // top right
		Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(0.5f , 0.99f),1} ,    // top left 
		Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.5f , 0.75f), 1} ,   // bottom left

		//left face
		// positions          // colors           // texture coords
		Vertex{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.5f , 0.75f), 1} ,   // bottom left
		Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.75f , 0.75f), 1} ,   // bottom right
		Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.75f , 0.99f), 1},   // top right
		Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.75f , 0.99f), 1} ,   // top right
		Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec2(0.5f , 0.99f), 1},    // top left 
		Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.5f , 0.75f), 1},   // bottom left

		//top face
		// positions          // colors           // texture coords
		Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.75f , 0.5f), 1},   // bottom left
		Vertex{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 0.5f), 1},   // bottom right
		Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec2(1.0f, 0.75f) ,1},   // top right
		Vertex{glm::vec3(0.5f , 0.5f ,0.5f) , glm::vec2(1.0f , 0.75f) , 1},   // top right
		Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec2(0.75f , 0.75f), 1} ,    // top left 
		Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.75f , 0.5f), 1},   // bottom left

		//bottom face
		// positions          // colors           // texture coords
		Vertex{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.25f , 0.75f),1} ,   // bottom left
		Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.5f , 0.75f),1} ,   // bottom right
		Vertex{glm::vec3(0.5f,  -0.5f, -0.5f), glm::vec2(0.5f , 1.0f), 1} ,   // top right
		Vertex{glm::vec3(0.5f,  -0.5f, -0.5f), glm::vec2(0.5f , 1.0f), 1} ,   // top right
		Vertex{glm::vec3(-0.5f,  -0.5f, -0.5f), glm::vec2(0.25f , 1.0f),1} ,    // top left 
		Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.25f , 0.75f), 1}   // bottom left
	};

	std::vector<GLuint> m_indices = {
		0 , 1 , 2 ,		3 , 4 , 5 , //front face
		6 , 7 , 8 ,		9 , 10 , 11 ,  //right face
		12, 13, 14,		15, 16, 17 ,  //bihind face
		18, 19, 20,		21, 22, 23 , //left face
		24, 25, 26,		27, 28, 29 ,//top face
		30, 31, 32,		33, 34, 35//bottom face
	};

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), &m_indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textCoords));
	glEnableVertexAttribArray(2);
	glVertexAttribIPointer(2, 1, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, id));
	glBindVertexArray(0);

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (data) {
		GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cerr << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}
