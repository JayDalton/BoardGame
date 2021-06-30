/*###############################################################################
 Kodierung: UTF-8 ohne BOM - äüö
 ###############################################################################*/

#include "room.hpp"

//############################################################################
/**
 */
//############################################################################
ogl::Room::Room(GLfloat u, GLfloat v, GLfloat w)
  : width(u), height(v), depth(w)
{

  //areas = std::vector<Area*>();
  //cubes = std::vector<Cube*>();
  //walls = std::map<std::string, Wall*>();
  //holes = std::map<std::string, Area*>();

  //walls["top"] = new Wall(width, depth, 600, 480);
  //walls["top"]->Rectangle::setMatrix(
  //  glm::translate(-width / 2, height, -depth)
  //  * glm::rotate(90.0f, 1.0f, 0.0f, 0.0f)
  //);

  //walls["back"] = new Wall(width, height, 600, 480);
  //walls["back"]->Rectangle::setMatrix(
  //  glm::translate(-width / 2, 0.0f, -depth)
  //);

  //walls["left"] = new Wall(depth, height, 600, 480);
  //walls["left"]->Rectangle::setMatrix(
  //  glm::translate(-width / 2, 0.0f, 0.0f)
  //  * glm::rotate(90.0f, 0.0f, 1.0f, 0.0f)
  //);

  //holes["leftone"] = new Area(depth * 0.8f, height * 0.3f, 1000, 800, 0.0f, 0.0f, 0.0f, 0.0f);
  //holes["leftone"]->Rectangle::setMatrix(
  //  glm::translate(-width / 2 - 0.2f, height * 0.6f, -depth * 0.1f)
  //  * glm::rotate(90.0f, 0.0f, 1.0f, 0.0f)
  //);

  //holes["lefttwo"] = new Area(depth * 0.8f, height * 0.3f, 1000, 800, 0.0f, 0.0f, 0.0f, 0.0f);
  //holes["lefttwo"]->Rectangle::setMatrix(
  //  glm::translate(-width / 2 - 0.2f, height * 0.1f, -depth * 0.1f)
  //  * glm::rotate(90.0f, 0.0f, 1.0f, 0.0f)
  //);

  //walls["right"] = new Wall(depth, height, 600, 480);
  //walls["right"]->Rectangle::setMatrix(
  //  glm::translate(width / 2, 0.0f, -depth)
  //  * glm::rotate(-90.0f, 0.0f, 1.0f, 0.0f)
  //);

  //holes["rightone"] = new Area(depth * 0.8f, height * 0.3f, 1000, 800, 0.0f, 0.0f, 0.0f, 0.0f);
  //holes["rightone"]->Rectangle::setMatrix(
  //  glm::translate(width / 2 + 0.2f, height * 0.6f, -depth + depth * 0.1f)
  //  * glm::rotate(-90.0f, 0.0f, 1.0f, 0.0f)
  //);

  //holes["righttwo"] = new Area(depth * 0.8f, height * 0.3f, 1000, 800, 0.0f, 0.0f, 0.0f, 0.0f);
  //holes["righttwo"]->Rectangle::setMatrix(
  //  glm::translate(width / 2 + 0.2f, height * 0.1f, -depth + depth * 0.1f)
  //  * glm::rotate(-90.0f, 0.0f, 1.0f, 0.0f)
  //);

  //holes["front"] = new Area(width, height, 1000, 800, 0.0f, 0.0f, 0.0f, 0.0f);
  //holes["front"]->Rectangle::setMatrix(
  //  glm::translate(-width / 2, 0.0f, 0.0f)
  //);

  //holes["cross"] = new Area(10.0f, 10.0f, 150, 150, 0.0f, 0.0f, 0.0f, 0.0f);
  //holes["cross"]->Rectangle::setMatrix(
  //  glm::translate(0.0f, height / 2, 0.1f)
  //);

  //holes["screen"] = new Area(width / 2, height / 2, 100, 100, 0.0f, 0.0f, 0.0f, 0.0f);
  //holes["screen"]->Rectangle::setMatrix(
  //  glm::translate(-width / 4, height / 4, 0.2f)
  //);
}

//############################################################################
/**
*/
//############################################################################
ogl::Room::~Room()
{
  //for (std::map<std::string, Wall*>::iterator it = walls.begin(); it != walls.end(); ++it) {
  //  delete it->second;
  //}

  //for (std::map<std::string, Area*>::iterator it = holes.begin(); it != holes.end(); ++it) {
  //  delete it->second;
  //}
  //for (std::vector<Cube*>::iterator it = cubes.begin(); it != cubes.end(); ++it) {
  //  delete *it;
  //}

  //for (std::vector<Area*>::iterator it = areas.begin(); it != areas.end(); ++it) {
  //  delete *it;
  //}
}

