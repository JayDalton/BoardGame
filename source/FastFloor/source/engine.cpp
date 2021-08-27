#include "engine.h"

#include "shapes/line.hpp"
#include "shapes/cuboid.hpp"
#include "shapes/rectangle.hpp"

#define STB_IMAGE_IMPLEMENTATION
//#include "image.h"
#include <stb_image.h>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//// camera
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

//bool firstMouse = true;
//float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
//float pitch = 0.0f;
//float lastX = 800.0f / 2.0;
//float lastY = 600.0 / 2.0;
//float fov = 45.0f;

//// timing
//float deltaTime = 0.0f;	// time between current frame and last frame
//float lastFrame = 0.0f;


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
   //initGeometry();

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

    Shader ourShader("shader/texture.vs", "shader/texture.fs");

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
    ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
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
      //OnRender();

      glm::mat4 trans = glm::mat4(1.0f);
      trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
      trans = glm::rotate(trans, (float)SDL_GetTicks(), glm::vec3(0.0f, 0.0f, 1.0f));

      unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

      // Renderziel
      auto [width, height] = getWindowSize();
      glViewport(0, 0, width, height);

      // Hintergrund
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);


      // bind textures on corresponding texture units
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, texture1);
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, texture2);

      // render container
      ourShader.use();
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
   for (auto& shape : m_shapes)
   {
      shape->update(duration);
   }
}

void GameEngine::OnRenderWorld()
{
   //auto [width, height] = getWindowSize();
   ////glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

   //// MainWindow
   //glViewport(0, 0, width, height);
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

   //window->display();

}

void GameEngine::initWindow()
{

}

bool GameEngine::initOpenGL()
{
   using std::cout;
   using std::endl;

   glEnable(GL_DEPTH_TEST);

   bool success = true;

   return success;
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
   auto error = glGetError();

   GLfloat mat_ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
   GLfloat mat_diffuse[] = { 0.4f, 0.8f, 0.4f, 1.0f };
   GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
   GLfloat mat_shininess[] = { 50.0f };

   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   error = glGetError();
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   error = glGetError();
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   error = glGetError();
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   error = glGetError();

   GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0 };
   GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
   GLfloat light_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
   GLfloat light_position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

   glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
   error = glGetError();
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   error = glGetError();
   glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
   error = glGetError();
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   error = glGetError();

   error = glGetError();

   glEnable(GL_COLOR_MATERIAL);
   error = glGetError();
   glEnable(GL_LIGHTING);
   error = glGetError();
   glEnable(GL_LIGHT0);
   error = glGetError();
}

