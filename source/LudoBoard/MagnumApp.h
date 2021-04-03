#pragma once

#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Shaders/VertexColor.h>

using namespace Magnum;

class TriangleExample : public Platform::Application
{
public:
   explicit TriangleExample(const Arguments& arguments);

private:
   void drawEvent() override;

   GL::Mesh _mesh;
   Shaders::VertexColor2D _shader;
};