//############################################################################
/**
*/
//############################################################################
ogl::Room::Room(const ogl::Room& original)
{
  width = original.width;
  height = original.height;
  depth = original.depth;
  //walls = original.walls;
  //holes = original.holes;
  //areas = original.areas;
  //cubes = original.cubes;
  //isLeftRoom = original.isLeftRoom;
}

//############################################################################
/**
*/
//############################################################################
ogl::Room& ogl::Room::operator=(const ogl::Room& original)
{
  if(this != &original) {
    width = original.width;
    height = original.height;
    depth = original.depth;
    //walls = original.walls;
    //holes = original.holes;
    //areas = original.areas;
    //cubes = original.cubes;
    //isLeftRoom = original.isLeftRoom;
  }
  return *this;
}

//############################################################################
/**
*/
//############################################################################
bool ogl::Room::setForeTexture(std::string wall, const ogl::Texture* tex)
{
  bool result = false;
  //if (0 < walls.count(wall) && tex != 0) {
  //  walls[wall]->setForeTexture(tex);
  //  result = true;
  //}
  return result;
}

//############################################################################
/**
*/
//############################################################################
bool ogl::Room::setBackTexture(std::string wall, const ogl::Texture* tex)
{
  bool result = false;
  //if (0 < walls.count(wall) && tex != 0) {
  //  walls[wall]->setBackTexture(tex);
  //  result = true;
  //}
  return result;
}

//############################################################################
/**
*/
//############################################################################
bool ogl::Room::setMaskHole(std::string wall, GLint x, GLint y, const ogl::Texture *tex)
{
  bool result = false;
  //if (0 < walls.count(wall) && tex != 0) {
  //  walls[wall]->Texture::draw(x, y, tex);
  //  result = true;
  //}
  return result;
}

//############################################################################
/**
*/
//############################################################################
bool ogl::Room::setHairTexture(const ogl::Texture* tex)
{
  bool result = false;
  //if (0 < holes.count("cross") && 0 < tex) {
  //  holes["cross"]->Texture::operator=(*tex);
  //  holes["cross"]->Texture::bind();
  //  result = true;
  //}
  return result;
}

//############################################################################
/**
*/
//############################################################################
bool ogl::Room::setInfoTexture(const ogl::Texture* tex)
{
  bool result = false;
  //if (0 < holes.count("screen") && 0 < tex) {
  //  holes["screen"]->Texture::operator=(*tex);
  //  holes["screen"]->Texture::bind();
  //  result = true;
  //}
  return result;
}

//############################################################################
/**
*/
//############################################################################
void ogl::Room::addArea(GLfloat u, GLfloat v, ogl::Texture* tex)
{
  //Area* area = new Area(u, v, tex);

  //glm::vec3 p1 (walls["top"]->Rectangle::getBase());
  //glm::vec3 p2 (walls["left"]->Rectangle::getBase());
  //glm::vec3 p3 (walls["right"]->Rectangle::getBase());

  //GLfloat x1 = p2.x, x2 = p3.x;
  //GLfloat y1 = p2.y, y2 = p1.y;
  //GLfloat z1 = p2.z, z2 = p3.z;

  //std::vector<glm::vec3> path;
  //for (unsigned int i = 0; i < 150; i++) {
  //  GLfloat x = glm::linearRand(x1, x2);
  //  GLfloat y = glm::linearRand(y1, y2);
  //  GLfloat z = glm::linearRand(z1, z2);
  //  path.push_back(glm::vec3(x, y, z));
  //}

  ////area->Animation::setTime(glm::linearRand(5.0f, 7.0f));
  ////area->Animation::setPath(path);
  //areas.push_back(area);
}

//############################################################################
/**
*/
//############################################################################
void ogl::Room::remArea()
{
  //if (0 < areas.size()) {
  //  areas.pop_back();
  //}
}

//############################################################################
/**
*/
//############################################################################
void ogl::Room::remAreas()
{
  //for (std::vector<Area*>::iterator it = areas.begin(); it != areas.end(); ++it) {
  //  delete *it;
  //}
  //areas.clear();
}

//############################################################################
/**
*/
//############################################################################
void ogl::Room::remCube()
{
  //if (0 < cubes.size()) {
  //  cubes.pop_back();
  //}
}

