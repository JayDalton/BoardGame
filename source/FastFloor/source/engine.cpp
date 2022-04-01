#include "engine.h"

//#include "shapes/line.hpp"
//#include "shapes/cuboid.hpp"
#include "shapes/rectangle.hpp"

ogl::Size getWindowSize(SDL_Window* window)
{
   ogl::Size size, draw;

   SDL_GetWindowSize(window, &size.x, &size.y);
   SDL_GL_GetDrawableSize(window, &draw.x, &draw.y);

   if (size != draw)
   {
      SDL_Log("XX: %d|%d - %d|%d", size.x, size.y, draw.x, draw.y);
   }

   return size;
}

ogl::Size updateViewport(SDL_Window* window)
{
   //const auto [width, height] = getWindowSize(window);
   const auto size{ getWindowSize(window) };

   SDL_Log("OpenGL WindowRenderSize: %d x %d", size.x, size.y);

   glViewport(0, 0, size.x, size.y);

   return size;
}

ogl::GameEngine::GameEngine(std::string_view title)
   : m_title(title)
{

}

bool ogl::GameEngine::construct(int width, int height)
{
   using std::cout;
   using std::endl;
   
   if (!(m_system = sdl2::make_sdlsystem(SDL_INIT_VIDEO | SDL_INIT_TIMER)))
   {
      cout << "Error creating SDL2 system: " << SDL_GetError() << endl;
      return false;
   }

   /* Setting up OpenGL version and profile details for context creation */
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
   const char* glsl_version = "#version 150";

   // Create window with graphics context
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
   SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
   SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

   if (!(m_window = sdl2::make_window(m_title.data(), 
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 
      { SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI /*| SDL_WINDOW_RESIZABLE*/ })))
   {
      cout << "Error creating window: " << SDL_GetError() << endl;
      return false;
   }

   if (!(m_context = SDL_GL_CreateContext(m_window.get())))
   {
      cout << "Error creating context: " << SDL_GetError() << endl;
      return false;
   }

   SDL_GL_MakeCurrent(m_window.get(), m_context);
   SDL_GL_SetSwapInterval(1); // Enable vsync

   /* Loading Extensions */
   //glewExperimental = GL_TRUE;
   if (auto error = glewInit())
   {
      cout << std::format("GLEW init failed: {}", error) << endl;
      return false;
   }

   Uint32 renderFlags{ SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC };

   if (!(m_render = sdl2::make_renderer(m_window.get(), -1, renderFlags)))
   {
      cout << "Error creating renderer: " << SDL_GetError() << endl;
      return false;
   }

   return true;
}

void ogl::GameEngine::setWindowTitle(std::string label)
{
   SDL_SetWindowTitle(m_window.get(), 
      std::format("{} {}", m_title, label).c_str());
}

void ogl::GameEngine::start()
{
   //m_windowSize = updateViewport(m_window.get());

   initOpenGL();
   //initCamera();
   //initLights();
   initGeometry();

   createUser();

   m_lastTime = SteadyClock::now();

   // annimation loop
   while (m_running)
   {
      // per-frame time logic
      // --------------------
      auto currentFrame = SteadyClock::now();
      m_deltaTime = currentFrame - m_lastFrame;
      m_lastFrame = currentFrame;

      m_frames++;
      using namespace std::literals;
      if (1s < (SteadyClock::now() - m_lastTime))
      {
         setWindowTitle(std::format(" FPS {:5}", 1000ms / m_frames));
         m_lastTime += 1s;
         m_frames = 0;
      }

      OnReceiveLocal();
      OnReceiveRemote();

      OnUpdateWorld(m_deltaTime);

      // Renderziel
      OnRenderWorld(m_deltaTime);

      SDL_GL_SwapWindow(m_window.get());

      // calculates to 60 fps
      SDL_Delay(1000 / 60);
   }

   OnRemoveWorld();

   SDL_GL_DeleteContext(m_context);
   SDL_DestroyWindow(m_window.get());
   SDL_Quit();
}

