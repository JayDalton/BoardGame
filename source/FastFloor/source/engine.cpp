#include "engine.h"

#include "shapes/line.hpp"
#include "shapes/cuboid.hpp"
#include "shapes/rectangle.hpp"

//#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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
   using std::cerr;
   using std::cout;
   using std::endl;

   auto error = glGetError();
   const auto start = StopClock::now();

   error = glGetError();


    ogl::Shader ourShader("shader/texture.vs", "shader/texture.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    // add a new set of vertices to form a second triangle (a total of 6 vertices); the vertex attribute configuration remains the same (still one 3-float position vector per vertex)
    float vertices[] = {
       // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };
    unsigned int indices[] = {
       0, 1, 3, // first triangle
       1, 2, 3  // second triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture 
        // -------------------------
    unsigned int texture1, texture2;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // note that we set the container wrapping method to GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load("images/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
       glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
       glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
       std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// we want to repeat the awesomeface pattern so we kept it at GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("images/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
       // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
       glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
       glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
       std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.useShader(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(ourShader.m_id, "texture1"), 0);
    // or set it via the texture class
    ourShader.setInt("texture2", 1);


   m_timer = StopClock::now();

   // annimation loop
   while (m_running)
   {
      OnReceiveLocal();
      OnReceiveServer();

      //updateUser();
      OnUpdateWorld(getDuration(m_timer));

      glm::mat4 trans = glm::mat4(1.0f);
      trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
      trans = glm::rotate(trans, (float)SDL_GetTicks(), glm::vec3(0.0f, 0.0f, 1.0f));

      unsigned int transformLoc = glGetUniformLocation(ourShader.m_id, "transform");
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

      // Renderziel
      //auto size = getWindowSize();
      //glViewport(0, 0, size.x, size.y);

      OnRenderWorld();


      // bind textures on corresponding texture units
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, texture1);
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, texture2);

      // render container
      ourShader.useShader();
      glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


      SDL_GL_SwapWindow(m_window.get());

      using namespace std::literals;

      m_frames++;
      if (1s < getDuration(m_timer))
      {
         m_timer = StopClock::now();
         setWindowTitle(std::format(" FPS {:5}", m_frames));
         m_frames = 0;
      }

      // calculates to 60 fps
      SDL_Delay(1000 / 60);
   }

   glDeleteVertexArrays(1, &VAO);
   glDeleteBuffers(1, &VBO);
   glDeleteBuffers(1, &EBO);

   SDL_GL_DeleteContext(m_context);
   SDL_Quit();
}

GameEngine::Duration GameEngine::getDuration(const StopClock::time_point& start)
{
   return std::chrono::duration_cast<Duration>(StopClock::now() - start);
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
   glClear(GL_COLOR_BUFFER_BIT);
   //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

   //for (auto& shape : m_shapes) 
   //{
   //   //auto matrix{ m_camera.mtx() * shape->getMatrix() };
   //   //glLoadMatrixf(glm::value_ptr(matrix));
   //   shape->render();
   //}

   //// ViewPort buttom-left
   //glViewport(0, 0, windowSize.x / 4, windowSize.y / 4);
   //for (std::vector<ogl::Shape*>::iterator it = objs2d->begin(); it != objs2d->end(); ++it) {
   //   glLoadMatrixf(glm::value_ptr(screen.mtx() * (*it)->getMatrix()));
   //   (*it)->render();
   //}
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
   //m_shapes.push_back(
   //   std::make_unique<ogl::Line>(
   //      glm::vec3(0.0f, 0.0f, 0.0f),
   //      glm::vec3(0.0f, 0.0f, -50.0f),
   //      1.0f, 0.0f, 0.0f
   //   )
   //);

   //m_shapes.push_back(
   //   std::make_unique<ogl::Rectangle>(
   //      220.0f, 55.0f, 1.0f, 0.0f, 0.0f
   //   )
   //);

   m_shapes.push_back(
      std::make_unique<Square>(
         "shader/texture.vs",
         "shader/texture.fs",
         "images/container.jpg"
         )
   );

   //m_shapes.push_back(
   //   std::make_unique<Square>(
   //      "shader/texture.vs",
   //      "shader/texture.fs",
   //      "images/awesomeface.png"
   //      )
   //);

}

ogl::Size GameEngine::getWindowSize()
{
   int width{ 0 };
   int height{ 0 };

   SDL_GL_GetDrawableSize(m_window.get(), &width, &height);

   return { width, height };
}
