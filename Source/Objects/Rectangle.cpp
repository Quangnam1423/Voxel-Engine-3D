#include "Rectangle.h"
#include <glad/glad.h>  
#include <GLFW/glfw3.h>  
#include <stb_image.h>  
#include "Shader.h"  
#include <iostream>  

Rectangle::Rectangle()  
{  
    m_shader = nullptr;
    m_textureID = 0;
    m_vertices = {  
       // positions          // colors           // texture coords  
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right  
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right  
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left  
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left   
    };  
    m_indices = {  
        0, 1, 3, // first triangle  
        1, 2, 3  // second triangle  
    };  

   glGenVertexArrays(1, &m_vao);  
   glGenBuffers(1, &m_vbo);  
   glGenBuffers(1, &m_ebo);  

   glBindVertexArray(m_vao);  

   glBindBuffer(GL_ARRAY_BUFFER, m_vbo);  
   glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);  
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

   // position attribute  
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);  
   glEnableVertexAttribArray(0);  
   // color attribute  
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));  
   glEnableVertexAttribArray(1);  
   // texture coord attribute  
   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));  
   glEnableVertexAttribArray(2);  
}  

Rectangle::~Rectangle()  
{  
glDeleteVertexArrays(1, &m_vao);  
glDeleteBuffers(1, &m_vbo);  
glDeleteBuffers(1, &m_ebo);  
}  

void Rectangle::draw()  
{  
    m_shader->use();  
	m_shader->setInt("texture1", 0);
    glBindVertexArray(m_vao);  
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);  
    glBindVertexArray(0);  
}  

void Rectangle::cleanup()  
{  
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);

}