void ogl::GameEngine::OnReceiveLocal()
{
   //float cameraSpeed = 0.05;// m_deltaTime * 2.5;
   //float cameraSpeed = 2.5 * m_deltaTime.count();
   float cameraSpeed = 1.0;

   //std::cout << std::format("DeltaTime: {}", m_deltaTime) << std::endl;

   SDL_Event event;
   while (SDL_PollEvent(&event))
   {
      switch (event.type)
      {

      case SDL_QUIT:
         // handling of close button
         m_running = false;
         break;

      case SDL_WINDOWEVENT:
         switch (event.window.event) {
         case SDL_WINDOWEVENT_SHOWN:
            m_windowSize = { event.window.data1, event.window.data2 };
            break;
         case SDL_WINDOWEVENT_SIZE_CHANGED:
            m_windowSize = { event.window.data1, event.window.data2 };
            //m_windowSize = ::updateViewport(m_window.get());
            SDL_Log("Window size changed: %d x %d", m_windowSize.x, m_windowSize.y);
            break;
         case SDL_WINDOWEVENT_ENTER:
            SDL_Log("Mouse entered window %d",
               event.window.windowID);
            break;
         case SDL_WINDOWEVENT_LEAVE:
            SDL_Log("Mouse left window %d", event.window.windowID);
            break;
         }
         break;

      case SDL_MOUSEWHEEL:
      {
         auto direction{ glm::normalize(m_cameraTarget - m_cameraEye) };
         auto distance{ glm::distance(m_cameraTarget, m_cameraEye) };

         if (0 < distance)
         {
         }

         if (event.wheel.y > 0) // scroll up
         {
            auto factor = std::abs(event.wheel.y);
            auto stepLength = factor * cameraSpeed * direction;
            std::cout << std::format("Scroll UP {} {} {}\n", factor, cameraSpeed, glm::to_string(stepLength));
            //if (glm::distance(m_cameraTarget, stepLength) < distance)
            {
               m_cameraEye += stepLength;
            }
         }
         else if (event.wheel.y < 0) // scroll down
         {
            auto factor = std::abs(event.wheel.y);
            auto stepLength = factor * cameraSpeed * direction;
            std::cout << std::format("Scroll DOWN {} {} {}\n", factor, cameraSpeed, glm::to_string(stepLength));
            //if (glm::distance(m_cameraTarget, stepLength) < distance)
            {
               m_cameraEye -= stepLength;
            }
         }

         if (event.wheel.x > 0) // scroll right
         {
            std::cout << std::format("Scroll RIGHT {}\n", event.wheel.x);
         }
         else if (event.wheel.x < 0) // scroll left
         {
            std::cout << std::format("Scroll LEFT {}\n", event.wheel.x);
         }
      }
      break;

      case SDL_KEYDOWN: {
         auto direction{ glm::normalize(m_cameraTarget - m_cameraEye) };
         auto cameraRight{ glm::normalize(glm::cross(m_cameraUpside, direction)) };
         auto cameraFront{ glm::normalize(glm::cross(m_cameraUpside, cameraRight)) };

         switch (event.key.keysym.scancode) {
         case SDL_SCANCODE_ESCAPE:
            m_running = false;
            return;

         case SDL_SCANCODE_SPACE: {
            m_cameraEye = { 15.0, 15.0, 15.0 };
            m_cameraTarget = { 0.0, 0.0, 0.0 };
            std::cout << std::format("Reset Camera {}\n", glm::to_string(m_cameraEye));
         }
         break;

         case SDL_SCANCODE_W:
         case SDL_SCANCODE_UP: { // translate eye + target on plane
            m_cameraEye -= cameraFront;
            m_cameraTarget -= cameraFront;
            std::cout << std::format("Camera UP {}\n", glm::to_string(m_cameraEye));
         }
         break;

         case SDL_SCANCODE_S:
         case SDL_SCANCODE_DOWN: { // translate eye + target on plane
            m_cameraEye += cameraFront;
            m_cameraTarget += cameraFront;
            std::cout << std::format("Camera DOWN {}\n", glm::to_string(m_cameraEye));
         }
         break;

         case SDL_SCANCODE_A:
         case SDL_SCANCODE_LEFT: { // translate eye + target on plane
            m_cameraEye += cameraRight;
            m_cameraTarget += cameraRight;
            std::cout << std::format("Camera LEFT {}\n", glm::to_string(m_cameraEye));
         }
         break;

         case SDL_SCANCODE_D:
         case SDL_SCANCODE_RIGHT: { // translate eye + target on plane
            m_cameraEye -= cameraRight;
            m_cameraTarget -= cameraRight;
            std::cout << std::format("Camera RIGHT {}\n", glm::to_string(m_cameraEye));
         }
         break;

         case SDL_SCANCODE_E: { // right rotate by CameraUp
            m_cameraEye += glm::normalize(glm::cross(direction, m_cameraUpside)) * cameraSpeed;
            std::cout << std::format("Camera LEFT {}\n", glm::to_string(m_cameraEye));
         }
         break;

         case SDL_SCANCODE_Q: { // left rotate by CameraUp
            m_cameraEye -= glm::normalize(glm::cross(direction, m_cameraUpside)) * cameraSpeed;
            std::cout << std::format("Camera RIGHT {}\n", glm::to_string(m_cameraEye));
         }
         break;

         case SDL_SCANCODE_R: { // neigen hoch
            m_cameraEye += glm::normalize(glm::cross(direction, cameraRight)) * cameraSpeed;
            std::cout << std::format("Camera RIGHT {}\n", glm::to_string(m_cameraEye));
         }
         break;

         case SDL_SCANCODE_F: { // neigen runter
            m_cameraEye -= glm::normalize(glm::cross(direction, cameraRight)) * cameraSpeed;
            std::cout << std::format("Camera RIGHT {}\n", glm::to_string(m_cameraEye));
         }
         break;

         default:
            std::cout
               << "Code: " << event.key.keysym.scancode
               << " Sym: " << event.key.keysym.sym
               << " Sym: " << SDL_GetScancodeName(event.key.keysym.scancode)
               << " Sym: " << SDL_GetKeyName(event.key.keysym.sym)
               << std::endl;
            break;
         }
      }
      break;

      case SDL_MOUSEMOTION: {
      //   auto xpos = event.motion.x;
      //   auto ypos = event.motion.y;

      //   if (m_mouse.firstMouse)
      //   {
      //      m_mouse.lastX = xpos;
      //      m_mouse.lastY = ypos;
      //      m_mouse.firstMouse = false;
      //   }

      //   float xoffset = xpos - m_mouse.lastX;
      //   float yoffset = m_mouse.lastY - ypos; // reversed since y-coordinates go from bottom to top
      //   m_mouse.lastX = xpos;
      //   m_mouse.lastY = ypos;

      //   float sensitivity = 0.1f; // change this value to your liking
      //   xoffset *= sensitivity;
      //   yoffset *= sensitivity;

      //   m_mouse.yaw += xoffset;
      //   m_mouse.pitch += yoffset;

      //   // make sure that when pitch is out of bounds, screen doesn't get flipped
      //   if (m_mouse.pitch > 89.0f)
      //      m_mouse.pitch = 89.0f;
      //   if (m_mouse.pitch < -89.0f)
      //      m_mouse.pitch = -89.0f;

      //   glm::vec3 front;
      //   front.x = cos(glm::radians(m_mouse.yaw)) * cos(glm::radians(m_mouse.pitch));
      //   front.y = sin(glm::radians(m_mouse.pitch));
      //   front.z = sin(glm::radians(m_mouse.yaw)) * cos(glm::radians(m_mouse.pitch));
      //   m_cameraFront = glm::normalize(front);
      }
      break;

      }
   }
}

