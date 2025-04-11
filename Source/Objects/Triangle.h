#pragma once
#include <vector>

class Shader;

class Triangle {
public:
	Triangle();
	~Triangle();
	void init();
	void draw();
	void cleanup();
	void setShader(Shader* shader);
private:
	Shader* m_shader;
	unsigned int m_VAO, m_VBO, m_EBO;
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
};