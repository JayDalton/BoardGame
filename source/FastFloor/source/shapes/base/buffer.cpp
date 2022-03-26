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
   std::vector<ItemType> vertexBuffer;
   vertexBuffer.reserve(elementList.size() * sizeof(ItemType));
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

   // normal attribute
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(3 * sizeof(ItemType)));
   glEnableVertexAttribArray(1);

   // color attribute
   glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(6 * sizeof(ItemType)));
   glEnableVertexAttribArray(2);

   // texture coord attribute
   glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(9 * sizeof(ItemType)));
   glEnableVertexAttribArray(3);

   //std::cout << std::format("\nBufferId: {}, VBO: {}, EBO: {}, IndexSize: {}, VertexSize: {}"
   //   , m_VAO, m_VBO, m_EBO, m_indexSize, m_vertexSize);
}
