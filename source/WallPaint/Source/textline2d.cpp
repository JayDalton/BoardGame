/*###############################################################################
Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#include "textline2d.hpp"

const GLuint ogl::TextLine2D::INDICES[] = {0, 1, 3, 1, 2, 3};

const GLfloat ogl::TextLine2D::VERTICES[][11] = {
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
ogl::TextLine2D::TextLine2D(std::string text, const Texture *tex)
  : Shape(), Texture(*tex)
{
  unsigned int length = text.size();
  Geometry::buffer_len = length * 4 * struct_len;
  Geometry::indice_len = length * 6;
  Geometry::buffer = new GLfloat[buffer_len];
  Geometry::indices = new GLuint[indice_len];

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> UVs;
  for (unsigned int c = 0; c < length; ++c) {

		char character = text[c];
		float uv_x = (character % 16) / 16.0f;
		float uv_y = (character / 16) / 16.0f;

  //  buffer[c * 4 * struct_len +   0] = x + c * scale;
  //  buffer[c * 4 * struct_len +   0] = y + scale;
  //  buffer[c * 4 * struct_len +   0] = 0.0f;

  //  buffer[c * 4 * struct_len +   0] = 0.0f;
  //  buffer[c * 4 * struct_len +   0] = 0.0f;
  //  buffer[c * 4 * struct_len +   0] = 1.0f;

  //  buffer[c * 4 * struct_len +   0] = 1.0f;
  //  buffer[c * 4 * struct_len +   0] = 1.0f;
  //  buffer[c * 4 * struct_len +   0] = 1.0f;

  //  glm::vec3 vertex0 ( x + c * scale        , y + scale, 0.0f);
		//glm::vec3 vertex1 ( x + c * scale + scale, y + scale, 0.0f);
		//glm::vec3 vertex2 ( x + c * scale + scale, y        , 0.0f);
		//glm::vec3 vertex3 ( x + c * scale        , y        , 0.0f);

  //  glm::vec3 normal0 (0.0f, 0.0f, 1.0f);
  //  glm::vec3 normal1 (0.0f, 0.0f, 1.0f);
  //  glm::vec3 normal2 (0.0f, 0.0f, 1.0f);
  //  glm::vec3 normal3 (0.0f, 0.0f, 1.0f);

  //  glm::vec3 colors0 (1.0f, 1.0f, 1.0f);
  //  glm::vec3 colors1 (1.0f, 1.0f, 1.0f);
  //  glm::vec3 colors2 (1.0f, 1.0f, 1.0f);
  //  glm::vec3 colors3 (1.0f, 1.0f, 1.0f);

		//glm::vec2 vertuv0 (glm::vec2( uv_x           , 1.0f - uv_y ));
		//glm::vec2 vertuv1 (glm::vec2( uv_x+1.0f/16.0f, 1.0f - uv_y ));
		//glm::vec2 vertuv2 (glm::vec2( uv_x+1.0f/16.0f, 1.0f - (uv_y + 1.0f/16.0f) ));
		//glm::vec2 vertuv3 (glm::vec2( uv_x           , 1.0f - (uv_y + 1.0f/16.0f) ));

    for (unsigned int i = 0; i < 4; ++i) {
      Geometry::buffer[c * 4 * struct_len + struct_len * i +  0] = VERTICES[i][ 0] + c;
      Geometry::buffer[c * 4 * struct_len + struct_len * i +  1] = VERTICES[i][ 1];
      Geometry::buffer[c * 4 * struct_len + struct_len * i +  2] = VERTICES[i][ 2];
      Geometry::buffer[c * 4 * struct_len + struct_len * i +  3] = VERTICES[i][ 3];
      Geometry::buffer[c * 4 * struct_len + struct_len * i +  4] = VERTICES[i][ 4];
      Geometry::buffer[c * 4 * struct_len + struct_len * i +  5] = VERTICES[i][ 5];
      Geometry::buffer[c * 4 * struct_len + struct_len * i +  6] = 1.0f;
      Geometry::buffer[c * 4 * struct_len + struct_len * i +  7] = 1.0f;
      Geometry::buffer[c * 4 * struct_len + struct_len * i +  8] = 1.0f;
      Geometry::buffer[c * 4 * struct_len + struct_len * i +  9] = (i == 0 || i == 3) ? uv_x : uv_x + 1.0f/16.0f; //VERTICES[i][ 9];
      Geometry::buffer[c * 4 * struct_len + struct_len * i + 10] = (i == 2 || i == 3) ? 1.0f - uv_y : 1.0f - (uv_y + 1.0f/16.0f); //VERTICES[i][10];
    }

    for (unsigned int i = 0; i < 6; ++i) {
      indices[i + c * 6] = INDICES[i] + c * 4;
    }
  }
  Texture::init();
  Texture::bind();
}

//############################################################################
/** 
*/
//############################################################################  
ogl::TextLine2D::~TextLine2D()
{
}

//############################################################################
/** 
*/
//############################################################################  
ogl::TextLine2D::TextLine2D(const TextLine2D& original)
  : Shape(original), Texture(original)
{
}

//############################################################################
/** 
*/
//############################################################################  
ogl::TextLine2D& ogl::TextLine2D::operator=(const TextLine2D& original)
{
  if(this != &original) {
    Shape::operator=(original);
    Texture::operator=(original);
  }
  return *this;
}

//############################################################################
/**
*/
//############################################################################
void ogl::TextLine2D::render() const
{

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, Texture::id);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(3, GL_FLOAT, StructSize(), Geometry::getBuffer());
  glNormalPointer(GL_FLOAT, StructSize(), Geometry::getBuffer(3));
  glColorPointer(3, GL_FLOAT, StructSize(), Geometry::getBuffer(6));
  glTexCoordPointer(2, GL_FLOAT, StructSize(), Geometry::getBuffer(9));
  glDrawElements(GL_TRIANGLES, IndiceLength(), GL_UNSIGNED_INT, getIndice());

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);

  glDisable(GL_BLEND);
}
