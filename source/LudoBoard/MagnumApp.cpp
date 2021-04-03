#include "MagnumApp.h"

using namespace Math::Literals;

TriangleExample::TriangleExample(const Arguments& arguments)
   : Platform::Application{arguments, Configuration{}
   .setTitle("Primitives Example") }
{
   GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
   GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);

   Trade::MeshData cube = Primitives::cubeSolid();

   GL::Buffer vertices;
   vertices.setData(MeshTools::interleave(
      cube.positions3DAsArray(),
      cube.normalsAsArray())
   );


   std::pair<Containers::Array<char>, MeshIndexType> compressed =
      MeshTools::compressIndices(cube.indicesAsArray());

   GL::Buffer indices;
   indices.setData(compressed.first);

   m_mesh.setPrimitive(cube.primitive())
      .setCount(cube.indexCount())
      .addVertexBuffer(
         std::move(vertices), 0, 
         Shaders::Phong::Position{},
         Shaders::Phong::Normal{})
      .setIndexBuffer(std::move(indices), 0, compressed.second);

   //_mesh = MeshTools::compile(Primitives::cubeSolid());

   m_transformation = Matrix4::rotationX(30.0_degf) * Matrix4::rotationY(40.0_degf);
   m_projection = Matrix4::perspectiveProjection(
      35.0_degf, 
      Vector2{ windowSize() }
      .aspectRatio()
      , 0.01f
      , 100.0f)
      * Matrix4::translation(Vector3::zAxis(-10.0f));
   m_color = Color3::fromHsv({35.0_degf, 1.0f, 1.0f});

}

void TriangleExample::drawEvent() 
{
   GL::defaultFramebuffer.clear(GL::FramebufferClear::Color|GL::FramebufferClear::Depth);

   m_shader.setLightPositions({ {1.4f, 1.0f, 0.75f} })
      .setDiffuseColor(m_color)
      .setAmbientColor(Color3::fromHsv({m_color.hue(), 1.0f, 0.3f}))
      .setTransformationMatrix(m_transformation)
      .setNormalMatrix(m_transformation.normalMatrix())
      .setProjectionMatrix(m_projection)
      .draw(m_mesh);

   swapBuffers();
}

void TriangleExample::mousePressEvent(MouseEvent& event)
{
   if (event.button() != MouseEvent::Button::Left)
   {
      return;
   }

   event.setAccepted();
}

void TriangleExample::mouseReleaseEvent(MouseEvent& event)
{
   m_color = Color3::fromHsv({m_color.hue() + 50.0_degf, 1.0f, 1.0f});

   event.setAccepted();
   redraw();
}

void TriangleExample::mouseMoveEvent(MouseMoveEvent& event)
{
   if (!(event.buttons() & MouseMoveEvent::Button::Left))
   {
      return;
   }

   Vector2 delta = 3.0f * Vector2{event.relativePosition()} / Vector2{windowSize()};

   m_transformation = Matrix4::rotationX(Rad{delta.y()})
      * m_transformation
      * Matrix4::rotationY(Rad{delta.x()});

   event.setAccepted();
   redraw();
}


