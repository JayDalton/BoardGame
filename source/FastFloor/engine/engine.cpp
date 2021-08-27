#include "engine.h"

#include "objects/shapes/line.hpp"
#include "objects/shapes/cuboid.hpp"
#include "objects/shapes/rectangle.hpp"


GameEngine::GameEngine(std::string_view title)
   : m_title(title)
{

}

bool GameEngine::construct(int w, int h)
{
   using std::cout;
   using std::endl;

   const auto start = StopClock::now();

   if (auto system = sdl2::make_sdlsystem(SDL_INIT_VIDEO | SDL_INIT_TIMER))
   {
      m_system = std::move(system);
      cout << "init system " << (StopClock::now() - start) << endl;
   }
   else
   {
      cout << "Error creating SDL2 system: " << SDL_GetError() << endl;
      return false;
   }

   /* Setting up OpenGL version and profile details for context creation */
   //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

   Uint32 windowFlags{ SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL };

   if (auto win = sdl2::make_window(m_title.data(), 
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      w, h, windowFlags))
   {
      m_window = std::move(win); // Context ???
      cout << "init window " << (StopClock::now() - start) << endl;
   }
   else
   {
      cout << "Error creating window: " << SDL_GetError() << endl;
      return false;
   }

   if (!SDL_GL_CreateContext(m_window.get()))
   {
      cout << "Error creating context: " << SDL_GetError() << endl;
      return false;
   }

   int get1 = 0, get2 = 0;

   auto res1 = SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &get1);
   auto res2 = SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &get2);

   /* Loading Extensions */
   glewExperimental = GL_TRUE;
   if (auto res = glewInit())
   {
      cout << std::format("GLEW init failed: {}", res) << endl;
      return false;
   }
   auto error = glGetError();

   if (GLEW_VERSION_2_1)
   {
      auto error = glGetError();
   }

   if (GLEW_VERSION_3_2)
   {
      auto error = glGetError();
   }

   if (GLEW_VERSION_3_3)
   {
      auto error = glGetError();
   }

   if (GLEW_VERSION_4_4)
   {
      auto error = glGetError();
   }

   if (GLEW_VERSION_4_5)
   {
      auto error = glGetError();
   }

   if (GLEW_VERSION_4_6)
   {
      auto error = glGetError();
   }

   //Use Vsync
   if (SDL_GL_SetSwapInterval(1) < 0)
   {
      cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << endl;
      return false;
   }
   error = glGetError();
   //Initialize OpenGL
   initWindow();
   //initOpenGL();

   if (!initOpenGL())
   {
      cout << std::format("Unable to initialize OpenGL!\n");
      return false;
   }
   error = glGetError();

   Uint32 renderFlags{ SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC };

   if (auto ren = sdl2::make_renderer(m_window.get(), -1, renderFlags))
   {
      m_render = std::move(ren);
      cout << "init render " << (StopClock::now() - start) << endl;
   }
   else
   {
      cout << "Error creating renderer: " << SDL_GetError() << endl;
      return false;
   }
   error = glGetError();

   initCamera();
   error = glGetError();
   //initLights();
   error = glGetError();
   error = glGetError();
   initGeometry();
   error = glGetError();

   cout << "init geometry " << (StopClock::now() - start) << endl;

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

   auto file = SDL_RWFromFile("img/grumpy-cat.bmp", "rb");
   if (file == nullptr) {
      cerr << "Error reading file: " << SDL_GetError() << endl;
      return;
   }
   error = glGetError();

   auto bmp = sdl2::make_bmp(file);
   if (!bmp) {
      cerr << "Error creating surface: " << SDL_GetError() << endl;
      return;
   }
   error = glGetError();

   auto tex = sdl2::make_texture(m_render.get(), bmp.get());
   if (!tex) {
      cerr << "Error creating texture: " << SDL_GetError() << endl;
      return;
   }
   error = glGetError();

   // An array of 3 vectors which represents 3 vertices
   static const GLfloat g_vertex_buffer_data[] = {
      -1.0f, -1.0f, 0.0f,
      1.0f, -1.0f, 0.0f,
      0.0f,  1.0f, 0.0f,
   };

   // This will identify our vertex buffer
   GLuint vertexbuffer;
   // Generate 1 buffer, put the resulting identifier in vertexbuffer
   glGenBuffers(1, &vertexbuffer);
   // The following commands will talk about our 'vertexbuffer' buffer
   glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
   // Give our vertices to OpenGL.
   glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

   error = glGetError();

   auto programID = loadShader("shader/SimpleVertexShader", "shader/SimpleFragmentShader");

   if (auto error = glGetError())
   {
      cout << std::format("Error {} {}\n", error, *gluErrorString(error));
   }

   m_timer = StopClock::now();

   // annimation loop
   while (m_running)
   {
      SDL_Event event;
      while (SDL_PollEvent(&event))
      {
         OnEvent(event);
      }

      //OnReceive(); // io server
      //updateUser();
      //OnUpdate(getDuration(m_timer));
      // timer reset?

      auto [width, height] = getWindowSize();

      if (auto error = glGetError())
      {
         cout << std::format("Error {} {}\n", error, *gluErrorString(error));
      }

      glViewport(0, 0, width, height);
      //glClearColor(1.f, 0.f, 1.f, 0.f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
      //OnRender();
      error = glGetError();

      // Use our shader
      //glUseProgram(programID);
      error = glGetError();

      // 1st attribute buffer : vertices
      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
      glVertexAttribPointer(
         0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
         3,                  // size
         GL_FLOAT,           // type
         GL_FALSE,           // normalized?
         0,                  // stride
         (void*)0            // array buffer offset
      );

      if (auto error = glGetError())
      {
         cout << std::format("Error {} {}\n", error, *gluErrorString(error));
      }
      // Draw the triangle !
      glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
      if (auto error = glGetError())
      {
         bool a1 = GL_INVALID_ENUM == error;
         bool a2 = GL_INVALID_VALUE == error;
         bool a3 = GL_INVALID_OPERATION == error;
         cout << std::format("Error {} {}\n", error, *gluErrorString(error));
      }
      glDisableVertexAttribArray(0);
      if (auto error = glGetError())
      {
         cout << std::format("Error {} {}\n", error, *gluErrorString(error));
      }

      SDL_GL_SwapWindow(m_window.get());

      using namespace std::literals;

      m_frames++;
      if (1s < getDuration(m_timer))
      {
         setWindowTitle(std::format(" FPS {:5}", m_frames));
         cout << m_frames << " fps" << std::endl;
         m_timer = StopClock::now();
         m_frames = 0;
      }

      // calculates to 60 fps
      SDL_Delay(1000 / 60);
   }
}

