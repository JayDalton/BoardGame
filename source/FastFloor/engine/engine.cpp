#include "engine.h"

#include "objects/shapes/line.hpp"
#include "objects/shapes/cuboid.hpp"
#include "objects/shapes/rectangle.hpp"


GameEngine::GameEngine(std::string_view title)
   : m_title(title)
{

}

bool GameEngine::construct(int x, int y, int w, int h)
{
   using std::cout;
   using std::cerr;
   using std::endl;

   auto tp1 = std::chrono::steady_clock::now();

   if (auto system = sdl2::make_sdlsystem(SDL_INIT_VIDEO | SDL_INIT_TIMER))
   {
      m_system = std::move(system);
      cout << "init system " << tp1 - std::chrono::steady_clock::now();
   }
   else
   {
      cerr << "Error creating SDL2 system: " << SDL_GetError() << endl;
      return false;
   }

   /* Setting up OpenGL version and profile details for context creation */
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);   

   Uint32 windowFlags{ SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL };

   if (auto win = sdl2::make_window(m_title.data(), 
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      w, h, windowFlags))
   {
      m_window = std::move(win); // Context ???
      SDL_GLContext Context = SDL_GL_CreateContext(m_window.get());
      
      /* Loading Extensions */
      glewExperimental = GL_TRUE;
      if (glewInit())
      {
         cerr << "GLEW init failed" << endl;
         return false;
      }
   }
   else
   {
      cerr << "Error creating window: " << SDL_GetError() << endl;
      return false;
   }

   Uint32 renderFlags{ SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC };

   if (auto ren = sdl2::make_renderer(m_window.get(), -1, renderFlags))
   {
      m_render = std::move(ren);
   }
   else
   {
      cerr << "Error creating renderer: " << SDL_GetError() << endl;
      return false;
   }

   initCamera();
   initLights();
   initGeometry();

   return true;
}

void GameEngine::setWindowTitle(std::string label)
{
   SDL_SetWindowTitle(m_window.get(), 
      std::format("{} {}", m_title, label).c_str());
}

void GameEngine::start()
{
   using std::cerr;
   using std::endl;

   auto file = SDL_RWFromFile("img/grumpy-cat.bmp", "rb");
   if (file == nullptr) {
      cerr << "Error reading file: " << SDL_GetError() << endl;
      return;
   }

   auto bmp = sdl2::make_bmp(file);
   if (!bmp) {
      cerr << "Error creating surface: " << SDL_GetError() << endl;
      return;
   }

   auto tex = sdl2::make_texture(m_render.get(), bmp.get());
   if (!tex) {
      cerr << "Error creating texture: " << SDL_GetError() << endl;
      return;
   }

   auto getDuration = [](const StopClock::time_point& start) {
      return std::chrono::duration_cast<Duration>(StopClock::now() - start);
   };

   m_timer = StopClock::now();

   // annimation loop
   while (m_running)
   {
      SDL_Event event;
      while (SDL_PollEvent(&event))
      {
         OnEvent(event);
      }

      OnReceive(); // io server

      updateUser();

      OnUpdate(getDuration(m_timer));

      OnRender();

      //glViewport(0, 0, 600, 400);
      //glClearColor(1.f, 0.f, 1.f, 0.f);
      //glClear(GL_COLOR_BUFFER_BIT);

      SDL_GL_SwapWindow(m_window.get());

      using namespace std::literals;

      m_frames++;
      if (1s < getDuration(m_timer))
      {
         setWindowTitle(std::format(" FPS {:5}", m_frames));
         std::cout << m_frames << " fps" << std::endl;
         m_timer = StopClock::now();
         m_frames = 0;
      }

      //// calculates to 60 fps
      //SDL_Delay(1000 / 60);
   }

}

void GameEngine::OnEvent(const SDL_Event& event)
{
   switch (event.type)
   {

   case SDL_QUIT:
      // handling of close button
      m_running = false;
      break;

   case SDL_KEYDOWN:
      // keyboard API for key pressed
      switch (event.key.keysym.scancode) {
      case SDL_SCANCODE_ESCAPE:
         m_running = false;
         return;
      case SDL_SCANCODE_W:
      case SDL_SCANCODE_UP:
         break;
      case SDL_SCANCODE_A:
      case SDL_SCANCODE_LEFT:
         break;
      case SDL_SCANCODE_S:
      case SDL_SCANCODE_DOWN:
         break;
      case SDL_SCANCODE_D:
      case SDL_SCANCODE_RIGHT:
         break;
      default:
         break;
      }
   }

}

void GameEngine::OnReceive()
{

}

void GameEngine::OnUpdate(Duration duration)
{

}

void GameEngine::OnRender()
{
   auto [width, height] = getWindowSize();
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

   // MainWindow
   glViewport(0, 0, width, height);
   for (auto& shape : m_shapes) 
   {
      glLoadMatrixf(glm::value_ptr(m_camera.mtx() * shape->getMatrix()));
      shape->render();
   }

   //// ViewPort buttom-left
   //glViewport(0, 0, windowSize.x / 4, windowSize.y / 4);
   //for (std::vector<ogl::Shape*>::iterator it = objs2d->begin(); it != objs2d->end(); ++it) {
   //   glLoadMatrixf(glm::value_ptr(screen.mtx() * (*it)->getMatrix()));
   //   (*it)->render();
   //}

   //window->display();

}

void GameEngine::initCamera()
{
   m_camera = ogl::Camera(
      glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 1000.0f),
      glm::vec3(0.0f, 0.0f, 8.0f),
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(0.0f, 1.0f, 0.0f)
   );

   m_screen = ogl::Camera(
      glm::ortho(-40.0f, 40.0f, -30.0f, 30.0f, 0.1f, 1000.0f),
      glm::vec3(0.0f, 0.0f, 1.0f),
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(0.0f, 1.0f, 0.0f)
   );
}

void GameEngine::initLights()
{
   GLfloat mat_ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
   GLfloat mat_diffuse[] = { 0.4f, 0.8f, 0.4f, 1.0f };
   GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
   GLfloat mat_shininess[] = { 50.0f };

   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

   GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0 };
   GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
   GLfloat light_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
   GLfloat light_position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

   glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_COLOR_MATERIAL);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
}

void GameEngine::initGeometry()
{
   m_shapes.push_back(
      std::make_unique<ogl::Line>(
         glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3(0.0f, 0.0f, -50.0f),
         1.0f, 0.0f, 0.0f
      )
   );

   m_shapes.push_back(
      std::make_unique<ogl::Rectangle>(
         220.0f, 55.0f, 1.0f, 0.0f, 0.0f
      )
   );

}

std::pair<int, int> GameEngine::getWindowSize()
{
   int width{ 0 };
   int height{ 0 };

   SDL_GetWindowSize(m_window.get(), &width, &height);
   SDL_GL_GetDrawableSize(m_window.get(), &width, &height);

   return { width, height };
}
