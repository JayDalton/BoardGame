/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#include "icosphere.hpp"

//############################################################################
/** 
*/
//############################################################################  
ogl::IcoSphere::IcoSphere(unsigned int iteration, GLfloat r, GLfloat g, GLfloat b)
  : Shape(), Index(0), recursion(iteration)
{
  middlePointIndexCache = std::map<unsigned long, unsigned int>();

  GLfloat t = (1.0f + sqrt(5.0f)) / 2.0f;

  addVertex( glm::vec3(-1, +t, +0));
  addVertex( glm::vec3(+1, +t, +0));
  addVertex( glm::vec3(-1, -t, +0));
  addVertex( glm::vec3(+1, -t, +0));

  addVertex( glm::vec3( 0, -1,  t));
  addVertex( glm::vec3( 0,  1,  t));
  addVertex( glm::vec3( 0, -1, -t));
  addVertex( glm::vec3( 0,  1, -t));

  addVertex( glm::vec3( t,  0, -1));
  addVertex( glm::vec3( t,  0,  1));
  addVertex( glm::vec3(-t,  0, -1));
  addVertex( glm::vec3(-t,  0,  1));

  generate();
  setBuffer();
  setIndices();  
  setColor(r, g, b);
  vertices.clear();
  triangle.clear();
  middlePointIndexCache.clear();
}

//############################################################################
/** 
*/
//############################################################################  
ogl::IcoSphere::~IcoSphere()
{
}

//############################################################################
/** 
*/
//############################################################################  
ogl::IcoSphere::IcoSphere(const IcoSphere& original)
  : Shape(original)
{
  vertices = original.vertices;
  triangle = original.triangle;
  middlePointIndexCache = original.middlePointIndexCache;
}

//############################################################################
/** 
*/
//############################################################################  
ogl::IcoSphere& ogl::IcoSphere::operator=(const IcoSphere& original)
{
  if (this != &original) {
    Shape::operator=(original);
    vertices = original.vertices;
    triangle = original.triangle;
    middlePointIndexCache = original.middlePointIndexCache;
  }
  return *this;
}

//############################################################################
/** 
*/
//############################################################################  
unsigned int ogl::IcoSphere::addVertex(glm::vec3 v)
{
  vertices.push_back(glm::normalize(v));
  return Index++;
}

//############################################################################
/** 
     p1      p7
    /|       | \
   p0|       |  p5       p8----- p9
   | |       |  |       /       / 
   | |p3     p6 |     p10------p11
   |/         \ |
   p2          p4       
*/
//############################################################################  
void ogl::IcoSphere::generate()
{
  // create 20 triangles of the icosahedron

  // 5 faces around point 0
  triangle.push_back( glm::vec3(0, 11,  5));
  triangle.push_back( glm::vec3(0,  5,  1));
  triangle.push_back( glm::vec3(0,  1,  7));
  triangle.push_back( glm::vec3(0,  7, 10));
  triangle.push_back( glm::vec3(0, 10, 11));

  // 5 adjacent faces
  triangle.push_back( glm::vec3( 1,  5, 9));
  triangle.push_back( glm::vec3( 5, 11, 4));
  triangle.push_back( glm::vec3(11, 10, 2));
  triangle.push_back( glm::vec3(10,  7, 6));
  triangle.push_back( glm::vec3( 7,  1, 8));

  // 5 faces around point 3
  triangle.push_back( glm::vec3( 3, 9, 4 ));
  triangle.push_back( glm::vec3( 3, 4, 2 ));
  triangle.push_back( glm::vec3( 3, 2, 6 ));
  triangle.push_back( glm::vec3( 3, 6, 8 ));
  triangle.push_back( glm::vec3( 3, 8, 9 ));

  // 5 adjacent faces
  triangle.push_back( glm::vec3( 4, 9, 5 ));
  triangle.push_back( glm::vec3( 2, 4, 11));
  triangle.push_back( glm::vec3( 6, 2, 10));
  triangle.push_back( glm::vec3( 8, 6, 7 ));
  triangle.push_back( glm::vec3( 9, 8, 1 ));

  // refine triangles
  for (unsigned int i = 0; i < recursion; i++)
  {
    std::vector<glm::vec3> faces;
    for (std::vector<glm::vec3>::iterator it = triangle.begin(); it != triangle.end(); it++)
    {
      // replace triangle by 4 triangles
      unsigned int a = getMiddlePoint((*it).x, (*it).y);
      unsigned int b = getMiddlePoint((*it).y, (*it).z);
      unsigned int c = getMiddlePoint((*it).z, (*it).x);

      faces.push_back( glm::vec3((*it).x, a, c));
      faces.push_back( glm::vec3((*it).y, b, a));
      faces.push_back( glm::vec3((*it).z, c, b));
      faces.push_back( glm::vec3(a, b, c));
    }
    triangle = faces;
  }
  
}

