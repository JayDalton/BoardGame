#include "rectangle.hpp"

#include <GL/glew.h>

//############################################################################
/** 
((V, N, C, T), (V, N, C, T), ...)
((vx,vy,vz, nx,ny,nz, cr,cg,cb, tx,ty), (...), ...)
*/
//############################################################################  
Rectangle::Rectangle(ogl::Size size, ogl::Color color)
   : ogl::Shape("", "", color), m_size(size)
{
  //Geometry::buffer_len = 4 * struct_len;
  //Geometry::buffer = new float[buffer_len];
  //for (unsigned int i = 0; i < 4; ++i) {
  //  buffer[struct_len * i +  0] = VERTICES[i][ 0] * u;
  //  buffer[struct_len * i +  1] = VERTICES[i][ 1] * v;
  //  buffer[struct_len * i +  2] = VERTICES[i][ 2];
  //  buffer[struct_len * i +  3] = VERTICES[i][ 3];
  //  buffer[struct_len * i +  4] = VERTICES[i][ 4];
  //  buffer[struct_len * i +  5] = VERTICES[i][ 5];
  //  buffer[struct_len * i +  6] = r;
  //  buffer[struct_len * i +  7] = g;
  //  buffer[struct_len * i +  8] = b;
  //  buffer[struct_len * i +  9] = VERTICES[i][ 9];
  //  buffer[struct_len * i + 10] = VERTICES[i][10];
  //}

  //indice_len = 6;
  //indices = new GLuint[indice_len];
  //for (unsigned int i = 0; i < indice_len; i++) {
  //  indices[i] = INDICES[i];
  //}
}

//############################################################################
/** 
((V, N, C, T), (V, N, C, T), ...)
((vx,vy,vz, nx,ny,nz, cr,cg,cb, tx,ty), (...), ...)
*/
//############################################################################  
std::vector<glm::vec3> Rectangle::vertices() const
{
  std::vector<glm::vec3> result;
  //result.push_back(glm::vec3(buffer[ 0], buffer[ 1], buffer[ 2]));
  //result.push_back(glm::vec3(buffer[11], buffer[12], buffer[13]));
  //result.push_back(glm::vec3(buffer[22], buffer[23], buffer[24]));
  //result.push_back(glm::vec3(buffer[33], buffer[34], buffer[35]));
  return result;
}

glm::vec3 Rectangle::getBase() const
{
   return{};// glm::vec3(glm::vec3(buffer[0], buffer[1], buffer[2]));
}

GLuint Rectangle::getWidth() const
{
  //glm::vec3 E1 (glm::vec3(buffer[ 0], buffer[ 1], buffer[ 2]));
  //glm::vec3 E2 (glm::vec3(buffer[11], buffer[12], buffer[13]));

  //return glm::distance(E1, E2);
   return {};
}

GLuint Rectangle::getHeight() const
{
  //glm::vec3 E1 (glm::vec3(buffer[ 0], buffer[ 1], buffer[ 2]));
  //glm::vec3 E3 (glm::vec3(buffer[33], buffer[34], buffer[35]));

  //return glm::distance(E1, E3);
   return {};
}

bool Rectangle::intersect(glm::vec3 P1, glm::vec3 P2, glm::vec3 &PI) const
{
  bool result = false;

  //glm::vec3 E1 (glm::vec3(buffer[ 0], buffer[ 1], buffer[ 2]));
  //glm::vec3 E2 (glm::vec3(buffer[11], buffer[12], buffer[13]));
  //glm::vec3 E3 (glm::vec3(buffer[33], buffer[34], buffer[35]));

  //glm::vec3 tuv =
  //  glm::inverse(
  //    glm::mat3(
  //      glm::vec3(P1.x - P2.x, P1.y - P2.y, P1.z - P2.z),
  //      glm::vec3(E2.x - E1.x, E2.y - E1.y, E2.z - E1.z),
  //      glm::vec3(E3.x - E1.x, E3.y - E1.y, E3.z - E1.z)
  //    )
  //  ) *
  //  glm::vec3(P1.x - E1.x, P1.y - E1.y, P1.z - E1.z)
  //;

  //float t = tuv.x, u = tuv.y, v = tuv.z;

  //// intersection with the plane
  //if (0-1e-6 <= t  && t <= 1+1e-6) {
  //  // intersection with the triangle
  //  if (
  //    0-1e-6 <= u && u <= 1+1e-6 &&
  //    0-1e-6 <= v && v <= 1+1e-6
  //    //&& (u + v) <= 1+1e-6 // nur Dreieck
  //    ) {
  //      result = true;
  //      PI.x = t;
  //      PI.y = u;
  //      PI.z = v;
  //  }
  //}

  return result;
}

void Rectangle::render() const
{
  //glEnableClientState(GL_VERTEX_ARRAY);
  //glEnableClientState(GL_NORMAL_ARRAY);
  //glEnableClientState(GL_COLOR_ARRAY);

  //glVertexPointer(3, GL_FLOAT, StructSize(), getBuffer());
  //glNormalPointer(GL_FLOAT, StructSize(), getBuffer(3));
  //glColorPointer(3, GL_FLOAT, StructSize(), getBuffer(6));
  //glTexCoordPointer(2, GL_FLOAT, StructSize(), getBuffer(9));
  //glDrawElements(GL_TRIANGLES, IndiceLength(), GL_UNSIGNED_INT, getIndice());

  //glDisableClientState(GL_COLOR_ARRAY);
  //glDisableClientState(GL_NORMAL_ARRAY);
  //glDisableClientState(GL_VERTEX_ARRAY);
}

Square::Square(std::string_view vertex, std::string_view fragment, std::string_view texture) 
   : ogl::Shape(vertex, fragment, texture)
{
   glGenVertexArrays(1, &m_VAO);
   glGenBuffers(1, &m_VBO);
   glGenBuffers(1, &m_EBO);

   glBindVertexArray(m_VAO);

   glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices.data(), GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices.data(), GL_STATIC_DRAW);

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

void Square::render() const
{
   // bind textures on corresponding texture units
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, Texture::m_id);
   //glActiveTexture(GL_TEXTURE1);
   //glBindTexture(GL_TEXTURE_2D, Texture::m_id2);

   // render container
   Shader::useShader();
   glBindVertexArray(m_VAO);
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}
