#include "cuboid.hpp"

#include <GL/glew.h>

const GLfloat ogl::Cuboid::VERTICES[][11] = {

  {-1, 1, 1,   0, 1, 0,   1, 1, 1,   0.000000f, 0.50f},   // unten links
  { 1, 1, 1,   0, 1, 0,   1, 1, 1,   0.333333f, 0.50f},   // unten rechts (top)
  { 1, 1,-1,   0, 1, 0,   1, 1, 1,   0.333333f, 1.00f},   // oben rechts
  {-1, 1,-1,   0, 1, 0,   1, 1, 1,   0.000000f, 1.00f},  // oben links

  {-1,-1, 1,   0, 0, 1,   1, 1, 1,   0.333333f, 0.50f},   // unten links
  { 1,-1, 1,   0, 0, 1,   1, 1, 1,   0.666666f, 0.50f},   // unten rechts
  { 1, 1, 1,   0, 0, 1,   1, 1, 1,   0.666666f, 1.00f},   // oben rechts (front)
  {-1, 1, 1,   0, 0, 1,   1, 1, 1,   0.333333f, 1.00f},  // oben links

  { 1,-1, 1,   1, 0, 0,   1, 1, 1,   0.666666f, 0.50f},   // unten links
  { 1,-1,-1,   1, 0, 0,   1, 1, 1,   1.000000f, 0.50f},   // unten rechts
  { 1, 1,-1,   1, 0, 0,   1, 1, 1,   1.000000f, 1.00f},   // oben rechts
  { 1, 1, 1,   1, 0, 0,   1, 1, 1,   0.666666f, 1.00f},  // oben links (right)

  { 1,-1,-1,   0, 0,-1,   1, 1, 1,   0.000000f, 0.00f},   // unten links (back)
  {-1,-1,-1,   0, 0,-1,   1, 1, 1,   0.333333f, 0.00f},   // unten rechts
  {-1, 1,-1,   0, 0,-1,   1, 1, 1,   0.333333f, 0.50f},   // oben rechts
  { 1, 1,-1,   0, 0,-1,   1, 1, 1,   0.000000f, 0.50f},  // oben links

  {-1,-1,-1,  -1, 0, 0,   1, 1, 1,   0.333333f, 0.00f},   // unten links
  {-1,-1, 1,  -1, 0, 0,   1, 1, 1,   0.666666f, 0.00f},   // unten rechts
  {-1, 1, 1,  -1, 0, 0,   1, 1, 1,   0.666666f, 0.50f},   // oben rechts (left)
  {-1, 1,-1,  -1, 0, 0,   1, 1, 1,   0.333333f, 0.50f},  // oben links

  {-1,-1,-1,   0,-1, 0,   1, 1, 1,   0.666666f, 0.00f},   // unten links (bottom)
  { 1,-1,-1,   0,-1, 0,   1, 1, 1,   1.000000f, 0.00f},   // unten rechts
  { 1,-1, 1,   0,-1, 0,   1, 1, 1,   1.000000f, 0.50f},   // oben rechts
  {-1,-1, 1,   0,-1, 0,   1, 1, 1,   0.666666f, 0.50f}   // oben links

};

const GLuint ogl::Cuboid::INDICES[] = {
   0, 1, 2,   2, 3, 0,      // front
   4, 5, 6,   6, 7, 4,      // right
   8, 9,10,  10,11, 8,      // top
  12,13,14,  14,15,12,      // left
  16,17,18,  18,19,16,      // bottom
  20,21,22,  22,23,20       // back
};

