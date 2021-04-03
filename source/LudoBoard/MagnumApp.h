#pragma once

#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Shaders/VertexColor.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/MeshTools/CompressIndices.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/Shaders/Phong.h>
#include <Magnum/Trade/MeshData.h>

using namespace Magnum;

class TriangleExample : public Platform::Application
{
public:
   explicit TriangleExample(const Arguments& arguments);

private:
   void drawEvent() override;
   void mousePressEvent(MouseEvent& event) override;
   void mouseReleaseEvent(MouseEvent& event) override;
   void mouseMoveEvent(MouseMoveEvent& event) override;

   GL::Mesh m_mesh;
   Shaders::Phong m_shader;

   Matrix4 m_transformation;
   Matrix4 m_projection;
   Color3 m_color;
};