GameEngine::Duration GameEngine::getDuration(const StopClock::time_point& start)
{
   return std::chrono::duration_cast<Duration>(StopClock::now() - start);
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
   for (auto& shape : m_shapes)
   {
      shape->update(duration);
   }
}

void GameEngine::OnRender()
{
   auto [width, height] = getWindowSize();
   //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

   // MainWindow
   glViewport(0, 0, width, height);
   for (auto& shape : m_shapes) 
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

   //window->display();

}

void GameEngine::initWindow()
{

}

bool GameEngine::initOpenGL()
{
   //using std::cerr;
   using std::cout;
   using std::endl;

   //glShadeModel(GL_SMOOTH);                    // shading method: GL_SMOOTH or GL_FLAT

   //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                   // background color
   //glClearDepth(1.0f);                         // 0 is near, 1 is far
   //glEnable(GL_DEPTH_TEST);
   //glDepthFunc(GL_LEQUAL);

   //glEnable(GL_CULL_FACE);
   //glEnable(GL_NORMALIZE);
   //glEnable(GL_COLOR_MATERIAL);
   //glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

   //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   //glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
   //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
   //glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

   //glClearStencil(0);                          // clear stencil buffer

   bool success = true;
   GLenum error = GL_NO_ERROR;

   ////Initialize Projection Matrix
   //glMatrixMode(GL_PROJECTION);
   //glLoadIdentity();

   ////Check for error
   //error = glGetError();
   //if (error != GL_NO_ERROR)
   //{
   //   cout << std::format("Error initializing OpenGL! {}\n", *gluErrorString(error));
   //   success = false;
   //}

   ////Initialize Modelview Matrix
   //glMatrixMode(GL_MODELVIEW);
   //glLoadIdentity();

   ////Check for error
   //error = glGetError();
   //if (error != GL_NO_ERROR)
   //{
   //   cout << std::format("Error initializing OpenGL! {}\n", *gluErrorString(error));
   //   success = false;
   //}

   //Initialize clear color
   glClearColor(0.f, 0.f, 0.f, 1.f);

   //Check for error
   error = glGetError();
   if (error != GL_NO_ERROR)
   {
      cout << std::format("Error initializing OpenGL! {}\n", *gluErrorString(error));
      success = false;
   }

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
