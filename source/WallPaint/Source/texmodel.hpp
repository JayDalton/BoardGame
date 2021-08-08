/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#ifndef OGL_TEXMODEL_HPP
#define OGL_TEXMODEL_HPP

#include <boost/filesystem.hpp>

#include <SFML/OpenGL.hpp>

#include "texture.hpp"
#include "objmodel.hpp"

namespace ogl {

  class TexModel : public ObjModel, public Texture
  {
    public:
      TexModel(boost::filesystem::path path, const Texture *tex);
      TexModel(boost::filesystem::path path, const Texture &tex);
      TexModel(
        boost::filesystem::path path,
        GLuint tu = 10, GLuint tv = 10,
        GLfloat cr = 1, GLfloat cg = 1,
        GLfloat cb = 1, GLfloat ca = 1
      );
      virtual ~TexModel();
      TexModel(const TexModel& area);
      TexModel& operator=(const TexModel& area);

      void setTexture(const Texture *tex);
      void setTexture(const Texture &tex);

      void draw(
        GLint x, 
        GLint y, 
        const Texture* tex, 
        GLfloat cr = 0, 
        GLfloat cg = 0, 
        GLfloat cb = 0, 
        GLfloat ca = 0
      );

      void fill(
        GLfloat cr = 1, 
        GLfloat cg = 1, 
        GLfloat cb = 1, 
        GLfloat ra = 1
      );

      virtual void render() const;

  };

}

#endif
