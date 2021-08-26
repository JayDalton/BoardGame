#include "camera.hpp"

ogl::Camera::Camera(glm::mat4 mtx, glm::vec3 src, glm::vec3 trg, glm::vec3 vec)
  : matrix(mtx), lookat(glm::lookAt(src, trg, vec))
{
}

ogl::Camera::Camera(glm::mat4& mtx, glm::mat4& lkt)
  : matrix(mtx), lookat(lkt)
{
}

ogl::Camera::~Camera()
{
}

ogl::Camera::Camera(const Camera& original)
{
  matrix = original.matrix;
  lookat = original.lookat;
}

ogl::Camera& ogl::Camera::operator=(const Camera& original)
{
  if(this != &original) {
    matrix = original.matrix;
    lookat = original.lookat;
  }
  return *this;
}

void ogl::Camera::modDistance(GLfloat scale)
{
  glm::vec3 vector(glm::inverse(lookat)[3]); // Might have to divide by w if you can't assume w == 1
  //glm::vec3 vector (glm::vec3(lookat[3]) * glm::mat3(lookat)); // only if no scaling on mtx

  lookat = glm::translate(lookat, vector * scale);
}

void ogl::Camera::rotateAxisX(GLfloat scale)
{
  lookat = glm::rotate(lookat, scale, glm::vec3(1.0f, 0.0f, 0.0f));
}

void ogl::Camera::rotateAxisY(GLfloat scale)
{
  lookat = glm::rotate(lookat, scale, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 ogl::Camera::mtx() const
{
  return matrix * lookat;
}

