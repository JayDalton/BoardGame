#include "rectangle.hpp"

const GLuint ogl::Rectangle::INDICES[] = {0, 1, 3, 1, 2, 3};

const GLfloat ogl::Rectangle::VERTICES[][11] = {
  0,0,0,  0,0,1,  1,1,1,  0,0,
  1,0,0,  0,0,1,  1,1,1,  1,0,
  1,1,0,  0,0,1,  1,1,1,  1,1,
  0,1,0,  0,0,1,  1,1,1,  0,1
};

//############################################################################
/** 
((V, N, C, T), (V, N, C, T), ...)
((vx,vy,vz, nx,ny,nz, cr,cg,cb, tx,ty), (...), ...)
*/
//############################################################################  
ogl::Rectangle::Rectangle(GLfloat u, GLfloat v, GLfloat r, GLfloat g, GLfloat b)
  : Shape()
{
  Geometry::buffer_len = 4 * struct_len;
  Geometry::buffer = new GLfloat[buffer_len];
  for (unsigned int i = 0; i < 4; ++i) {
    buffer[struct_len * i +  0] = VERTICES[i][ 0] * u;
    buffer[struct_len * i +  1] = VERTICES[i][ 1] * v;
    buffer[struct_len * i +  2] = VERTICES[i][ 2];
    buffer[struct_len * i +  3] = VERTICES[i][ 3];
    buffer[struct_len * i +  4] = VERTICES[i][ 4];
    buffer[struct_len * i +  5] = VERTICES[i][ 5];
    buffer[struct_len * i +  6] = r;
    buffer[struct_len * i +  7] = g;
    buffer[struct_len * i +  8] = b;
    buffer[struct_len * i +  9] = VERTICES[i][ 9];
    buffer[struct_len * i + 10] = VERTICES[i][10];
  }

  indice_len = 6;
  indices = new GLuint[indice_len];
  for (unsigned int i = 0; i < indice_len; i++) {
    indices[i] = INDICES[i];
  }
}

ogl::Rectangle::~Rectangle()
{
}

ogl::Rectangle::Rectangle(const Rectangle& original)
  : Shape(original)
{
}

ogl::Rectangle& ogl::Rectangle::operator=(const Rectangle& original)
{
  if(this != &original) {
    Shape::operator=(original);
  }
  return *this;
}

//############################################################################
/** 
((V, N, C, T), (V, N, C, T), ...)
((vx,vy,vz, nx,ny,nz, cr,cg,cb, tx,ty), (...), ...)
*/
//############################################################################  
std::vector<glm::vec3> ogl::Rectangle::vertices() const
{
  std::vector<glm::vec3> result;
  result.push_back(glm::vec3(buffer[ 0], buffer[ 1], buffer[ 2]));
  result.push_back(glm::vec3(buffer[11], buffer[12], buffer[13]));
  result.push_back(glm::vec3(buffer[22], buffer[23], buffer[24]));
  result.push_back(glm::vec3(buffer[33], buffer[34], buffer[35]));
  return result;
}

glm::vec3 ogl::Rectangle::getBase() const
{
  return glm::vec3(glm::vec3(buffer[ 0], buffer[ 1], buffer[ 2]));
}

GLuint ogl::Rectangle::getWidth() const
{
  glm::vec3 E1 (glm::vec3(buffer[ 0], buffer[ 1], buffer[ 2]));
  glm::vec3 E2 (glm::vec3(buffer[11], buffer[12], buffer[13]));

  return glm::distance(E1, E2);
}

GLuint ogl::Rectangle::getHeight() const
{
  glm::vec3 E1 (glm::vec3(buffer[ 0], buffer[ 1], buffer[ 2]));
  glm::vec3 E3 (glm::vec3(buffer[33], buffer[34], buffer[35]));

  return glm::distance(E1, E3);
}

bool ogl::Rectangle::intersect(glm::vec3 P1, glm::vec3 P2, glm::vec3 &PI) const
{
  bool result = false;

  glm::vec3 E1 (glm::vec3(buffer[ 0], buffer[ 1], buffer[ 2]));
  glm::vec3 E2 (glm::vec3(buffer[11], buffer[12], buffer[13]));
  glm::vec3 E3 (glm::vec3(buffer[33], buffer[34], buffer[35]));

  glm::vec3 tuv =
    glm::inverse(
      glm::mat3(
        glm::vec3(P1.x - P2.x, P1.y - P2.y, P1.z - P2.z),
        glm::vec3(E2.x - E1.x, E2.y - E1.y, E2.z - E1.z),
        glm::vec3(E3.x - E1.x, E3.y - E1.y, E3.z - E1.z)
      )
    ) *
    glm::vec3(P1.x - E1.x, P1.y - E1.y, P1.z - E1.z)
  ;

  float t = tuv.x, u = tuv.y, v = tuv.z;

  // intersection with the plane
  if (0-1e-6 <= t  && t <= 1+1e-6) {
    // intersection with the triangle
    if (
      0-1e-6 <= u && u <= 1+1e-6 &&
      0-1e-6 <= v && v <= 1+1e-6
      //&& (u + v) <= 1+1e-6 // nur Dreieck
      ) {
        result = true;
        PI.x = t;
        PI.y = u;
        PI.z = v;
    }
  }

  return result;
}

void ogl::Rectangle::render() const
{
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(3, GL_FLOAT, StructSize(), getBuffer());
  glNormalPointer(GL_FLOAT, StructSize(), getBuffer(3));
  glColorPointer(3, GL_FLOAT, StructSize(), getBuffer(6));
  glTexCoordPointer(2, GL_FLOAT, StructSize(), getBuffer(9));
  glDrawElements(GL_TRIANGLES, IndiceLength(), GL_UNSIGNED_INT, getIndice());

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}