//In C++17, we could take a `std::filesystem::path` instead of a std::string
//for the filename.
GLuint CreateShaderObject(GLenum stage, const std::string& filename)
{
   auto error = glGetError();

   std::ifstream input(filename.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

   //Figure out how big the file is.
   auto fileSize = input.tellg();
   input.seekg(0, std::ios::beg);

   //Read the whole file.
   std::string fileData(fileSize, 0);
   input.read(&fileData[0], fileSize);
   input.close();

   //Create a shader name
   auto shader = glCreateShader(stage);
   error = glGetError();

   //Send the shader source code to GL
   auto fileCstr = (const GLchar*)fileData.c_str();
   glShaderSource(shader, 1, &fileCstr, nullptr);
   error = glGetError();

   //Compile the shader
   glCompileShader(shader);
   error = glGetError();

   GLint isCompiled = 0;
   glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
   error = glGetError();
   if (isCompiled == GL_FALSE)
   {
      GLint maxLength = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

      //C++11 does not permit you to overwrite the NUL terminator,
      //even if you are overwriting it with the NUL terminator.
      //C++17 does, so you could subtract 1 from the length and skip the `pop_back`.
      std::basic_string<GLchar> infoLog(maxLength, 0);
      glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
      infoLog.pop_back();

      //We don't need the shader anymore.
      glDeleteShader(shader);

      //Use the infoLog as you see fit.

      //Exit with failure.
      return 0;
   }

   return shader;
}

GLuint LinkProgramObject(std::vector<GLuint> shaders)
{
   auto error = glGetError();

   //Get a program object.
   auto program = glCreateProgram();

   //Attach our shaders to our program
   for (auto shader : shaders)
   {
      glAttachShader(program, shader);
      error = glGetError();
   }

   //Link our program
   glLinkProgram(program);
   error = glGetError();

   //Note the different functions here: glGetProgram* instead of glGetShader*.
   GLint isLinked = 0;
   glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
   error = glGetError();
   if (isLinked == GL_FALSE)
   {
      GLint maxLength = 0;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

      //C++11 does not permit you to overwrite the NUL terminator,
      //even if you are overwriting it with the NUL terminator.
      //C++17 does, so you could subtract 1 from the length and skip the `pop_back`.
      std::basic_string<GLchar> infoLog(maxLength, 0);
      glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
      infoLog.pop_back();

      //We don't need the program anymore.
      glDeleteProgram(program);

      //Use the infoLog as you see fit.

      //Exit with failure
      return 0;
   }

   //Always detach shaders after a successful link.
   for (auto shader : shaders)
   {
      glDetachShader(program, shader);
      error = glGetError();
   }

   return program;
}

unsigned GameEngine::loadShader(std::string_view vertex, std::string_view fragment)
{
   auto error = glGetError();

   // Create the shaders
   GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
   GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
   error = glGetError();

   // Read the Vertex Shader code from the file
   std::string VertexShaderCode;
   std::ifstream VertexShaderStream(vertex.data(), std::ios::in);
   if (VertexShaderStream.is_open()) {
      std::stringstream sstr;
      sstr << VertexShaderStream.rdbuf();
      VertexShaderCode = sstr.str();
      VertexShaderStream.close();
   }
   else {
      std::cout << std::format("Impossible to open {}. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex);
      getchar();
      return 0;
   }

   // Read the Fragment Shader code from the file
   std::string FragmentShaderCode;
   std::ifstream FragmentShaderStream(fragment.data(), std::ios::in);
   if (FragmentShaderStream.is_open()) {
      std::stringstream sstr;
      sstr << FragmentShaderStream.rdbuf();
      FragmentShaderCode = sstr.str();
      FragmentShaderStream.close();
   }

   error = glGetError();

   GLint Result = GL_FALSE;
   int InfoLogLength;

   // Compile Vertex Shader
   std::cout << std::format("Compiling shader : {}\n", vertex);
   char const* VertexSourcePointer = VertexShaderCode.c_str();
   glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
   glCompileShader(VertexShaderID);
   error = glGetError();

   // Check Vertex Shader
   glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
   glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
   if (InfoLogLength > 0) {
      std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
      glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
      std::cout << std::format("%s\n", &VertexShaderErrorMessage[0]);
   }
   error = glGetError();

   // Compile Fragment Shader
   std::cout << std::format("Compiling shader : {}\n", fragment);
   char const* FragmentSourcePointer = FragmentShaderCode.c_str();
   glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
   glCompileShader(FragmentShaderID);
   error = glGetError();

   // Check Fragment Shader
   glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
   glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
   if (InfoLogLength > 0) {
      std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
      glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
      std::cout << std::format("%s\n", &FragmentShaderErrorMessage[0]);
   }
   error = glGetError();

   // Link the program
   std::cout << std::format("Linking program\n");
   GLuint ProgramID = glCreateProgram();
   glAttachShader(ProgramID, VertexShaderID);
   glAttachShader(ProgramID, FragmentShaderID);
   glLinkProgram(ProgramID);
   error = glGetError();

   // Check the program
   glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
   glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
   if (InfoLogLength > 0) {
      std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
      glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
      std::cout << std::format("%s\n", &ProgramErrorMessage[0]);
   }
   error = glGetError();

   glDetachShader(ProgramID, VertexShaderID);
   glDetachShader(ProgramID, FragmentShaderID);
   error = glGetError();

   glDeleteShader(VertexShaderID);
   glDeleteShader(FragmentShaderID);
   error = glGetError();

   return ProgramID;
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

   SDL_GL_GetDrawableSize(m_window.get(), &width, &height);

   return { width, height };
}
