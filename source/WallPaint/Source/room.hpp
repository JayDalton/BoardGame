/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#ifndef OGL_ROOM_HPP
#define OGL_ROOM_HPP

#include <map>
#include <vector>
#include <iostream>

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>

#include <SFML/OpenGL.hpp>

#include "rectangle.hpp"
#include "area.hpp"
#include "cube.hpp"
#include "wall.hpp"

namespace ogl {

  class Room
  {
    private:
      GLfloat width;
      GLfloat height;
      GLfloat depth;
      //std::vector<Area*> areas;
      //std::vector<Cube*> cubes;
      //std::map<std::string, Wall*> walls;
      //std::map<std::string, Area*> holes;
      //bool isLeftRoom;

    public:
      Room(GLfloat u = 1, GLfloat v = 1, GLfloat w = 1);
      ~Room();
      Room(const Room& room);
      Room& operator=(const Room& room);

      bool setForeTexture(std::string wall, const Texture* tex);
      bool setBackTexture(std::string wall, const Texture* tex);
      bool setHairTexture(const Texture* tex);
      bool setInfoTexture(const Texture* tex);
      bool setMaskHole(std::string wall, GLint x, GLint y, const Texture *tex);
      bool setMaskFill(std::string wall);

      GLfloat getFillInfo() const;

      void addArea(GLfloat u, GLfloat v, Texture* tex);
      void addCube(GLfloat t, Texture* fore, Texture* back);

      void remArea();
      void remCube();
      void remAreas();
      void remCubes();

      bool intersect(glm::vec3 P1, glm::vec3 P2, glm::vec3 &PI);
      bool strike(glm::vec3 P1, glm::vec3 P2, Texture *tex);
      void trans(glm::mat4 matrix);

      void update(double d_time);

      void draw();
      void drawAreas();
      void drawCubes();

      void resetWalls();
      bool target(glm::vec3 P1, glm::vec3 P2);

      void front(Texture* tex);

      std::vector<Cube*> getCubes();
      std::vector<Area*> getAreas();
      std::map<std::string, Wall*> getWalls() const;
      std::map<std::string, Area*> getHoles() const;

      void startAnims();
      void stopAnims();

  };

}

#endif