//############################################################################
/** |
    ((V, N, C, T), (V, N, C, T), ...)
    ((vx,vy,vz, nx,ny,nz, cr,cg,cb, tx,ty), (...), ...)


//    v6----- v5
//   /|      /|
//  v3------v2|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v0------v1
*/
//############################################################################  
ogl::Cuboid::Cuboid(GLfloat u, GLfloat v, GLfloat w, GLfloat r, GLfloat g, GLfloat b)
  : Shape(), cuboid_u(u), cuboid_v(v), cuboid_w(w)
{
  buffer_len = 24 * struct_len;
  buffer = new GLfloat[buffer_len];
  for (unsigned int i = 0; i < 24; i++) {
    buffer[struct_len * i +  0] = VERTICES[i][ 0] * cuboid_u;
    buffer[struct_len * i +  1] = VERTICES[i][ 1] * cuboid_v;
    buffer[struct_len * i +  2] = VERTICES[i][ 2] * cuboid_w;
    buffer[struct_len * i +  3] = VERTICES[i][ 3];
    buffer[struct_len * i +  4] = VERTICES[i][ 4];
    buffer[struct_len * i +  5] = VERTICES[i][ 5];
    buffer[struct_len * i +  6] = r;
    buffer[struct_len * i +  7] = g;
    buffer[struct_len * i +  8] = b;
    buffer[struct_len * i +  9] = VERTICES[i][ 9];
    buffer[struct_len * i + 10] = VERTICES[i][10];
  }

  indice_len = 36;
  indices = new GLuint[indice_len];
  for (unsigned int i = 0; i < indice_len; i++) {
    indices[i] = INDICES[i];
  }

}

//############################################################################
/** 
*/
//############################################################################  
ogl::Cuboid::~Cuboid()
{
}

//############################################################################
/** 
*/
//############################################################################  
ogl::Cuboid::Cuboid(const Cuboid& original)
  : Shape(original)
{
  cuboid_u = original.cuboid_u;
  cuboid_v = original.cuboid_v;
  cuboid_w = original.cuboid_w;
}

//############################################################################
/** 
*/
//############################################################################  
ogl::Cuboid& ogl::Cuboid::operator=(const Cuboid& original)
{
  if (this != &original) {
    //Shape::operator=(original);
    cuboid_u = original.cuboid_u;
    cuboid_v = original.cuboid_v;
    cuboid_w = original.cuboid_w;
  }
  return *this;
}

//############################################################################
/** 
*/
//############################################################################  
std::vector<glm::vec3> ogl::Cuboid::vertices() const
{
  std::vector<glm::vec3> result;
  unsigned int p = struct_len;
  result.push_back(glm::vec3(buffer[ 0 * p + 0], buffer[ 0 * p + 1], buffer[ 0 * p + 2]));
  result.push_back(glm::vec3(buffer[ 1 * p + 0], buffer[ 1 * p + 1], buffer[ 1 * p + 2]));
  result.push_back(glm::vec3(buffer[ 2 * p + 0], buffer[ 2 * p + 1], buffer[ 2 * p + 2]));
  result.push_back(glm::vec3(buffer[ 3 * p + 0], buffer[ 3 * p + 1], buffer[ 3 * p + 2]));
  result.push_back(glm::vec3(buffer[ 6 * p + 0], buffer[ 6 * p + 1], buffer[ 6 * p + 2]));
  result.push_back(glm::vec3(buffer[ 7 * p + 0], buffer[ 7 * p + 1], buffer[ 7 * p + 2]));
  result.push_back(glm::vec3(buffer[13 * p + 0], buffer[13 * p + 1], buffer[13 * p + 2]));
  result.push_back(glm::vec3(buffer[14 * p + 0], buffer[14 * p + 1], buffer[14 * p + 2]));
  return result;
}

//############################################################################
/** 
*/
//############################################################################  
std::vector< std::vector<glm::vec3> > ogl::Cuboid::triangles() const
{
  std::vector< std::vector<glm::vec3> > result;
  for (unsigned int i = 0; i < indice_len; i += 3) {
    std::vector<glm::vec3> temp;
    temp.push_back(glm::vec3(
      buffer[indices[i + 0] * struct_len + 0],
      buffer[indices[i + 0] * struct_len + 1],
      buffer[indices[i + 0] * struct_len + 2]
    ));
    temp.push_back(glm::vec3(
      buffer[indices[i + 1] * struct_len + 0],
      buffer[indices[i + 1] * struct_len + 1],
      buffer[indices[i + 1] * struct_len + 2]
    ));
    temp.push_back(glm::vec3(
      buffer[indices[i + 2] * struct_len + 0],
      buffer[indices[i + 2] * struct_len + 1],
      buffer[indices[i + 2] * struct_len + 2]
    ));
    result.push_back(temp);
  }
  return result;
}

