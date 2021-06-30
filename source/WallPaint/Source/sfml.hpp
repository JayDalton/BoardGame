#ifndef SFML_APPLICATION_HPP
#define SFML_APPLICATION_HPP

#include <map>
#include <string>
#include <vector>
#include <iostream>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include <glm/glm.hpp>
//#include <glm/ext.hpp>
#include <glm/gtc/random.hpp>
//#include <glm/gtc/quaternion.hpp>
//#include <glm/gtx/quaternion.hpp>

#include "serverudp.hpp"
#include "servertcp.hpp"
#include "camera.hpp"
#include "shape.hpp"
#include "line.hpp"
#include "polyline.hpp"
#include "rectangle.hpp"
#include "icosphere.hpp"
#include "cuboid.hpp"
#include "area.hpp"
#include "wall.hpp"
#include "cube.hpp"
#include "ball.hpp"
#include "texture.hpp"
#include "tgaloader.hpp"
#include "texturemanager.hpp"
#include "objmodel.hpp"
#include "texmodel.hpp"
#include "textline2d.hpp"

class SFML {

  private:
    bool running;
    bool mouseLeftDown;
    bool mouseRightDown;
    bool mouseMiddleDown;
    sf::Vector2i mousePosition;
    GLuint drawMode;
    sf::Window* window;

    std::vector<ogl::Shape*>* shapes;
    std::vector<ogl::Shape*>* objs2d;

    boost::asio::io_service io_service;
    ogl::UDPServer server;

    ogl::TextureManager* pTexMan;
    ogl::Camera camera;
    ogl::Camera screen;
    ogl::Line* pFireLine;

  public:
    SFML();

    int OnExecute();
    bool OnInit();
    void OnEvent(sf::Event& Event);
    void OnLoop();
    void OnUpdate(GLfloat delta);
    void OnRender();
    void OnCamera();
    void OnReceive();
    void OnCleanup();

  private:
    bool initWindow();
    bool initOpenGL();
    bool initCamera();
    bool initLights();
    bool initViews();
    bool initTextures();
    bool initGeometry();
    bool initIOServer();
    void runIOService();

    void renderContent();
    void updateContent();
};

#endif