void ogl::GameEngine::OnReceiveRemote()
{
}

void ogl::GameEngine::OnUpdateWorld(Duration duration)
{
   //m_objCache.updateAll(duration);
   //for (auto&& object : m_objects)
   //{
   //   object.update(duration);
   //}
}

void ogl::GameEngine::OnRenderWorld(Duration duration)
{
   // Hintergrund
   glClearColor(0.3f, 0.5f, 0.4f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   auto view = glm::lookAt(
      m_cameraEye, 
      m_cameraTarget, 
      m_cameraUpside);

   for (auto&& object : m_objects)
   {
      render(object, m_projection * view);
   }

   updateUser(m_projection * view);

   //// ViewPort buttom-left
   //glViewport(0, 0, windowSize.x / 4, windowSize.y / 4);
   //for (std::vector<ogl::Shape*>::iterator it = objs2d->begin(); it != objs2d->end(); ++it) {
   //   glLoadMatrixf(glm::value_ptr(screen.mtx() * (*it)->getMatrix()));
   //   (*it)->render();
   //}
}

void ogl::GameEngine::OnRemoveWorld()
{
   for (auto&& [id, tex] : m_texture)
   {
      tex.freeTexture();
   }
   for (auto&& [id, tex] : m_shader)
   {
      tex.freeShader();
   }
   for (auto&& [id, tex] : m_buffer)
   {
      tex.freeBuffer();
   }
}

void ogl::GameEngine::initWindow()
{

}

void ogl::GameEngine::initOpenGL()
{
   //glClearDepthf(1.0f);
   glEnable(GL_DEPTH_TEST);
   //glDepthFunc(GL_LEQUAL);
   //glEnable(GL_CULL_FACE);
}

void ogl::GameEngine::initCamera()
{
   m_camera = Camera(
      glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 1000.0f),
      glm::vec3(0.0f, 0.0f, 8.0f),
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(0.0f, 1.0f, 0.0f)
   );

   m_screen = Camera(
      glm::ortho(-40.0f, 40.0f, -30.0f, 30.0f, 0.1f, 1000.0f),
      glm::vec3(0.0f, 0.0f, 1.0f),
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(0.0f, 1.0f, 0.0f)
   );
}

