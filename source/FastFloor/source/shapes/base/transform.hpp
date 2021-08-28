#pragma once

#include <chrono>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>

namespace ogl 
{
   using Duration = std::chrono::milliseconds;
   using StopClock = std::chrono::steady_clock;
   using TimePoint = StopClock::time_point;

   class Transform
   {
   public:
      Transform();
      Transform(const Transform& trans);
      Transform& operator=(const Transform& trans);

      void setRotX(float angle = 360.0f);
      void setRotY(float angle = 360.0f);
      void setRotZ(float angle = 360.0f);

      void movePath(std::vector<glm::vec3> vertices, float time);
      void setPath(std::vector<glm::vec3> vertices);
      void setTime(float time);

      void update(Duration delta);

      void setPathAnimation();
      void setRingAnimation();

      void start();
      void pause();
      void follo();
      void abort();

      glm::mat4 getMatrix() const;
      void setMatrix(glm::mat4 matrix);

      bool isActive();

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

   protected:
      glm::mat4 matrix;

   private:
      bool animate;
      bool looping;

      float duration;
      float timestamp;
      float animspeed;

      unsigned int lstIdx1;
      unsigned int lstIdx2;

      std::vector<glm::vec3> movepath;
      float rot_X_duration;
      float rot_Y_duration;
      float rot_Z_duration;
      float rot_X_scale;
      float rot_Y_scale;
      float rot_Z_scale;

   private:
      glm::mat4 rotateX(float scale);
      glm::mat4 rotateY(float scale);
      glm::mat4 rotateZ(float scale);
   };
}
