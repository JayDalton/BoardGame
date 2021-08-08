/*#######################################################################
#######################################################################*/
#include "sfml.hpp"

/*#######################################################################
#######################################################################*/
SFML::SFML()
: server(io_service, 30000)
{
  running = true;
  mouseLeftDown = false;
  mouseRightDown = false;
  mouseMiddleDown = false;
  drawMode = 0;

  pFireLine = 0;

  pTexMan = new ogl::TextureManager();
  shapes = new std::vector<ogl::Shape*>();
  objs2d = new std::vector<ogl::Shape*>();
}

/*#######################################################################
#######################################################################*/
bool SFML::OnInit()
{
  sf::Clock c;

  std::cout << std::endl << "Init Window ... ";
  std::cout << (initWindow() ? "OK" : "NIL") << " ";
  std::cout << c.getElapsedTime().asMilliseconds() << "ms";
  c.restart();

  std::cout << std::endl << "Init OpenGL ... ";
  std::cout << (initOpenGL() ? "OK" : "NIL") << " ";
  std::cout << c.getElapsedTime().asMilliseconds() << "ms";
  c.restart();

  std::cout << std::endl << "Init Camera ... ";
  std::cout << (initCamera() ? "OK" : "NIL") << " ";
  std::cout << c.getElapsedTime().asMilliseconds() << "ms";
  c.restart();

  std::cout << std::endl << "Init Lights ... ";
  std::cout << (initLights() ? "OK" : "NIL") << " ";
  std::cout << c.getElapsedTime().asMilliseconds() << "ms";
  c.restart();

  std::cout << std::endl << "Init Textures ... ";
  std::cout << (initTextures() ? "OK" : "NIL") << " ";
  std::cout << c.getElapsedTime().asMilliseconds() << "ms";
  c.restart();

  std::cout << std::endl << "Init Geometry ... ";
  std::cout << (initGeometry() ? "OK" : "NIL") << " ";
  std::cout << c.getElapsedTime().asMilliseconds() << "";
  c.restart();

  std::cout << std::endl << "Init IOServer ... ";
  std::cout << (initIOServer() ? "OK" : "NIL") << " ";
  std::cout << c.getElapsedTime().asMilliseconds() << "ms";
  c.restart();

  return true;
}

/*#######################################################################
#######################################################################*/
bool SFML::initWindow()
{
  window = new sf::Window(
    sf::VideoMode(800, 600),
    "Prototyp",
    sf::Style::Default,
    sf::ContextSettings(32)
    );

  window->setVerticalSyncEnabled(true);
  window->setFramerateLimit(30);
  return true;
}

/*#######################################################################
#######################################################################*/
bool SFML::initOpenGL()
{
  glShadeModel(GL_SMOOTH);                    // shading method: GL_SMOOTH or GL_FLAT

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                   // background color
  glClearDepth(1.0f);                         // 0 is near, 1 is far
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  glEnable(GL_CULL_FACE);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

  //glClearStencil(0);                          // clear stencil buffer
  return true;
}

/*#######################################################################
#######################################################################*/
bool SFML::initLights()
{
  GLfloat mat_ambient[]   = {0.4f, 0.4f, 0.4f, 1.0f};
  GLfloat mat_diffuse[]   = {0.4f, 0.8f, 0.4f, 1.0f};
  GLfloat mat_specular[]  = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat mat_shininess[] = {50.0f};
 
  glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
 
  GLfloat light_ambient[] = {0.5f, 0.5f, 0.5f, 1.0};
  GLfloat light_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
  GLfloat light_specular[] = {0.5f, 0.5f, 0.5f, 1.0f};
  GLfloat light_position[] = {0.0f, 0.0f, 10.0f, 1.0f};
 
  glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
 
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  return true;
}

/*#######################################################################
#######################################################################*/
bool SFML::initCamera()
{
  camera = ogl::Camera(
    glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 1000.0f),
    glm::vec3(0.0f, 0.0f, 8.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f)
  );

  screen = ogl::Camera(
    glm::ortho(-40.0f, 40.0f, -30.0f, 30.0f, 0.1f, 1000.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f)
  );
  return true;
}