//############################################################################
/** 
*/
//############################################################################  
std::vector< std::vector<glm::vec3> > ogl::Cuboid::rectangles() const
{
  std::vector< std::vector<glm::vec3> > result;
  for (unsigned int i = 0; i < buffer_len; i += 4 * struct_len) {
    std::vector<glm::vec3> temp;
    temp.push_back(glm::vec3(
      buffer[i + (0 * struct_len) + 0],
      buffer[i + (0 * struct_len) + 1],
      buffer[i + (0 * struct_len) + 2]
    ));
    temp.push_back(glm::vec3(
      buffer[i + (1 * struct_len) + 0],
      buffer[i + (1 * struct_len) + 1],
      buffer[i + (1 * struct_len) + 2]
    ));
    temp.push_back(glm::vec3(
      buffer[i + (2 * struct_len) + 0],
      buffer[i + (2 * struct_len) + 1],
      buffer[i + (2 * struct_len) + 2]
    ));
    temp.push_back(glm::vec3(
      buffer[i + (3 * struct_len) + 0],
      buffer[i + (3 * struct_len) + 1],
      buffer[i + (3 * struct_len) + 2]
    ));
    result.push_back(temp);
  }
  return result;
}

//############################################################################
/** 
*/
//############################################################################  
std::vector< std::vector<GLfloat> > ogl::Cuboid::planeUVs() const
{
  std::vector< std::vector<GLfloat> > result;
  for (unsigned int i = 0; i < buffer_len; i += 4 * struct_len) {
    std::vector<GLfloat> temp;
    temp.push_back(buffer[i +  9]);
    temp.push_back(buffer[i + 10]);
    result.push_back(temp);
  }
  return result;
}

