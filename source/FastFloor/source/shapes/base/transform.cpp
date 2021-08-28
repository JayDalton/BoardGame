#include "transform.hpp"


#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <SDL2/SDL_opengl.h>

ogl::Transform::Transform()
  : matrix(1.0f), animate(false), looping(false), duration(1.0f), timestamp(0),
  animspeed(1.0f), lstIdx1(0), lstIdx2(1)
{
  rot_X_duration = 0;
  rot_Y_duration = 0;
  rot_Z_duration = 0;
  rot_X_scale = 0;
  rot_Y_scale = 0;
  rot_Z_scale = 0;

  //gtx::
  //glm::quaternion::angleAxis(glm::degrees(RotationAngle), RotationAxis);
}

ogl::Transform::Transform(const Transform& original)
{
}

ogl::Transform& ogl::Transform::operator=(const Transform& original)
{
  if(this != &original) {

  }
  return *this;
}

void ogl::Transform::setMatrix(glm::mat4 mtx)
{
  matrix = mtx;
}

glm::mat4 ogl::Transform::getMatrix() const
{
  return matrix;
}

void ogl::Transform::update(Duration delta)
{
  //if (animate && 1 < movepath.size()) 
  //{
  //  timestamp += delta * animspeed;
  //  GLfloat scale = timestamp / duration;

  //  glm::vec3 p1 (movepath[lstIdx1]);
  //  glm::vec3 p2 (movepath[lstIdx2]);
  //  glm::vec3 p0 (p1 + (p2 - p1) * scale);

  //  matrix = glm::translate(p0)
  //    * rotateX(delta)
  //    * rotateY(delta)
  //    * rotateZ(delta)
  //    //      * glm::scale(glm::sin(scale * 3.14f), glm::sin(scale * 3.14f), glm::sin(scale * 3.14f));
  //    ;

  //  if (duration <= timestamp) {
  //    timestamp = 0;
  //    if (looping) {
  //      lstIdx1 = lstIdx1 < movepath.size() - 1 ? lstIdx1 + 1 : 0;
  //      lstIdx2 = lstIdx2 < movepath.size() - 1 ? lstIdx2 + 1 : 0;
  //    } else {
  //      if (lstIdx1 < movepath.size() - 2) {
  //        lstIdx1++;
  //        lstIdx2++;
  //      } else {
  //        animate = false;
  //      }
  //    }
  //  }
  //}
}

void ogl::Transform::setRotX(GLfloat duration)
{
  rot_X_duration = duration;
}

void ogl::Transform::setRotY(GLfloat duration)
{
  rot_Y_duration = duration;
}

void ogl::Transform::setRotZ(GLfloat duration)
{
  rot_Z_duration = duration;
}

glm::mat4 ogl::Transform::rotateX(GLfloat delta)
{
  GLfloat scale = 0;
  if (0 < rot_X_duration) {
    rot_X_scale += delta;
    scale = rot_X_scale / rot_X_duration;
    if (rot_X_duration <= rot_X_scale) {
      rot_X_scale = 0;
    }
  }
  return glm::rotate(scale * 360.0f, glm::vec3{ 1.0f, 0.0f, 0.0f });
}

glm::mat4 ogl::Transform::rotateY(GLfloat delta)
{
  GLfloat scale = 0;
  glm::mat4 result (1.0f);
  if (0 < rot_Y_duration) {
    rot_Y_scale += delta;
    scale = rot_Y_scale / rot_Y_duration;
    if (rot_Y_duration <= rot_X_scale) {
      rot_Y_scale = 0;
    }
  }
  return glm::rotate(scale * 360.0f, glm::vec3{ 0.0f, 1.0f, 0.0f });
}

glm::mat4 ogl::Transform::rotateZ(GLfloat delta)
{
  GLfloat scale = 0;
  glm::mat4 result (1.0f);
  if (0 < rot_Z_duration) {
    rot_Z_scale += delta;
    scale = rot_Z_scale / rot_Z_duration;
    if (rot_Z_duration <= rot_Z_scale) {
      rot_Z_scale = 0;
    }
  }
  return glm::rotate(scale * 360.0f, glm::vec3{ 0.0f, 0.0f, 1.0f });
}

void ogl::Transform::start()
{
  //timestamp = 0;
  animate = true;
}

void ogl::Transform::abort()
{
  animate = false;
}

void ogl::Transform::setPath(std::vector<glm::vec3> vertices)
{
  movepath = vertices;
}

void ogl::Transform::setTime(GLfloat time)
{
  duration = time;
}

bool ogl::Transform::isActive()
{
  return animate;
}
