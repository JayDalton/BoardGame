#include "shape.hpp"

#include <GL/glew.h>

ogl::Shape::~Shape()
{
   //glDeleteVertexArrays(1, &m_VAO);
   //glDeleteBuffers(1, &m_VBO);
   //glDeleteBuffers(1, &m_EBO);
}

void ogl::Shape::bindBuffer()
{
   //glGenVertexArrays(1, &m_VAO);
   //glGenBuffers(1, &m_VBO);
   //glGenBuffers(1, &m_EBO);

   //glBindVertexArray(m_VAO);

   //glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
   //glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices.data(), GL_STATIC_DRAW);

   //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
   //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices.data(), GL_STATIC_DRAW);

   //// position attribute
   //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
   //glEnableVertexAttribArray(0);
   //// color attribute
   //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
   //glEnableVertexAttribArray(1);
   //// texture coord attribute
   //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
   //glEnableVertexAttribArray(2);
}
