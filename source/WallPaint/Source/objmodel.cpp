/*###############################################################################
Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#include "objmodel.hpp"

//############################################################################
/** 
((V, N, C, T), (V, N, C, T), ...)
((vx,vy,vz, nx,ny,nz, cr,cg,cb, tx,ty), (...), ...)
*/
//############################################################################  
ogl::ObjModel::ObjModel(boost::filesystem::path path, GLfloat r, GLfloat g, GLfloat b)
  : Shape()
{
  if (boost::filesystem::exists(path)) {
    std::ifstream file (path.c_str(), std::ios::in | std::ios::binary);
    loadModel(file, r, g, b);
    file.close();
  }
}

//############################################################################
/** 
*/
//############################################################################  
ogl::ObjModel::~ObjModel()
{
}

//############################################################################
/** 
*/
//############################################################################  
ogl::ObjModel::ObjModel(const ObjModel& original)
  : Shape(original)
{
  path = original.path;
}

//############################################################################
/** 
*/
//############################################################################  
ogl::ObjModel& ogl::ObjModel::operator=(const ObjModel& original)
{
  if(this != &original) {
    Shape::operator=(original);
    path = original.path;
  }
  return *this;
}

//############################################################################
/** 
*/
//############################################################################  
GLvoid ogl::ObjModel::loadModel(std::ifstream& file, GLfloat r, GLfloat g, GLfloat b) 
{
  std::vector<glm::vec3> vertices = std::vector<glm::vec3>();
  std::vector<glm::vec3> normals = std::vector<glm::vec3>();
  std::vector<glm::vec2> texcoord = std::vector<glm::vec2>();
  std::vector<glm::ivec3> indices = std::vector<glm::ivec3>();

  std::string line;
  file.seekg (0, std::ios::beg);
  while (std::getline(file, line)) {

    if (0 < line.length()) {
      std::vector<std::string> tokens;
      boost::split(tokens, line, boost::is_any_of(" /"));

      if (tokens[0] == "v") {
        vertices.push_back(glm::vec3(
          std::atof(tokens[1].c_str()), 
          std::atof(tokens[2].c_str()), 
          std::atof(tokens[3].c_str())
        ));

      } else if (tokens[0] == "vn") {
        normals.push_back(glm::vec3(
          std::atof(tokens[1].c_str()), 
          std::atof(tokens[2].c_str()), 
          std::atof(tokens[3].c_str())
        ));

      } else if (tokens[0] == "vt") {
        texcoord.push_back(glm::vec2(
          std::atof(tokens[1].c_str()), 
          std::atof(tokens[2].c_str())
        ));

      } else if (tokens[0] == "f") {
        indices.push_back(glm::ivec3(
          std::atoi(tokens[1].c_str()), 
          std::atoi(tokens[2].c_str()), 
          std::atoi(tokens[3].c_str())
        ));
        indices.push_back(glm::ivec3(
          std::atoi(tokens[4].c_str()), 
          std::atoi(tokens[5].c_str()), 
          std::atoi(tokens[6].c_str())
        ));
        indices.push_back(glm::ivec3(
          std::atoi(tokens[7].c_str()), 
          std::atoi(tokens[8].c_str()), 
          std::atoi(tokens[9].c_str())
        ));
      }
    }
  }

  Geometry::buffer_len = indices.size() * struct_len;
  Geometry::buffer = new GLfloat[Geometry::buffer_len];
  for (unsigned int i = 0; i < indices.size(); ++i) {
    buffer[struct_len * i +  0] = vertices[indices[i][0] - 1][0];
    buffer[struct_len * i +  1] = vertices[indices[i][0] - 1][1];
    buffer[struct_len * i +  2] = vertices[indices[i][0] - 1][2];
    buffer[struct_len * i +  3] = normals[indices[i][2] - 1][0];
    buffer[struct_len * i +  4] = normals[indices[i][2] - 1][1];
    buffer[struct_len * i +  5] = normals[indices[i][2] - 1][2];
    buffer[struct_len * i +  6] = r;
    buffer[struct_len * i +  7] = g;
    buffer[struct_len * i +  8] = b;
    buffer[struct_len * i +  9] = texcoord[indices[i][1] - 1][0];
    buffer[struct_len * i + 10] = texcoord[indices[i][1] - 1][1];
  }

  Geometry::indice_len = indices.size();
  Geometry::indices = new GLuint[Geometry::indice_len];
  for (unsigned int i = 0; i < Geometry::indice_len; ++i) {
    Geometry::indices[i] = i;
  }

}

//############################################################################
/**
*/
//############################################################################
void ogl::ObjModel::render() const
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