void ogl::GameEngine::initLights()
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

void ogl::GameEngine::initGeometry()
{
   // 3D Koordinatensystem
   auto model = glm::mat4(1.0f);
   auto shaderId1 = createShader("shader/Complex.vs", "shader/Colored.fs");

   Drawable planeX;
   planeX.m_buffer = createRect({5, 5}, Colors::Red);
   planeX.m_shader = shaderId1;
   planeX.m_position = {5, 5, 0};
   //planeX.m_localMat = glm::translate(model, {});
   m_objects.push_back(planeX);

   Drawable planeY;
   planeY.m_buffer = createRect({5.0, 5.0}, Colors::Green);
   planeY.m_shader = shaderId1;
   planeY.m_position = {0.0,0.0,0.5};
   //planeY.m_localMat = glm::rotate(model, glm::radians(90.0f), { 0.0f, 1.0f, 0.0f });
   m_objects.push_back(planeY);

   Drawable planeZ;
   planeZ.m_buffer = createRect({0.5, 1.0}, Colors::Blue);
   planeZ.m_shader = shaderId1;
   planeZ.m_position = {};
   planeZ.m_localMat = glm::rotate(model, glm::radians(90.0f), { 1.0f, 0.0f, 0.0f });
   m_objects.push_back(planeZ);
}

void ogl::GameEngine::render(Drawable object, Matrix view)
{
   if (m_texture.contains(object.m_texture1))
   {
      auto& texture = m_texture.at(object.m_texture1);
      texture.useTexture();
   }

   if (m_texture.contains(object.m_texture2))
   {
      auto& texture = m_texture.at(object.m_texture2);
      texture.useTexture();
   }

   if (m_shader.contains(object.m_shader))
   {
      auto& shader = m_shader.at(object.m_shader);
      shader.useShader();
      shader.setMat4("model", view * object.getPosition());
   }

   if (m_buffer.contains(object.m_buffer))
   {
      auto& buffer = m_buffer.at(object.m_buffer);
      buffer.useBuffer();
   }
}

ogl::ShaderId ogl::GameEngine::createShader(std::string_view vertex, std::string_view fragment)
{
   Shader shader;
   shader.createShaders(vertex, fragment);
   return append(shader);
}