//############################################################################
/**
*/
//############################################################################
void ogl::Room::remCubes()
{
  //for (std::vector<Cube*>::iterator it = cubes.begin(); it != cubes.end(); ++it) {
  //  delete *it;
  //}
  //cubes.clear();
}

//############################################################################
/**
*/
//############################################################################
void ogl::Room::addCube(GLfloat t, ogl::Texture* fore, ogl::Texture* back)
{
  Cube* cube = new Cube(t, t, t, 1000, 800);
  cube->setForeTexture(fore);
  cube->setBackTexture(back);

  glm::vec3 p1 (walls["top"]->Rectangle::getBase());
  glm::vec3 p2 (walls["left"]->Rectangle::getBase());
  glm::vec3 p3 (walls["right"]->Rectangle::getBase());

  GLfloat x1 = p2.x, x2 = p3.x;
  GLfloat y1 = p2.y, y2 = p1.y;
  GLfloat z1 = p2.z, z2 = p3.z;

  std::vector<glm::vec3> path;
  for (unsigned int i = 0; i < 150; i++) {
    GLfloat x = glm::linearRand(x1, x2);
    GLfloat y = glm::linearRand(y1, y2);
    GLfloat z = glm::linearRand(z1, z2);
    path.push_back(glm::vec3(x, y, z));
  }

  //cube->Animation::setTime(glm::linearRand(3.0f, 5.0f));
  //cube->Animation::setPath(path);
  //cube->Animation::setRotX(8.0f);
  //cube->Animation::setRotY(2.5f);
  cubes.push_back(cube);
}

//############################################################################
/**
*/
//############################################################################
bool ogl::Room::setMaskFill(std::string wall)
{
  bool result = false;
  if (0 < walls.count(wall)) {
    walls[wall]->Texture::fill();
    result = true;
  }
  return result;
}

//############################################################################
/**
*/
//############################################################################
void ogl::Room::resetWalls()
{
  for (std::map<std::string, Wall*>::const_iterator it = walls.begin(); it != walls.end(); it++) {
    it->second->Texture::fill(1.0f, 1.0f, 1.0f, 1.0f);
    it->second->Texture::bind();
  }
}

//############################################################################
/**
*/
//############################################################################
GLfloat ogl::Room::getFillInfo() const
{
  GLfloat result = 0;
  for (std::map<std::string, Wall*>::const_iterator it = walls.begin(); it != walls.end(); it++) {
    result += it->second->Texture::getAlphaInfo();
  }
  return result / walls.size();
}

//############################################################################
/**
 */
//############################################################################
void ogl::Room::draw()
{
  if (isLeftRoom) {
    walls["top"]->render();
    walls["back"]->render();
    walls["right"]->render();
    for (std::vector<Cube*>::iterator itr = cubes.begin(); itr != cubes.end(); ++itr) {
      (*itr)->render();
    }

    for (std::vector<Area*>::iterator itr = areas.begin(); itr != areas.end(); ++itr) {
      (*itr)->render();
    }
    holes["leftone"]->render();
    holes["lefttwo"]->render();
    walls["left"]->render();
    holes["cross"]->render();
    holes["screen"]->render();

  } else {

    walls["top"]->render();
    walls["back"]->render();
    walls["left"]->render();
    for (std::vector<Cube*>::iterator itr = cubes.begin(); itr != cubes.end(); ++itr) {
      (*itr)->render();
    }

    for (std::vector<Area*>::iterator itr = areas.begin(); itr != areas.end(); ++itr) {
      (*itr)->render();
    }
    holes["rightone"]->render();
    holes["righttwo"]->render();
    walls["right"]->render();
    holes["cross"]->render();
    holes["screen"]->render();
  }

}

void ogl::Room::drawCubes()
{
  for (std::vector<Cube*>::iterator itr = cubes.begin(); itr != cubes.end(); ++itr) {
    (*itr)->render();
  }
}

void ogl::Room::drawAreas()
{
  for (std::vector<Area*>::iterator itr = areas.begin(); itr != areas.end(); ++itr) {
    (*itr)->render();
  }
}

//############################################################################
/**
 */
//############################################################################
void ogl::Room::trans(glm::mat4 matrix)
{
  //for (std::map<std::string, Wall*>::iterator it = walls.begin(); it != walls.end(); it++) {
  //  it->second->Rectangle::addTrans(matrix);
  //}

  //for (std::map<std::string, Area*>::iterator it = holes.begin(); it != holes.end(); it++) {
  //  it->second->Rectangle::addTrans(matrix);
  //}

  //for (std::vector<Area*>::iterator it = areas.begin(); it != areas.end(); it++) {
  //  (*it)->Rectangle::addTrans(matrix);
  //}

  //for (std::vector<Cube*>::iterator it = cubes.begin(); it != cubes.end(); it++) {
  //  (*it)->Cuboid::addTrans(matrix);
  //}
}

