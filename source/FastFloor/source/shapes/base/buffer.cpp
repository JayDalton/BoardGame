#include "buffer.hpp"

#include <GL/glew.h>

#include <numeric>

void ogl::Buffer::useBuffer()
{
   glBindVertexArray(m_VAO);
   glDrawElements(GL_TRIANGLES, m_indexSize, GL_UNSIGNED_INT, 0);
   //glDrawElements(GL_TRIANGLE_STRIP, m_indexSize, GL_UNSIGNED_INT, 0);
   //glDrawElements(GL_TRIANGLE_FAN, m_indexSize, GL_UNSIGNED_INT, 0);
   //glDrawElements(GL_LINE_STRIP, m_indexSize, GL_UNSIGNED_INT, 0);
}

void ogl::Buffer::freeBuffer()
{
   glDeleteVertexArrays(1, &m_VAO);
   glDeleteBuffers(1, &m_VBO);
   glDeleteBuffers(1, &m_EBO);
   m_VAO = m_VBO = m_EBO = 0;
}

void ogl::Buffer::bindBuffer(
   const std::vector<Element>& elementList, 
   const std::vector<IndexType>& indexList)
{
   std::vector<ElemItemType> vertexBuffer;
   vertexBuffer.reserve(elementList.size() * sizeof(ElemItemType));
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
   glBufferData(GL_ARRAY_BUFFER, getVerticesByteSize(), vertexBuffer.data(), GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, getIndicesByteSize(), indexList.data(), GL_STATIC_DRAW);

   // position attribute
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)0);
   glEnableVertexAttribArray(0);

   // color attribute
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(3 * sizeof(float)));
   glEnableVertexAttribArray(1);

   // texture coord attribute
   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(6 * sizeof(float)));
   glEnableVertexAttribArray(2);

   //std::cout << std::format("\nBufferId: {}, VBO: {}, EBO: {}, IndexSize: {}, VertexSize: {}"
   //   , m_VAO, m_VBO, m_EBO, m_indexSize, m_vertexSize);
}
