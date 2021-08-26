/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#ifndef OGL_CAMERA_HPP
#define OGL_CAMERA_HPP

#include <vector>
#include <iostream>

#include <SFML/OpenGL.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ogl {

  class Camera
  {
    private:
      glm::mat4 matrix;
      glm::mat4 lookat;

    public:
      Camera(
        glm::mat4 mtx = glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 1000.0f), 
        glm::vec3 src = glm::vec3(0.0f, 0.0f, 1.0f), 
        glm::vec3 trg = glm::vec3(0.0f, 0.0f, 0.0f), 
        glm::vec3 vec = glm::vec3(0.0f, 1.0f, 0.0f)
      );

      Camera(glm::mat4& mtx, glm::mat4& lkt);

      virtual ~Camera();
      Camera(const Camera& cam);
      Camera& operator=(const Camera& cam);

      void modDistance(GLfloat scale);
      void rotateAxisX(GLfloat scale);
      void rotateAxisY(GLfloat scale);

      glm::mat4 mtx() const;

  };

}

#endif
