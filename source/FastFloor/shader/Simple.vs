#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
  
out vec4 vertexColor;      // output a color to the fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0);
    vertexColor = vec4(aColor, 1.0);
}