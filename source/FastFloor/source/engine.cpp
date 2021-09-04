#include "engine.h"

//#include "shapes/line.hpp"
//#include "shapes/cuboid.hpp"
#include "shapes/rectangle.hpp"

GameEngine::GameEngine(std::string_view title)
   : m_title(title), m_system(sdl2::make_sdlsystem(SDL_INIT_VIDEO | SDL_INIT_TIMER))
{

}

bool GameEngine::construct(int width, int height)
{
   using std::cout;
   using std::endl;

   if (m_system == nullptr)
   {
      cout << "Error creating SDL2 system: " << SDL_GetError() << endl;
      return false;
   }

   /* Setting up OpenGL version and profile details for context creation */
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

   if (auto win = sdl2::make_window(m_title.data(), 
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 
      { SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL }))
   {
      m_window = std::move(win); // Context ???
   }

   if (!m_window)
   {
      cout << "Error creating window: " << SDL_GetError() << endl;
      return false;
   }

   m_context = SDL_GL_CreateContext(m_window.get());
   if (!m_context)
   {
      cout << "Error creating context: " << SDL_GetError() << endl;
      return false;
   }

   /* Loading Extensions */
   glewExperimental = GL_TRUE;
   if (auto error = glewInit())
   {
      cout << std::format("GLEW init failed: {}", error) << endl;
      return false;
   }

   //Use Vsync
   if (SDL_GL_SetSwapInterval(1) < 0)
   {
      cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << endl;
      return false;
   }

   Uint32 renderFlags{ SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC };

   if (auto ren = sdl2::make_renderer(m_window.get(), -1, renderFlags))
   {
      m_render = std::move(ren);
   }

   if (!m_render)
   {
      cout << "Error creating renderer: " << SDL_GetError() << endl;
      return false;
   }

   //glEnable(GL_DEPTH_TEST);

   initCamera();
   //initLights();
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
   m_lastTime = SteadyClock::now();

   // annimation loop
   while (m_running)
   {
      m_frames++;
      using namespace std::literals;
      if (1s < (SteadyClock::now() - m_lastTime))
      {
         setWindowTitle(std::format(" FPS {:5}", 1000ms / m_frames));
         m_lastTime += 1s;
         m_frames = 0;
      }

      OnReceiveLocal();
      OnReceiveServer();

      //updateUser();
      OnUpdateWorld(getDuration(m_lastTime));

      // Renderziel
      OnRenderWorld();


      SDL_GL_SwapWindow(m_window.get());

      // calculates to 60 fps
      SDL_Delay(1000 / 60);
   }

   //OnDestroyWorld();

   SDL_GL_DeleteContext(m_context);
   SDL_Quit();
}

GameEngine::Duration GameEngine::getDuration(const SteadyClock::time_point& start)
{
   return std::chrono::duration_cast<Duration>(SteadyClock::now() - start);
}

void GameEngine::OnReceiveLocal()
{
   float cameraSpeed = m_deltaTime * 2.5;

   SDL_Event event;
   while (SDL_PollEvent(&event))
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
            m_cameraPos += cameraSpeed * m_cameraFront;
            break;
         case SDL_SCANCODE_A:
         case SDL_SCANCODE_LEFT:
            m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
            break;
         case SDL_SCANCODE_S:
         case SDL_SCANCODE_DOWN:
            m_cameraPos -= cameraSpeed * m_cameraFront;
            break;
         case SDL_SCANCODE_D:
         case SDL_SCANCODE_RIGHT:
            m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
            break;
         default:
            break;
         }
         break;

      case SDL_MOUSEMOTION:
      {
         auto xpos = event.motion.x;
         auto ypos = event.motion.y;

         if (m_mouse.firstMouse)
         {
            m_mouse.lastX = xpos;
            m_mouse.lastY = ypos;
            m_mouse.firstMouse = false;
         }

         float xoffset = xpos - m_mouse.lastX;
         float yoffset = m_mouse.lastY - ypos; // reversed since y-coordinates go from bottom to top
         m_mouse.lastX = xpos;
         m_mouse.lastY = ypos;

         float sensitivity = 0.1f; // change this value to your liking
         xoffset *= sensitivity;
         yoffset *= sensitivity;

         m_mouse.yaw += xoffset;
         m_mouse.pitch += yoffset;

         // make sure that when pitch is out of bounds, screen doesn't get flipped
         if (m_mouse.pitch > 89.0f)
            m_mouse.pitch = 89.0f;
         if (m_mouse.pitch < -89.0f)
            m_mouse.pitch = -89.0f;

         glm::vec3 front;
         front.x = cos(glm::radians(m_mouse.yaw)) * cos(glm::radians(m_mouse.pitch));
         front.y = sin(glm::radians(m_mouse.pitch));
         front.z = sin(glm::radians(m_mouse.yaw)) * cos(glm::radians(m_mouse.pitch));
         m_cameraFront = glm::normalize(front);
      }
      break;

      case SDL_MOUSEWHEEL:
      {
         auto yoffset = event.wheel.y;
         m_mouse.fov -= (float)yoffset;

         if (m_mouse.fov < 1.0f)
            m_mouse.fov = 1.0f;

         if (m_mouse.fov > 45.0f)
            m_mouse.fov = 45.0f;
      }
         break;
      }
   }
}