/*#######################################################################
#######################################################################*/
int SFML::OnExecute()
{
  std::cout << "########################################" << std::endl;
  std::cout << "               WallPaint                " << std::endl;
  std::cout << "########################################" << std::endl;

  if (OnInit()) {

    sf::Clock round;
    //sf::Clock clock;
    //static unsigned int frames = 0;

    while (running) {

      sf::Event event;

      while (window->pollEvent(event)) {
        OnEvent(event);
      }

      OnReceive();
      OnUpdate(round.getElapsedTime().asSeconds());
      round.restart();
      OnRender();

      //frames++;
      //if (1 < clock.getElapsedTime().asSeconds()) {
      //  std::cout << frames << " fps" << std::endl;
      //  clock.restart();
      //  frames = 0;
      //}
    }

    OnCleanup();
  }
  return 0;
}

/*#######################################################################
#######################################################################*/
void SFML::OnEvent(sf::Event& event)
{
  switch (event.type) {

    case sf::Event::Closed:
      running = false;
      break;

    case sf::Event::Resized:
      break;

    case sf::Event::KeyPressed:
      switch (event.key.code) {

      case sf::Keyboard::Escape:
        running = false;
        break;

      case sf::Keyboard::Up: {
        glm::vec3 tmp = pFireLine->getP2();
        pFireLine->setP2(glm::vec3(tmp.x, tmp.y + 5, tmp.z));
      } break;

      case sf::Keyboard::Down: {
        glm::vec3 tmp = pFireLine->getP2();
        pFireLine->setP2(glm::vec3(tmp.x, tmp.y - 5, tmp.z));
      } break;

      case sf::Keyboard::Left: {
        glm::vec3 tmp = pFireLine->getP2();
        pFireLine->setP2(glm::vec3(tmp.x - 5, tmp.y, tmp.z));
      } break;

      case sf::Keyboard::Right: {
        glm::vec3 tmp = pFireLine->getP2();
        pFireLine->setP2(glm::vec3(tmp.x + 5, tmp.y, tmp.z));
      } break;

        case sf::Keyboard::W:
          camera.rotateAxisX(+10);
          break;

        case sf::Keyboard::A:
          camera.rotateAxisY(-10);
          break;

        case sf::Keyboard::S:
          camera.rotateAxisX(-10);
          break;

        case sf::Keyboard::D:
          camera.rotateAxisY(+10);
          break;

        case sf::Keyboard::V:
          drawMode++;
          switch (drawMode % 3) {
            case 0:
              glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
              glEnable(GL_DEPTH_TEST);
              glEnable(GL_CULL_FACE);
              drawMode = 0;
              break;
            case 1:
              glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
              glDisable(GL_DEPTH_TEST);
              glDisable(GL_CULL_FACE);
              drawMode = 1;
              break;
            case 2:
              glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
              glDisable(GL_DEPTH_TEST);
              glDisable(GL_CULL_FACE);
              drawMode = 2;
              break;
          }
          break;
      }
      break;

    case sf::Event::MouseWheelMoved:
        camera.modDistance(event.mouseWheel.delta * 0.1f);
      break;

    case sf::Event::MouseMoved:
      if (mouseLeftDown) {
        camera.rotateAxisX((float) event.mouseMove.y - mousePosition.y);
        camera.rotateAxisY((float) event.mouseMove.x - mousePosition.x);
        mousePosition = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
      }
      if (mouseRightDown) {
        camera.modDistance(((float) event.mouseMove.y - mousePosition.y) * 0.1f);
        mousePosition = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
      }
      break;

    case sf::Event::MouseButtonPressed:
      mousePosition = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
      switch (event.mouseButton.button) {
        case sf::Mouse::Left:
          mouseLeftDown = true;
          break;
        case sf::Mouse::Right:
          mouseRightDown = true;
          break;
        case sf::Mouse::Middle:
          mouseMiddleDown = true;
          break;
      }
      break;

    case sf::Event::MouseButtonReleased:
      mousePosition = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
      switch (event.mouseButton.button) {
        case sf::Mouse::Left:
          mouseLeftDown = false;
          break;
        case sf::Mouse::Right:
          mouseRightDown = false;
          break;
        case sf::Mouse::Middle:
          mouseMiddleDown = false;
          break;
      }
      break;

  }

}

