#include "shape.hpp"

#include <GL/glew.h>

ogl::Shape::~Shape()
{
   glDeleteVertexArrays(1, &m_VAO);
   glDeleteBuffers(1, &m_VBO);
   glDeleteBuffers(1, &m_EBO);
}

//void ogl::Shape::render(Buffer& buffer, Shader& shader)
//{
//   //Texture::useTexture(); ???
//   //glActiveTexture(GL_TEXTURE0);
//   //glBindTexture(GL_TEXTURE_2D, Texture::id());
//   //glActiveTexture(GL_TEXTURE1);
//   //glBindTexture(GL_TEXTURE_2D, Texture::m_id2);
//
//   // render container
//   //shader.useShader();
//   //Shader::useShader();
//   //Shader::setMat4("model", pos);
//
//   //Buffer::render(); ???
//   //buffer.render();
//   //glBindVertexArray(m_VAO);
//   ////glDrawElements(GL_LINE_STRIP, m_indices.size(), GL_UNSIGNED_INT, 0);
//   //glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
//}

void ogl::Shape::bindBuffer(std::vector<unsigned>&& indices)
{
   //m_indices = indices;

   //glGenVertexArrays(1, &m_VAO);
   //glGenBuffers(1, &m_VBO);
   //glGenBuffers(1, &m_EBO);

   //glBindVertexArray(m_VAO);

   //glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
   //glBufferData(GL_ARRAY_BUFFER, getVerticesSize(), m_vertices.data(), GL_STATIC_DRAW);

   //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
   //glBufferData(GL_ELEMENT_ARRAY_BUFFER, getIndicesSize(), m_indices.data(), GL_STATIC_DRAW);

   //// position attribute
   //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)0);
   //glEnableVertexAttribArray(0);

   //// color attribute
   //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(3 * sizeof(float)));
   //glEnableVertexAttribArray(1);

   //// texture coord attribute
   //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(6 * sizeof(float)));
   //glEnableVertexAttribArray(2);

   ////m_indices.clear();
   //m_vertices.clear();
}

void ogl::Shape::bindBuffer(
   const std::vector<Element>& vertices, 
   const std::vector<IndexType>& indices)
{
   m_indexSize = indices.size();

   //glGenVertexArrays(1, &m_VAO);
   //glGenBuffers(1, &m_VBO);
   //glGenBuffers(1, &m_EBO);

   //glBindVertexArray(m_VAO);

   //glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
   //glBufferData(GL_ARRAY_BUFFER, sizeof(VertexType) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

   //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
   //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexType) * indices.size(), indices.data(), GL_STATIC_DRAW);

   //// position attribute
   //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)0);
   //glEnableVertexAttribArray(0);

   //// color attribute
   //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(3 * sizeof(float)));
   //glEnableVertexAttribArray(1);

   //// texture coord attribute
   //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(6 * sizeof(float)));
   //glEnableVertexAttribArray(2);
}

ogl::Buffer::~Buffer()
{
   glDeleteVertexArrays(1, &m_VAO);
   glDeleteBuffers(1, &m_VBO);
   glDeleteBuffers(1, &m_EBO);
}

void ogl::Buffer::bindBuffer(const std::vector<Element>& elementList, const std::vector<IndexType>& indexList)
{
   std::vector<VertexType> vertexBuffer;
   vertexBuffer.reserve(elementList.size() * sizeof(VertexType));
   for (auto&& element : elementList)
   {
      std::copy(element.cbegin(), element.cend(), std::back_inserter(vertexBuffer));
   }

   m_indexSize = indexList.size();
   m_vertexSize = vertexBuffer.size();

   glGenVertexArrays(1, &m_VAO);
   glGenBuffers(1, &m_VBO);
   glGenBuffers(1, &m_EBO);

   glBindVertexArray(m_VAO);

   glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
   glBufferData(GL_ARRAY_BUFFER, getVerticesSize(), vertexBuffer.data(), GL_STATIC_DRAW);
   //glBufferData(GL_ARRAY_BUFFER, sizeof(VertexType) * vertexBuffer.size(), vertexBuffer.data(), GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, getIndicesSize(), indexList.data(), GL_STATIC_DRAW);
   //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexType) * indexList.size(), indexList.data(), GL_STATIC_DRAW);

   // position attribute
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)0);
   glEnableVertexAttribArray(0);

   // color attribute
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(3 * sizeof(float)));
   glEnableVertexAttribArray(1);

   // texture coord attribute
   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(6 * sizeof(float)));
   glEnableVertexAttribArray(2);
}

void ogl::Buffer::render()
{
   glBindVertexArray(m_VAO);
   glDrawElements(GL_TRIANGLES, m_indexSize, GL_UNSIGNED_INT, 0);
   glDrawElements(GL_LINE_STRIP, m_indexSize, GL_UNSIGNED_INT, 0);
}