//############################################################################
/** 
*/
//############################################################################  
glm::vec3 ogl::Cuboid::center() const
{
  unsigned int p = struct_len;
  glm::vec3 p1 (buffer[ 1 * p + 0], buffer[ 1 * p + 1], buffer[ 1 * p + 2]);
  glm::vec3 p2 (buffer[20 * p + 0], buffer[20 * p + 1], buffer[20 * p + 2]);
  glm::vec3 v1 (p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
  return p1 + v1 * 0.5f;
}

////############################################################################
///** 
//*/
////############################################################################  
//void ogl::Cuboid::setTrans(glm::mat4 matrix)
//{
//  unsigned int p = struct_len;
//
//  for (unsigned int i = 0; i < 24; i += 4) {
//
//    glm::vec4 V0 (matrix * glm::vec4 (
//      VERTICES[i + 0][0] * cuboid_u, 
//      VERTICES[i + 0][1] * cuboid_v, 
//      VERTICES[i + 0][2] * cuboid_w, 1
//    ));
//
//    glm::vec4 V1 (matrix * glm::vec4 (
//      VERTICES[i + 1][0] * cuboid_u, 
//      VERTICES[i + 1][1] * cuboid_v, 
//      VERTICES[i + 1][2] * cuboid_w, 1
//    ));
//
//    glm::vec4 V2 (matrix * glm::vec4 (
//      VERTICES[i + 2][0] * cuboid_u, 
//      VERTICES[i + 2][1] * cuboid_v, 
//      VERTICES[i + 2][2] * cuboid_w, 1
//    ));
//
//    glm::vec4 V3 (matrix * glm::vec4 (
//      VERTICES[i + 3][0] * cuboid_u, 
//      VERTICES[i + 3][1] * cuboid_v, 
//      VERTICES[i + 3][2] * cuboid_w, 1
//    ));
//
//    buffer[(i + 0) * p + 0] = V0.x; buffer[(i + 0) * p + 1] = V0.y; buffer[(i + 0) * p + 2] = V0.z;
//    buffer[(i + 1) * p + 0] = V1.x; buffer[(i + 1) * p + 1] = V1.y; buffer[(i + 1) * p + 2] = V1.z;
//    buffer[(i + 2) * p + 0] = V2.x; buffer[(i + 2) * p + 1] = V2.y; buffer[(i + 2) * p + 2] = V2.z;
//    buffer[(i + 3) * p + 0] = V3.x; buffer[(i + 3) * p + 1] = V3.y; buffer[(i + 3) * p + 2] = V3.z;
//
//    glm::vec3 N0 = glm::normalize(glm::cross(glm::vec3(V1 - V0), glm::vec3(V3 - V0)));
//
//    buffer[(i + 0) * p + 3] = N0.x;  buffer[(i + 0) * p + 4] = N0.y;  buffer[(i + 0) * p + 5] = N0.z;
//    buffer[(i + 1) * p + 3] = N0.x;  buffer[(i + 1) * p + 4] = N0.y;  buffer[(i + 1) * p + 5] = N0.z;
//    buffer[(i + 2) * p + 3] = N0.x;  buffer[(i + 2) * p + 4] = N0.y;  buffer[(i + 2) * p + 5] = N0.z;
//    buffer[(i + 3) * p + 3] = N0.x;  buffer[(i + 3) * p + 4] = N0.y;  buffer[(i + 3) * p + 5] = N0.z;
//
//  }
//}
//
////############################################################################
///**
//*/
////############################################################################
//void ogl::Cuboid::addTrans(glm::mat4 matrix)
//{
//  unsigned int p = struct_len;
//
//  for (unsigned int i = 0; i < buffer_len; i += 4 * struct_len) {
//
//    glm::vec4 V0 (matrix * glm::vec4 (
//      buffer[i + (0 * p) + 0], buffer[i + (0 * p) + 1], buffer[i + (0 * p) + 2], 1
//    ));
//
//    glm::vec4 V1 (matrix * glm::vec4 (
//      buffer[i + (1 * p) + 0], buffer[i + (1 * p) + 1], buffer[i + (1 * p) + 2], 1
//    ));
//
//    glm::vec4 V2 (matrix * glm::vec4 (
//      buffer[i + (2 * p) + 0], buffer[i + (2 * p) + 1], buffer[i + (2 * p) + 2], 1
//    ));
//
//    glm::vec4 V3 (matrix * glm::vec4 (
//      buffer[i + (3 * p) + 0], buffer[i + (3 * p) + 1], buffer[i + (3 * p) + 2], 1
//    ));
//
//    buffer[i + (0 * p) + 0] = V0.x; buffer[i + (0 * p) + 1] = V0.y; buffer[i + (0 * p) + 2] = V0.z;
//    buffer[i + (1 * p) + 0] = V1.x; buffer[i + (1 * p) + 1] = V1.y; buffer[i + (1 * p) + 2] = V1.z;
//    buffer[i + (2 * p) + 0] = V2.x; buffer[i + (2 * p) + 1] = V2.y; buffer[i + (2 * p) + 2] = V2.z;
//    buffer[i + (3 * p) + 0] = V3.x; buffer[i + (3 * p) + 1] = V3.y; buffer[i + (3 * p) + 2] = V3.z;
//
//    glm::vec3 N0 = glm::normalize(glm::cross(glm::vec3(V1 - V0), glm::vec3(V3 - V0)));
//
//    buffer[i + (0 * p) + 3] = N0.x;  buffer[i + (0 * p) + 4] = N0.y;  buffer[i + (0 * p) + 5] = N0.z;
//    buffer[i + (1 * p) + 3] = N0.x;  buffer[i + (1 * p) + 4] = N0.y;  buffer[i + (1 * p) + 5] = N0.z;
//    buffer[i + (2 * p) + 3] = N0.x;  buffer[i + (2 * p) + 4] = N0.y;  buffer[i + (2 * p) + 5] = N0.z;
//    buffer[i + (3 * p) + 3] = N0.x;  buffer[i + (3 * p) + 4] = N0.y;  buffer[i + (3 * p) + 5] = N0.z;
//
//  }
//}
//
//############################################################################
/** 
*/
//############################################################################  
bool ogl::Cuboid::intersect(glm::vec3 P1, glm::vec3 P2, glm::vec3 &PI, GLuint &plane) const
{
  bool result = false;
  std::vector< std::vector<glm::vec3> > rects = rectangles();

  for (unsigned int i = 0; i < rects.size(); i++) {

    glm::vec3 E1 (rects[i][0]);
    glm::vec3 E2 (rects[i][1]);
    glm::vec3 E3 (rects[i][3]);

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
    	) {
    	  result = true;
        if (t < PI.x) {
          plane = i;
      	  PI.x = t;
      	  PI.y = u;
      	  PI.z = v;
        }
    	}
    }
  }
  return result;
}

//############################################################################
/** 
*/
//############################################################################  
void ogl::Cuboid::render() const
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