ogl::TextureId ogl::GameEngine::createTexture(std::string_view fileName)
{
   Texture texture;
   texture.createTexture(fileName);
   return append(texture);
}

ogl::BufferId ogl::GameEngine::createSquare(float size, Color color)
{
   Buffer buffer{};
   buffer.bindBuffer({
      Buffer::create({ +size, +size, 0.f }, color, { 1.0f, 1.0f }),
      Buffer::create({ +size, -size, 0.f }, color, { 1.0f, 0.0f }),
      Buffer::create({ -size, -size, 0.f }, color, { 0.0f, 0.0f }),
      Buffer::create({ -size, +size, 0.f }, color, { 0.0f, 1.0f }) },
      { 0u, 1u, 3u, 1u, 2u, 3u }
   );

   return append(buffer);
}

ogl::BufferId ogl::GameEngine::createRect(SizeF size, Color color)
{
   Buffer buffer{};
   buffer.bindBuffer({
      Buffer::create({ +size.x, +size.y, 0.f }, color, { 1.0f, 1.0f }),
      Buffer::create({ +size.x, -size.y, 0.f }, color, { 1.0f, 0.0f }),
      Buffer::create({ -size.x, -size.y, 0.f }, color, { 0.0f, 0.0f }),
      Buffer::create({ -size.x, +size.y, 0.f }, color, { 0.0f, 1.0f }) },
      { 0u, 1u, 3u, 1u, 2u, 3u }
   );

   return append(buffer);
}

ogl::BufferId ogl::GameEngine::createCircle(float size, Color color)
{
   return {};
}

ogl::BufferId ogl::GameEngine::createHexagon(float size, Color color)
{
   Buffer buffer{};
   buffer.bindBuffer({
      Buffer::create(Vertex{ 0.f }, color, { 0.5f, 0.5f }),
      Buffer::create(Geometry::circlePoint(030.f, size), color),
      Buffer::create(Geometry::circlePoint(090.f, size), color),
      Buffer::create(Geometry::circlePoint(150.f, size), color),
      Buffer::create(Geometry::circlePoint(210.f, size), color),
      Buffer::create(Geometry::circlePoint(270.f, size), color),
      Buffer::create(Geometry::circlePoint(330.f, size), color) },
      {
      0u, 1u, 2u,
      0u, 2u, 3u,
      0u, 3u, 4u,
      0u, 4u, 5u,
      0u, 5u, 6u,
      0u, 6u, 1u,
      }
   );

   return append(buffer);
}

ogl::BufferId ogl::GameEngine::createHexoid(float size, Color color)
{
   return {};
}

