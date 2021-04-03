#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#define GLM_FORCE_MESSAGES // eport the configuration as part of the build log
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <gl/GL.h>
#include <gl/GLU.h>

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
   glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
   glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
   View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
   View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
   glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
   return Projection * View * Model;
}

double zoom = 8.0;
double drehx = 0.0;
double drehy = 0.0;
double drehz = 0.0;
static GLuint texName;

void init(void)
{
   //GLTXimage* i;
   //GLMmodel* m;

   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };		// Farbe der Lichtquelle
   GLfloat mat_shininess[] = { 50.0 };					// Gr��e der Lichtquelle

   GLfloat light_position1[] = { 1.0, 1.0, 1.0, 0.0 };	// Position der Lichtquelle, letzter Wert -> Unendlichkeit
   GLfloat light_position2[] = { -1.0, 1.0, 1.0, 0.0 };

   GLfloat color_red[] = { 1, 0, 0, 1 };
   GLfloat color_green[] = { 0, 1, 0, 1 };


   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

   glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, color_red);

   glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, color_green);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_NORMALIZE);

   /* Begin Import Texturen */
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
   /* Ende Import Texturen */

   //i = gltxReadRGB("paisley.rgb");

   ///* Import OBJ Datei */
   //m = glmReadOBJ("teddy.obj");
   //glmUnitize(m);
   //glmFacetNormals(m);
   //glmVertexNormals(m, 80.0);
   //id = glmList(m, GLM_SMOOTH);

   //glTexImage2D(GL_TEXTURE_2D, 0, i->components, i->width, i->height, 0, GL_RGB, GL_UNSIGNED_BYTE, i->data);

}


int main()
{
   sf::Window window(sf::VideoMode(800, 600), "SFML OpenGL", sf::Style::Default, sf::ContextSettings(32));
   window.setVerticalSyncEnabled(true);

   // activate the window
   window.setActive(true);

   // load resources, initialize the OpenGL states, ...

   // run the main loop
   bool running = true;
   while (running)
   {
      // handle events
      sf::Event event;
      while (window.pollEvent(event))
      {
         if (event.type == sf::Event::Closed)
         {
            // end the program
            running = false;
         }
         else if (event.type == sf::Event::Resized)
         {
            // adjust the viewport when the window is resized
            glViewport(0, 0, event.size.width, event.size.height);
         }
      }

      // clear the buffers
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // draw...

      // end the current frame (internally swaps the front and back buffers)
      window.display();
   }

   // release resources...

   return 0;
}
