#include "MagnumApp.h"

TriangleExample::TriangleExample(const Arguments& arguments)
   : Platform::Application{arguments, Configuration{}.setTitle("Magnum Triangle Example")}
{
   using namespace Math::Literals;

   struct TriangleVertex {
      Vector2 position;
      Color3 color;
   };

   const TriangleVertex data[]{
       {{-0.5f, -0.5f}, 0xff0000_rgbf},    /* Left vertex, red color */
       {{ 0.5f, -0.5f}, 0x00ff00_rgbf},    /* Right vertex, green color */
       {{ 0.0f,  0.5f}, 0x0000ff_rgbf}     /* Top vertex, blue color */
   };

   GL::Buffer buffer;
   buffer.setData(data);

   _mesh.setCount(3).addVertexBuffer(
      std::move(buffer), 0,
      Shaders::VertexColor2D::Position{},
      Shaders::VertexColor2D::Color3{}
   );
}

void TriangleExample::drawEvent() 
{
   GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);

   _shader.draw(_mesh);

   swapBuffers();
}