void GameEngine::OnReceiveServer()
{
}

void GameEngine::OnUpdateWorld(Duration duration)
{
   //for (auto& shape : m_shapes)
   //{
   //   shape->update(duration);
   //}
}

void GameEngine::OnRenderWorld()
{
   //// MainWindow
   auto size = getWindowSize();
   glViewport(0, 0, size.x, size.y);

   // Hintergrund
   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

   for (const auto& shape : m_shapes) 
   {
      //auto matrix{ m_camera.mtx() * shape->getMatrix() };
      //glLoadMatrixf(glm::value_ptr(matrix));
      shape->render();
   }

   //// ViewPort buttom-left
   //glViewport(0, 0, windowSize.x / 4, windowSize.y / 4);
   //for (std::vector<ogl::Shape*>::iterator it = objs2d->begin(); it != objs2d->end(); ++it) {
   //   glLoadMatrixf(glm::value_ptr(screen.mtx() * (*it)->getMatrix()));
   //   (*it)->render();
   //}
}

void GameEngine::OnRemoveWorld()
{
   m_shapes.clear();
}

void GameEngine::initWindow()
{

}

bool GameEngine::initOpenGL()
{
   //glEnable(GL_DEPTH_TEST);

   return true;
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
   //auto error = glGetError();

   //GLfloat mat_ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
   //GLfloat mat_diffuse[] = { 0.4f, 0.8f, 0.4f, 1.0f };
   //GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
   //GLfloat mat_shininess[] = { 50.0f };

   //glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   //error = glGetError();
   //glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   //error = glGetError();
   //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   //error = glGetError();
   //glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   //error = glGetError();

   //GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0 };
   //GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
   //GLfloat light_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
   //GLfloat light_position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

   //glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
   //error = glGetError();
   //glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   //error = glGetError();
   //glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
   //error = glGetError();
   //glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   //error = glGetError();

   //error = glGetError();

   //glEnable(GL_COLOR_MATERIAL);
   //error = glGetError();
   //glEnable(GL_LIGHTING);
   //error = glGetError();
   //glEnable(GL_LIGHT0);
   //error = glGetError();
}

void GameEngine::initGeometry()
{
   m_shapes.push_back(
      std::make_unique<Square>(
         "shader/Simple.vs",
         "shader/Simple.fs",
         ogl::Colors::Blue));
   //      "images/container.jpg"

   m_shapes.push_back(
      std::make_unique<Hexagon>(
         "shader/Simple.vs",
         "shader/Simple.fs",
         ogl::Colors::Green));

   m_shapes.push_back(
      std::make_unique<Rectangle>(
         ogl::Size{200, 400},
         "shader/Simple.vs",
         "shader/Simple.fs",
         ogl::Colors::Red
         ));
}

ogl::Size GameEngine::getWindowSize()
{
   int width{ 0 };
   int height{ 0 };

   SDL_GL_GetDrawableSize(m_window.get(), &width, &height);

   return { width, height };
}
