#pragma once

//#include <SDL2/SDL_opengl.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ogl {

  class Camera
  {
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

      void modDistance(float scale);
      void rotateAxisX(float scale);
      void rotateAxisY(float scale);

      glm::mat4 mtx() const;

    private:
      glm::mat4 matrix;
      glm::mat4 lookat;

  };

}