//############################################################################
/** 
*/
//############################################################################  
GLuint ogl::IcoSphere::getMiddlePoint(GLuint p1, GLuint p2)
{
  GLuint pid = 0;
  bool FirstIsSmaller = p1 < p2;
  GLuint SmallerIndex = FirstIsSmaller ? p1 : p2;
  GLuint GreaterIndex = FirstIsSmaller ? p2 : p1;
  unsigned long Key = (SmallerIndex << 16) + GreaterIndex;

  if (0 < middlePointIndexCache.count(Key)) {
    pid = middlePointIndexCache.find(Key)->second;
  } else {
    glm::vec3 point1 = vertices[p1];
    glm::vec3 point2 = vertices[p2];
    glm::vec3 middle = glm::vec3(
      (point1.x + point2.x) / 2.0f,
      (point1.y + point2.y) / 2.0f,
      (point1.z + point2.z) / 2.0f
    );
    pid = middlePointIndexCache[Key] = addVertex(middle);
  }
  
  return pid;
}

//############################################################################
/** 
*/
//############################################################################  
void ogl::IcoSphere::setBuffer()
{
  buffer_len = 0;
  buffer = new GLfloat[triangle.size() * 3 * struct_len];

  for (unsigned int t = 0; t < triangle.size(); t++) {

    buffer[buffer_len] = vertices[triangle[t].x].x; buffer_len++;
    buffer[buffer_len] = vertices[triangle[t].x].y; buffer_len++;
    buffer[buffer_len] = vertices[triangle[t].x].z; buffer_len++;
    buffer[buffer_len] = vertices[triangle[t].x].x; buffer_len++;
    buffer[buffer_len] = vertices[triangle[t].x].y; buffer_len++;
    buffer[buffer_len] = vertices[triangle[t].x].z; buffer_len++;
    buffer[buffer_len] = 1.0f; buffer_len++;
    buffer[buffer_len] = 1.0f; buffer_len++;
    buffer[buffer_len] = 1.0f; buffer_len++;
    buffer[buffer_len] = glm::asin(vertices[triangle[t].x].x) / glm::pi<GLfloat>() + 0.5f; buffer_len++;
    buffer[buffer_len] = glm::asin(vertices[triangle[t].x].y) / glm::pi<GLfloat>() + 0.5f; buffer_len++;

    buffer[buffer_len] = vertices[triangle[t].y].x; buffer_len++;
    buffer[buffer_len] = vertices[triangle[t].y].y; buffer_len++;
    buffer[buffer_len] = vertices[triangle[t].y].z; buffer_len++;
    buffer[buffer_len] = vertices[triangle[t].y].x; buffer_len++;
    buffer[buffer_len] = vertices[triangle[t].y].y; buffer_len++;
    buffer[buffer_len] = vertices[triangle[t].y].z; buffer_len++;
    buffer[buffer_len] = 1.0f; buffer_len++;
    buffer[buffer_len] = 1.0f; buffer_len++;
    buffer[buffer_len] = 1.0f; buffer_len++;
    buffer[buffer_len] = glm::asin(vertices[triangle[t].y].x) / glm::pi<GLfloat>() + 0.5f; buffer_len++;
    buffer[buffer_len] = glm::asin(vertices[triangle[t].y].y) / glm::pi<GLfloat>() + 0.5f; buffer_len++;

    buffer[buffer_len] = vertices[triangle[t].z].x; buffer_len++;
    buffer[buffer_len] = vertices[triangle[t].z].y; buffer_len++;
    buffer[buffer_len] = vertices[triangle[t].z].z; buffer_len++;
    buffer[buffer_len] = vertices[triangle[t].z].x; buffer_len++;
    buffer[buffer_len] = vertices[triangle[t].z].y; buffer_len++;
    buffer[buffer_len] = vertices[triangle[t].z].z; buffer_len++;
    buffer[buffer_len] = 1.0f; buffer_len++;
    buffer[buffer_len] = 1.0f; buffer_len++;
    buffer[buffer_len] = 1.0f; buffer_len++;
    buffer[buffer_len] = glm::asin(vertices[triangle[t].z].x) / glm::pi<GLfloat>() + 0.5f; buffer_len++;
    buffer[buffer_len] = glm::asin(vertices[triangle[t].z].y) / glm::pi<GLfloat>() + 0.5f; buffer_len++;

  }
}

//############################################################################
/** 
*/
//############################################################################  
void ogl::IcoSphere::setIndices()
{
  indice_len = triangle.size() * 3;
  indices = new GLuint[indice_len];
  for (GLuint t = 0; t < indice_len; t++) {
    indices[t] = t;
  }
}

//############################################################################
/** 
*/
//############################################################################  
void ogl::IcoSphere::render() const
{
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glPushMatrix();
  glMultMatrixf(glm::value_ptr(matrix));
  glVertexPointer(3, GL_FLOAT, StructSize(), getBuffer(0));
  glNormalPointer(GL_FLOAT, StructSize(), getBuffer(3));
  glColorPointer(3, GL_FLOAT, StructSize(), getBuffer(6));
  glTexCoordPointer(2, GL_FLOAT, StructSize(), getBuffer(9));
  glDrawElements(GL_TRIANGLES, IndiceLength(), GL_UNSIGNED_INT, getIndice(0));
  glPopMatrix();

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}
