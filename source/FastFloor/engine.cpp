#include "engine.h"


GameEngine::GameEngine(std::string_view title)
   : m_title(title)
{

}

bool GameEngine::construct(int x, int y, int w, int h)
{
   using std::cerr;
   using std::endl;

   if (auto system = sdl2::make_sdlsystem(SDL_INIT_EVERYTHING))
   {
      m_system = std::move(system);
   }
   else
   {
      cerr << "Error creating SDL2 system: " << SDL_GetError() << endl;
      return false;
   }


   Uint32 windowFlags{ SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL };

   if (auto win = sdl2::make_window(m_title.data(), x, y, w, h, windowFlags))
   {
      m_window = std::move(win);
      SDL_GLContext Context = SDL_GL_CreateContext(m_window.get());
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

   return true;
}

void GameEngine::setWindowTitle(std::string label)
{
   SDL_SetWindowTitle(m_window.get(), std::format("{} {}", m_title, label).c_str());
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

   SDL_Rect dest{ 50, 50, 70, 20 };

   int close = 0;
   int speed = 300;


   // annimation loop
   while (!close)
   {
      // Handle Timing
      m_tp2 = std::chrono::steady_clock::now();
   
      std::chrono::duration<float> elapsedTime = m_tp2 - m_tp1;
      auto elapsedTime2 = m_tp2 - m_tp1;

      m_tp1 = m_tp2;

      SDL_Event event;
      // Events management
      while (SDL_PollEvent(&event))
      {
         switch (event.type)
         {

         case SDL_QUIT:
            // handling of close button
            close = 1;
            break;

         case SDL_KEYDOWN:
            // keyboard API for key pressed
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
               dest.y -= speed / 30;
               break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
               dest.x -= speed / 30;
               break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
               dest.y += speed / 30;
               break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
               dest.x += speed / 30;
               break;
            default:
               break;
            }
         }
      }

      updateUser();

      //// right boundary
      //if (dest.x + dest.w > 1000)
      //   dest.x = 1000 - dest.w;

      //// left boundary
      //if (dest.x < 0)
      //   dest.x = 0;

      //// bottom boundary
      //if (dest.y + dest.h > 1000)
      //   dest.y = 1000 - dest.h;

      //// upper boundary
      //if (dest.y < 0)
      //   dest.y = 0;

      //// clears the screen
      //SDL_RenderClear(m_render.get());
      //SDL_RenderCopy(m_render.get(), tex.get(), nullptr, &dest);

      ////SDL_SetRenderDrawColor(ren.get(), 255, 0, 0, 128);
      ////SDL_RenderFillRect(ren.get(), &dest);

      //// triggers the double buffers
      //// for multiple rendering
      //SDL_RenderPresent(m_render.get());

      //// calculates to 60 fps
      //SDL_Delay(1000 / 60);

      glViewport(0, 0, 600, 400);
      glClearColor(1.f, 0.f, 1.f, 0.f);
      glClear(GL_COLOR_BUFFER_BIT);

      SDL_GL_SwapWindow(m_window.get());
   }

}
