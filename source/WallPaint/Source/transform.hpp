/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#ifndef OGL_TRANSFORM_HPP
#define OGL_TRANSFORM_HPP

#include <vector>
#include <iostream>

#include <SFML/OpenGL.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace ogl {

  class Transform
  {
    protected:
      glm::mat4 matrix;

    public:
      //static enum GAME_STATE {
      //  GS_WAIT_FOR_PLAYERS = 0,
      //  GS_READY,
      //  GS_PLAYING,
      //  GS_TIME_UP,
      //  GS_FINISHED,
      //  GS_ABORTED,
      //  GS_FINAL_STATUS
      //}; 

    private:
      bool animate;
      bool looping;

      GLfloat duration;
      GLfloat timestamp;
      GLfloat animspeed;

      unsigned int lstIdx1;
      unsigned int lstIdx2;

      std::vector<glm::vec3> movepath;
      GLfloat rot_X_duration;
      GLfloat rot_Y_duration;
      GLfloat rot_Z_duration;
      GLfloat rot_X_scale;
      GLfloat rot_Y_scale;
      GLfloat rot_Z_scale;

    public:
      Transform();
      virtual ~Transform();
      Transform(const Transform& geom);
      Transform& operator=(const Transform& trans);

      void setRotX(GLfloat angle = 360.0f);
      void setRotY(GLfloat angle = 360.0f);
      void setRotZ(GLfloat angle = 360.0f);

      void movePath(std::vector<glm::vec3> vertices, GLfloat time);
      void setPath(std::vector<glm::vec3> vertices);
      void setTime(GLfloat time);

      void update(GLfloat delta);

      void setPathAnimation();
      void setRingAnimation();

      void start();
      void pause();
      void follo();
      void abort();

      glm::mat4 getMatrix() const;
      void setMatrix(glm::mat4 matrix);

      bool isActive();

    private:
      glm::mat4 rotateX(GLfloat scale);
      glm::mat4 rotateY(GLfloat scale);
      glm::mat4 rotateZ(GLfloat scale);

  };

}

#endif