//############################################################################
/**
*/
//############################################################################
bool ogl::Room::intersect(glm::vec3 P1, glm::vec3 P2, glm::vec3 &PI)
{
  bool result = false;
  glm::vec3 P0 (0.0f);
  for (std::map<std::string, Wall*>::iterator it = walls.begin(); !result && it != walls.end(); it++) {
    if(it->second->Rectangle::intersect(P1, P2, P0)) {

      std::vector<glm::vec3> list (it->second->Rectangle::vertices());

      glm::vec3 vB (list.at(0));
      glm::vec3 vU (list.at(1) - list.at(0));
      glm::vec3 vV (list.at(3) - list.at(0));

      PI = vB + vU * P0.y + vV * P0.z;

      result = true;
    }
  }
  return result;
}

//############################################################################
/**
 */
//############################################################################
bool ogl::Room::strike(glm::vec3 P1, glm::vec3 P2, ogl::Texture *tex)
{
  bool result = false;
  glm::vec3 PI (0.0f);
  for (std::map<std::string, Wall*>::iterator it = walls.begin(); it != walls.end(); it++) {
    if(it->second->Rectangle::intersect(P1, P2, PI)) {
      GLuint texW (it->second->Texture::getWidth());
      GLuint texH (it->second->Texture::getHeight());
      it->second->Texture::draw(texW * PI.y, texH * PI.z, tex);
      it->second->bind();
      result = true;
    }
  }
  return result;
}

//############################################################################
/**
 */
//############################################################################
void ogl::Room::front(ogl::Texture* tex)
{
  holes["front"]->Texture::operator=(*tex);
  holes["front"]->Texture::bind();
}

//############################################################################
/**
 */
//############################################################################
bool ogl::Room::target(glm::vec3 P1, glm::vec3 P2)
{
  bool result = false;
  glm::vec3 PI(0.0f);

  if (0 < holes.count("front") && 0 < holes.count("cross"))  {

    if(holes["front"]->Rectangle::intersect(P1, P2, PI)) {

      glm::vec3 base (holes["front"]->Rectangle::getBase());
      GLuint recW (holes["front"]->Rectangle::getWidth());
      GLuint recH (holes["front"]->Rectangle::getHeight());

      GLuint croW (holes["cross"]->Rectangle::getWidth());
      GLuint croH (holes["cross"]->Rectangle::getHeight());

      holes["cross"]->Rectangle::setMatrix(
      glm::translate(
        base.x + PI.y * recW - croW / 2,
        base.y + PI.z * recH - croH / 2,
        base.z
      )
      );
      result = true;
    }
  }

  return result;
}

//############################################################################
/**
 */
//############################################################################
void ogl::Room::update(double d_time)
{
  //for (std::vector<Cube*>::iterator itr = cubes.begin(); itr != cubes.end(); ++itr) {
  //(*itr)->Animation::update(d_time);
  //(*itr)->setMatrix((*itr)->Animation::mtx());
  //}

  //for (std::vector<Area*>::iterator itr = areas.begin(); itr != areas.end(); ++itr) {
  //  (*itr)->Animation::update(d_time);
  //  (*itr)->setMatrix((*itr)->Animation::mtx());
  //}
}

//############################################################################
/**
 */
//############################################################################
void ogl::Room::startAnims()
{
  for (std::vector<Cube*>::iterator itr = cubes.begin(); itr != cubes.end(); ++itr) {
    (*itr)->Animation::start();
  }

  for (std::vector<Area*>::iterator itr = areas.begin(); itr != areas.end(); ++itr) {
    (*itr)->Animation::start();
  }
}

//############################################################################
/**
 */
//############################################################################
void ogl::Room::stopAnims()
{
  for (std::vector<Cube*>::iterator itr = cubes.begin(); itr != cubes.end(); ++itr) {
    (*itr)->Animation::stop();
  }

  for (std::vector<Area*>::iterator itr = areas.begin(); itr != areas.end(); ++itr) {
  (*itr)->Animation::stop();
  }
}

std::vector<ogl::Cube*> ogl::Room::getCubes()
{
  return cubes;
}

std::vector<ogl::Area*> ogl::Room::getAreas()
{
  return areas;
}

std::map<std::string, ogl::Wall*> ogl::Room::getWalls() const
{
  return walls;
}

std::map<std::string, ogl::Area*> ogl::Room::getHoles() const
{
  return holes;
}