//const GLfloat ogl::Cuboid::VERTICES[][11] = {
//
//  {-1, 1, 1,   0, 1, 0,   1, 1, 1,   0.000000f, 0.50f},   // unten links
//  { 1, 1, 1,   0, 1, 0,   1, 1, 1,   0.333333f, 0.50f},   // unten rechts (top)
//  { 1, 1,-1,   0, 1, 0,   1, 1, 1,   0.333333f, 1.00f},   // oben rechts
//  {-1, 1,-1,   0, 1, 0,   1, 1, 1,   0.000000f, 1.00f},  // oben links
//
//  {-1,-1, 1,   0, 0, 1,   1, 1, 1,   0.333333f, 0.50f},   // unten links
//  { 1,-1, 1,   0, 0, 1,   1, 1, 1,   0.666666f, 0.50f},   // unten rechts
//  { 1, 1, 1,   0, 0, 1,   1, 1, 1,   0.666666f, 1.00f},   // oben rechts (front)
//  {-1, 1, 1,   0, 0, 1,   1, 1, 1,   0.333333f, 1.00f},  // oben links
//
//  { 1,-1, 1,   1, 0, 0,   1, 1, 1,   0.666666f, 0.50f},   // unten links
//  { 1,-1,-1,   1, 0, 0,   1, 1, 1,   1.000000f, 0.50f},   // unten rechts
//  { 1, 1,-1,   1, 0, 0,   1, 1, 1,   1.000000f, 1.00f},   // oben rechts
//  { 1, 1, 1,   1, 0, 0,   1, 1, 1,   0.666666f, 1.00f},  // oben links (right)
//
//  { 1,-1,-1,   0, 0,-1,   1, 1, 1,   0.000000f, 0.00f},   // unten links (back)
//  {-1,-1,-1,   0, 0,-1,   1, 1, 1,   0.333333f, 0.00f},   // unten rechts
//  {-1, 1,-1,   0, 0,-1,   1, 1, 1,   0.333333f, 0.50f},   // oben rechts
//  { 1, 1,-1,   0, 0,-1,   1, 1, 1,   0.000000f, 0.50f},  // oben links
//
//  {-1,-1,-1,  -1, 0, 0,   1, 1, 1,   0.333333f, 0.00f},   // unten links
//  {-1,-1, 1,  -1, 0, 0,   1, 1, 1,   0.666666f, 0.00f},   // unten rechts
//  {-1, 1, 1,  -1, 0, 0,   1, 1, 1,   0.666666f, 0.50f},   // oben rechts (left)
//  {-1, 1,-1,  -1, 0, 0,   1, 1, 1,   0.333333f, 0.50f},  // oben links
//
//  {-1,-1,-1,   0,-1, 0,   1, 1, 1,   0.666666f, 0.00f},   // unten links (bottom)
//  { 1,-1,-1,   0,-1, 0,   1, 1, 1,   1.000000f, 0.00f},   // unten rechts
//  { 1,-1, 1,   0,-1, 0,   1, 1, 1,   1.000000f, 0.50f},   // oben rechts
//  {-1,-1, 1,   0,-1, 0,   1, 1, 1,   0.666666f, 0.50f}   // oben links
//
//};

//const GLuint ogl::Cuboid::INDICES[] = {
//   0, 1, 2,   2, 3, 0,      // front
//   4, 5, 6,   6, 7, 4,      // right
//   8, 9,10,  10,11, 8,      // top
//  12,13,14,  14,15,12,      // left
//  16,17,18,  18,19,16,      // bottom
//  20,21,22,  22,23,20       // back
//};

//############################################################################
/** |
    ((V, N, C, T), (V, N, C, T), ...)
    ((vx,vy,vz, nx,ny,nz, cr,cg,cb, tx,ty), (...), ...)


//    v7----- v6
//   /|      /|
//  v3------v2|
//  | |     | |
//  | |v4---|-|v5
//  |/      |/
//  v0------v1
*/
ogl::BufferId ogl::GameEngine::createCuboid(float size, Color color)
{
   Buffer buffer{};
   buffer.setDrawMode(Buffer::DrawMode::LineStrip);
   buffer.bindBuffer({

      Buffer::create({ +size,-size,+size }, { 0, 0, +1 }, color, { 1, 1 }), // V1
      Buffer::create({ +size,+size,+size }, { 0, 0, +1 }, color, { 1, 0 }), // V2
      Buffer::create({ -size,+size,+size }, { 0, 0, +1 }, color, { 0, 0 }), // V3
      Buffer::create({ -size,-size,+size }, { 0, 0, +1 }, color, { 0, 1 }), // V0

      Buffer::create({ +size,-size,+size }, { +1, 0, 0 }, color, { 0, 1 }), // V1
      Buffer::create({ +size,-size,-size }, { +1, 0, 0 }, color, { 1, 1 }), // V5
      Buffer::create({ +size,+size,-size }, { +1, 0, 0 }, color, { 1, 0 }), // V6
      Buffer::create({ +size,+size,+size }, { +1, 0, 0 }, color, { 0, 0 }), // V2

      Buffer::create({ +size,-size,-size }, { 0, 0, -1 }, color, { 1, 1 }), // V5
      Buffer::create({ +size,+size,-size }, { 0, 0, -1 }, color, { 1, 0 }), // V6
      Buffer::create({ -size,+size,-size }, { 0, 0, -1 }, color, { 0, 0 }), // V7
      Buffer::create({ -size,-size,-size }, { 0, 0, -1 }, color, { 0, 1 }), // V4

      Buffer::create({ -size,-size,-size }, { -1, 0, 0 }, color, { 1, 0 }), // V4
      Buffer::create({ -size,-size,+size }, { -1, 0, 0 }, color, { 0, 0 }), // V0
      Buffer::create({ -size,+size,+size }, { -1, 0, 0 }, color, { 0, 1 }), // V3
      Buffer::create({ -size,+size,-size }, { -1, 0, 0 }, color, { 1, 1 }), // V7

      Buffer::create({ -size,-size,+size }, { 0, -1, 0 }, color, { 0, 0 }), // V0
      Buffer::create({ -size,-size,-size }, { 0, -1, 0 }, color, { 0, 1 }), // V4
      Buffer::create({ +size,-size,-size }, { 0, -1, 0 }, color, { 1, 1 }), // V5
      Buffer::create({ +size,-size,+size }, { 0, -1, 0 }, color, { 1, 0 }), // V1

      Buffer::create({ -size,+size,+size }, { 0, +1, 0 }, color, { 0, 0 }), // V0
      Buffer::create({ -size,+size,-size }, { 0, +1, 0 }, color, { 0, 1 }), // V4
      Buffer::create({ +size,+size,-size }, { 0, +1, 0 }, color, { 1, 1 }), // V5
      Buffer::create({ +size,+size,+size }, { 0, +1, 0 }, color, { 1, 0 }), // V1

      },
//    Y
//    v7----- v6
//   /|      /|
//  v3------v2|
//  | |     | |
//  | |v4---|-|v5
//  |/      |/
//  v0------v1 X
// Z
      {
         0, 1, 2,   2, 3, 0,      // front
         4, 5, 6,   6, 7, 4,      // right
         8, 9,10,  10,11, 8,      // top
        12,13,14,  14,15,12,      // left
        16,17,18,  18,19,16,      // bottom
        20,21,22,  22,23,20       // back
      }
      );

   return append(buffer);
}