/*#######################################################################
#######################################################################*/
void SFML::OnReceive()
{
  std::string msg;
  if (server.get_message(msg)) {
    std::cout << "Server: " << msg << std::endl;
    glm::vec3 tmp = pFireLine->getP2();

    if (msg.compare("up") == 0) {
      pFireLine->setP2(glm::vec3(tmp.x, tmp.y + 5, tmp.z));
    }
    if (msg.compare("left") == 0) {
      pFireLine->setP2(glm::vec3(tmp.x - 5, tmp.y, tmp.z));
    }
    if (msg.compare("right") == 0) {
      pFireLine->setP2(glm::vec3(tmp.x + 5, tmp.y, tmp.z));
    }
    if (msg.compare("down") == 0) {
      pFireLine->setP2(glm::vec3(tmp.x, tmp.y - 5, tmp.z));
    }
    if (msg.compare("fire") == 0) {
      //pFireLine->setP2(glm::vec3(tmp.x, tmp.y + 5, tmp.z));
    }
  }
}

/*#######################################################################
#######################################################################*/
void SFML::OnUpdate(GLfloat delta)
{
  for (std::vector<ogl::Shape*>::iterator it = shapes->begin(); it != shapes->end(); ++it) {
    (*it)->update(delta);
  }
}

/*#######################################################################
#######################################################################*/
void SFML::OnRender()
{
  sf::Vector2u windowSize = window->getSize();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  // MainWindow
  glViewport(0, 0, windowSize.x, windowSize.y);
  for (std::vector<ogl::Shape*>::iterator it = shapes->begin(); it != shapes->end(); ++it) {
    glLoadMatrixf(glm::value_ptr(camera.mtx() * (*it)->getMatrix()));
    (*it)->render();
  }

  // ViewPort buttom-left
  glViewport(0, 0, windowSize.x / 4, windowSize.y / 4);
  for (std::vector<ogl::Shape*>::iterator it = objs2d->begin(); it != objs2d->end(); ++it) {
    glLoadMatrixf(glm::value_ptr(screen.mtx() * (*it)->getMatrix()));
    (*it)->render();
  }

  window->display();
}

/*#######################################################################
#######################################################################*/
bool SFML::initIOServer()
{
  // Startet den Thread für IOService aller Server
  boost::thread t(boost::bind(&SFML::runIOService, this));
  return true;
}

/*#######################################################################
#######################################################################*/
void SFML::runIOService()
{
  try
  {
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}

/*#######################################################################
#######################################################################*/
bool SFML::initTextures()
{
  bool result = false;

  if (
    //pTexMan->loadDirectory("Textures") 
    pTexMan->loadDirectory("Textures/walls") &&
	pTexMan->loadDirectory("Textures/cross") &&
	pTexMan->loadFilename("Textures/FontTextureArial32u.tga")
	) {
    result = true;
  }

  return result;
}

/*#######################################################################
#######################################################################*/
bool SFML::initGeometry()
{
  ogl::Shape* pShape = 0;

  // FireLine
  ogl::Line* pLine = new ogl::Line(
    glm::vec3(0.0f, 0.0f, 0.0f), 
    glm::vec3(0.0f, 0.0f, -50.0f), 
    1.0f, 0.0f, 0.0f
  );
  pFireLine = pLine;
  shapes->push_back(pLine);

  // Wand
  ogl::Wall* pWall = new ogl::Wall(80.0f, 40.0f, 800, 400);
  pWall->setMatrix(glm::translate(-40.0f, -20.0f, -50.0f));
  pWall->setForeTexture(pTexMan->getTexture("roomwall03.tga"));
  shapes->push_back(pWall);

  // Cross
  ogl::Area* pArea = new ogl::Area(10.0f, 10.0f, pTexMan->getTexture("cross01.tga"));
  pArea->setMatrix(glm::translate(0.0f, 0.0f, -10.0f));
  //shapes->push_back(pArea);

  // Ball
  ogl::IcoSphere* pSphere = new ogl::IcoSphere();
  shapes->push_back(pSphere);

  return true;
}

/*#######################################################################
#######################################################################*/
void SFML::renderContent()
{
}

/*#######################################################################
#######################################################################*/
void SFML::updateContent()
{
}

/*#######################################################################
#######################################################################*/
void SFML::OnCleanup()
{
}