ogl::BufferId ogl::GameEngine::createSphere(float size, Color color)
{
   Buffer buffer{};
   buffer.bindBuffer({
      Buffer::create(Vertex{ 0.f }, color, { 0.5f, 0.5f }),
      Buffer::create(Geometry::circlePoint(030.f, size), color),
      Buffer::create(Geometry::circlePoint(090.f, size), color),
      Buffer::create(Geometry::circlePoint(150.f, size), color),
      Buffer::create(Geometry::circlePoint(210.f, size), color),
      Buffer::create(Geometry::circlePoint(270.f, size), color),
      Buffer::create(Geometry::circlePoint(330.f, size), color) },
      {
      0u, 1u, 2u,
      0u, 2u, 3u,
      0u, 3u, 4u,
      0u, 4u, 5u,
      0u, 5u, 6u,
      0u, 6u, 1u,
      }
      );

   return append(buffer);
}

ogl::BufferId ogl::GameEngine::createCylinder(float radius, float hight, Color color)
{
   Buffer buffer{};
   buffer.setDrawMode(Buffer::DrawMode::Triangles);
   //buffer.bindBuffer({
   //   Buffer::create(Vertex{ 0.f }, color, { 0.5f, 0.5f }),
   //   Buffer::create(Geometry::circlePoint(030.f, size), color),
   //   Buffer::create(Geometry::circlePoint(090.f, size), color),
   //   Buffer::create(Geometry::circlePoint(150.f, size), color),
   //   Buffer::create(Geometry::circlePoint(210.f, size), color),
   //   Buffer::create(Geometry::circlePoint(270.f, size), color),
   //   Buffer::create(Geometry::circlePoint(330.f, size), color) },
   //   {
   //   0u, 1u, 2u,
   //   0u, 2u, 3u,
   //   0u, 3u, 4u,
   //   0u, 4u, 5u,
   //   0u, 5u, 6u,
   //   0u, 6u, 1u,
   //   }
   //   );

   return append(buffer);
}

//ogl::Size ogl::GameEngine::getWindowSize()
//{
//   int width{ 0 };
//   int height{ 0 };
//
//   SDL_GL_GetDrawableSize(m_window.get(), &width, &height);
//
//   return { width, height };
//}
