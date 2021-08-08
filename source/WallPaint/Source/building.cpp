/*
 * building.cpp
 *
 *  Created on: Jan 8, 2013
 *      Author: arend
 */

#include "building.hpp"
float Building::SCALE = 10.0f;

//All Dimensions in Meter
float Building::HEIGHT = 12.965f;
float Building::WIDTH = 13.5f;
float Building::FLOOR_1_HEIGHT = 5.965f;
float Building::FLOOR_2_HEIGHT = 9.465f;
float Building::WINDOW_HEIGHT = 1.75f;

float Building::SIDE_DEPTH = 1.645f + (3.0f * 2.7f);
float Building::SIDE_MIDDLE_Z = (SIDE_DEPTH / 2.0f);

float Building::LED_HEIGHT = 2.0f;    // TODO: Led Team richtige maße eintragen!
float Building::LED_WIDTH = 5.0f;     // TODO: Led Team richtige maße eintragen!

//All Dimensions in Meter
//const static float BUILDING_HEIGHT = 12.965f;
#define HEIGHT_FIRST_START 5.965f
#define HEIGHT_FIRST_END 7.715f

#define HEIGHT_SECOND_START 9.465f
#define HEIGHT_SECOND_END 11.215f


//const static float BUILDING_WIDTH = 13.5f;
#define HALF_WIDTH_FRONT WIDTH_FRONT/2.0f

#define LEFT_WIDTH 5.20f + 1.80f
#define RIGHT_WIDTH 6.02f

//Reference: Dropbox/public_adrian/Projektstudium/00_Docs/Medienfassade Ansichten/06_04_11_Ansichten_VPU-1.pdf

//Front
//Horizontal Bottom to top
#define H0      0.0f
//#define H1
#define H2      3.235f
#define H3      4.515f
#define H4      5.965f
#define H5      7.715f
#define H6      9.465f
#define H7      11.215f
#define H8      12.965f


//Vertical  left to right
#define V0      0.0f
#define V1      1.35f
#define V2      V1 + 2.7f
#define V3      V2 + 2.7f
#define V4      V3 + 2.7f
#define V5      V4 + 2.7f
#define V6      V5 + 1.35f

#define V_HALF V6 / 2.0f // X/2

//Side (z_axis)
#define VS0    0.0
#define VS1    -1.645f
#define VS2    VS1 - 2.7f
#define VS3    VS2 - 2.7f
#define VS4    VS3 - 2.7f


Building::Building() {
    m_scale = SCALE;
    //Outer Frame
    //geometry.push_back(new Line( glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, HEIGHT_OVERALL, 0.0f)));
    //geometry.push_back(new Line( glm::vec3(0.0f, HEIGHT_OVERALL, 0.0f), glm::vec3(WIDTH_FRONT, HEIGHT_OVERALL, 0.0f)));
    //geometry.push_back(new Line( glm::vec3(WIDTH_FRONT, HEIGHT_OVERALL, 0.0f), glm::vec3(WIDTH_FRONT, 0.0f, 0.0f)));

    //Horizontal bottom to top
    //H0
    geometry.push_back(new Line( glm::vec3(V0, H0, 0.0f), glm::vec3(V1, H0, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V1, H0, 0.0f), glm::vec3(V2, H0, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V2, H0, 0.0f), glm::vec3(V3, H0, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V3, H0, 0.0f), glm::vec3(V4, H0, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V4, H0, 0.0f), glm::vec3(V5, H0, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V5, H0, 0.0f), glm::vec3(V6, H0, 0.0f)));
    //H1
    //geometry.push_back(new Line( glm::vec3(H1, V0, 0.0f), glm::vec3(H1, V6, 0.0f)));
    //H2

    geometry.push_back(new Line( glm::vec3(V0, H2, 0.0f), glm::vec3(V1, H2, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V1, H2, 0.0f), glm::vec3(V2, H2, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V2, H2, 0.0f), glm::vec3(V3, H2, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V3, H2, 0.0f), glm::vec3(V4, H2, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V4, H2, 0.0f), glm::vec3(V5, H2, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V5, H2, 0.0f), glm::vec3(V6, H2, 0.0f)));

    //H3
    geometry.push_back(new Line( glm::vec3(V0, H3, 0.0f), glm::vec3(V1, H3, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V1, H3, 0.0f), glm::vec3(V2, H3, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V2, H3, 0.0f), glm::vec3(V3, H3, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V3, H3, 0.0f), glm::vec3(V4, H3, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V4, H3, 0.0f), glm::vec3(V5, H3, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V5, H3, 0.0f), glm::vec3(V6, H3, 0.0f)));

    //H4
    geometry.push_back(new Line( glm::vec3(V0, H4, 0.0f), glm::vec3(V1, H4, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V1, H4, 0.0f), glm::vec3(V2, H4, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V2, H4, 0.0f), glm::vec3(V3, H4, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V3, H4, 0.0f), glm::vec3(V4, H4, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V4, H4, 0.0f), glm::vec3(V5, H4, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V5, H4, 0.0f), glm::vec3(V6, H4, 0.0f)));

    //H5
    geometry.push_back(new Line( glm::vec3(V0, H5, 0.0f), glm::vec3(V1, H5, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V1, H5, 0.0f), glm::vec3(V2, H5, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V2, H5, 0.0f), glm::vec3(V3, H5, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V3, H5, 0.0f), glm::vec3(V4, H5, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V4, H5, 0.0f), glm::vec3(V5, H5, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V5, H5, 0.0f), glm::vec3(V6, H5, 0.0f)));

    //H6
    geometry.push_back(new Line( glm::vec3(V0, H6, 0.0f), glm::vec3(V1, H6, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V1, H6, 0.0f), glm::vec3(V2, H6, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V2, H6, 0.0f), glm::vec3(V3, H6, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V3, H6, 0.0f), glm::vec3(V4, H6, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V4, H6, 0.0f), glm::vec3(V5, H6, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V5, H6, 0.0f), glm::vec3(V6, H6, 0.0f)));

    //H7
    geometry.push_back(new Line( glm::vec3(V0, H7, 0.0f), glm::vec3(V1, H7, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V1, H7, 0.0f), glm::vec3(V2, H7, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V2, H7, 0.0f), glm::vec3(V3, H7, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V3, H7, 0.0f), glm::vec3(V4, H7, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V4, H7, 0.0f), glm::vec3(V5, H7, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V5, H7, 0.0f), glm::vec3(V6, H7, 0.0f)));

    //H8
    geometry.push_back(new Line( glm::vec3(V0, H8, 0.0f), glm::vec3(V1, H8, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V1, H8, 0.0f), glm::vec3(V2, H8, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V2, H8, 0.0f), glm::vec3(V3, H8, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V3, H8, 0.0f), glm::vec3(V4, H8, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V4, H8, 0.0f), glm::vec3(V5, H8, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V5, H8, 0.0f), glm::vec3(V6, H8, 0.0f)));


    //Vertical left to right
    //V0
    geometry.push_back(new Line( glm::vec3(V0, H0, 0.0f), glm::vec3(V0, H2, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V0, H2, 0.0f), glm::vec3(V0, H3, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V0, H3, 0.0f), glm::vec3(V0, H4, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V0, H4, 0.0f), glm::vec3(V0, H5, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V0, H5, 0.0f), glm::vec3(V0, H6, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V0, H6, 0.0f), glm::vec3(V0, H7, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V0, H7, 0.0f), glm::vec3(V0, H8, 0.0f)));

    //V1
    geometry.push_back(new Line( glm::vec3(V1, H0, 0.0f), glm::vec3(V1, H2, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V1, H2, 0.0f), glm::vec3(V1, H3, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V1, H3, 0.0f), glm::vec3(V1, H4, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V1, H4, 0.0f), glm::vec3(V1, H5, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V1, H5, 0.0f), glm::vec3(V1, H6, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V1, H6, 0.0f), glm::vec3(V1, H7, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V1, H7, 0.0f), glm::vec3(V1, H8, 0.0f)));

    //V2
    geometry.push_back(new Line( glm::vec3(V2, H0, 0.0f), glm::vec3(V2, H2, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V2, H2, 0.0f), glm::vec3(V2, H3, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V2, H3, 0.0f), glm::vec3(V2, H4, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V2, H4, 0.0f), glm::vec3(V2, H5, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V2, H5, 0.0f), glm::vec3(V2, H6, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V2, H6, 0.0f), glm::vec3(V2, H7, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V2, H7, 0.0f), glm::vec3(V2, H8, 0.0f)));

    //V3
    geometry.push_back(new Line( glm::vec3(V3, H0, 0.0f), glm::vec3(V3, H2, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V3, H2, 0.0f), glm::vec3(V3, H3, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V3, H3, 0.0f), glm::vec3(V3, H4, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V3, H4, 0.0f), glm::vec3(V3, H5, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V3, H5, 0.0f), glm::vec3(V3, H6, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V3, H6, 0.0f), glm::vec3(V3, H7, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V3, H7, 0.0f), glm::vec3(V3, H8, 0.0f)));

    //V4
    geometry.push_back(new Line( glm::vec3(V4, H0, 0.0f), glm::vec3(V4, H2, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V4, H2, 0.0f), glm::vec3(V4, H3, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V4, H3, 0.0f), glm::vec3(V4, H4, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V4, H4, 0.0f), glm::vec3(V4, H5, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V4, H5, 0.0f), glm::vec3(V4, H6, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V4, H6, 0.0f), glm::vec3(V4, H7, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V4, H7, 0.0f), glm::vec3(V4, H8, 0.0f)));

    //V5
    geometry.push_back(new Line( glm::vec3(V5, H0, 0.0f), glm::vec3(V5, H2, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V5, H2, 0.0f), glm::vec3(V5, H3, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V5, H3, 0.0f), glm::vec3(V5, H4, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V5, H4, 0.0f), glm::vec3(V5, H5, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V5, H5, 0.0f), glm::vec3(V5, H6, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V5, H6, 0.0f), glm::vec3(V5, H7, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V5, H7, 0.0f), glm::vec3(V5, H8, 0.0f)));

    //V6
    geometry.push_back(new Line( glm::vec3(V6, H0, 0.0f), glm::vec3(V6, H2, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V6, H2, 0.0f), glm::vec3(V6, H3, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V6, H3, 0.0f), glm::vec3(V6, H4, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V6, H4, 0.0f), glm::vec3(V6, H5, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V6, H5, 0.0f), glm::vec3(V6, H6, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V6, H6, 0.0f), glm::vec3(V6, H7, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V6, H7, 0.0f), glm::vec3(V6, H8, 0.0f)));



    /*Alte druchgehenden Linien*/
    //Horizontal bottom to top
    /*
    geometry.push_back(new Line( glm::vec3(V0, H0, 0.0f), glm::vec3(V6, H0, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V0, H2, 0.0f), glm::vec3(V6, H2, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V0, H3, 0.0f), glm::vec3(V6, H3, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V0, H4, 0.0f), glm::vec3(V6, H4, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V0, H5, 0.0f), glm::vec3(V6, H5, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V0, H6, 0.0f), glm::vec3(V6, H6, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V0, H7, 0.0f), glm::vec3(V6, H7, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V0, H8, 0.0f), glm::vec3(V6, H8, 0.0f)));
    //Vertical left to right
    geometry.push_back(new Line( glm::vec3(V0, H0, 0.0f), glm::vec3(V0, H8, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V1, H0, 0.0f), glm::vec3(V1, H8, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V2, H0, 0.0f), glm::vec3(V2, H8, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V3, H0, 0.0f), glm::vec3(V3, H8, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V4, H0, 0.0f), glm::vec3(V4, H8, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V5, H0, 0.0f), glm::vec3(V5, H8, 0.0f)));
    geometry.push_back(new Line( glm::vec3(V6, H0, 0.0f), glm::vec3(V6, H8, 0.0f)));
    */
    //Square(glm::vec3 bottom_left, glm::vec3 bottom_right, glm::vec3 top_right, glm::vec3 top_left);
    //"Walls" left to right - bottom to top
    //H0 -> H2
    geometry.push_back(new Square(glm::vec3(V0, H0, 0.0f), glm::vec3(V1, H0, 0.0f), glm::vec3(V1, H2, 0.0f), glm::vec3(V0, H2, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V1, H0, 0.0f), glm::vec3(V2, H0, 0.0f), glm::vec3(V2, H2, 0.0f), glm::vec3(V1, H2, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V2, H0, 0.0f), glm::vec3(V3, H0, 0.0f), glm::vec3(V3, H2, 0.0f), glm::vec3(V2, H2, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V3, H0, 0.0f), glm::vec3(V4, H0, 0.0f), glm::vec3(V4, H2, 0.0f), glm::vec3(V3, H2, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V4, H0, 0.0f), glm::vec3(V5, H0, 0.0f), glm::vec3(V5, H2, 0.0f), glm::vec3(V4, H2, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V5, H0, 0.0f), glm::vec3(V6, H0, 0.0f), glm::vec3(V6, H2, 0.0f), glm::vec3(V5, H2, 0.0f)));

    //H2 -> H3
    geometry.push_back(new Square(glm::vec3(V0, H2, 0.0f), glm::vec3(V1, H2, 0.0f), glm::vec3(V1, H3, 0.0f), glm::vec3(V0, H3, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V1, H2, 0.0f), glm::vec3(V2, H2, 0.0f), glm::vec3(V2, H3, 0.0f), glm::vec3(V1, H3, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V2, H2, 0.0f), glm::vec3(V3, H2, 0.0f), glm::vec3(V3, H3, 0.0f), glm::vec3(V2, H3, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V3, H2, 0.0f), glm::vec3(V4, H2, 0.0f), glm::vec3(V4, H3, 0.0f), glm::vec3(V3, H3, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V4, H2, 0.0f), glm::vec3(V5, H2, 0.0f), glm::vec3(V5, H3, 0.0f), glm::vec3(V4, H3, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V5, H2, 0.0f), glm::vec3(V6, H2, 0.0f), glm::vec3(V6, H3, 0.0f), glm::vec3(V5, H3, 0.0f)));

    //H3 -> H4
    geometry.push_back(new Square(glm::vec3(V0, H3, 0.0f), glm::vec3(V1, H3, 0.0f), glm::vec3(V1, H4, 0.0f), glm::vec3(V0, H4, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V1, H3, 0.0f), glm::vec3(V2, H3, 0.0f), glm::vec3(V2, H4, 0.0f), glm::vec3(V1, H4, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V2, H3, 0.0f), glm::vec3(V3, H3, 0.0f), glm::vec3(V3, H4, 0.0f), glm::vec3(V2, H4, 0.0f)));
    geometry.back()->setName(std::string("LED"));
    geometry.push_back(new Square(glm::vec3(V3, H3, 0.0f), glm::vec3(V4, H3, 0.0f), glm::vec3(V4, H4, 0.0f), glm::vec3(V3, H4, 0.0f)));
    geometry.back()->setName(std::string("LED"));
    geometry.push_back(new Square(glm::vec3(V4, H3, 0.0f), glm::vec3(V5, H3, 0.0f), glm::vec3(V5, H4, 0.0f), glm::vec3(V4, H4, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V5, H3, 0.0f), glm::vec3(V6, H3, 0.0f), glm::vec3(V6, H4, 0.0f), glm::vec3(V5, H4, 0.0f)));
    //H4 -> H5 -> Fenster

    //H5 -> H6
    geometry.push_back(new Square(glm::vec3(V0, H5, 0.0f), glm::vec3(V1, H5, 0.0f), glm::vec3(V1, H6, 0.0f), glm::vec3(V0, H6, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V1, H5, 0.0f), glm::vec3(V2, H5, 0.0f), glm::vec3(V2, H6, 0.0f), glm::vec3(V1, H6, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V2, H5, 0.0f), glm::vec3(V3, H5, 0.0f), glm::vec3(V3, H6, 0.0f), glm::vec3(V2, H6, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V3, H5, 0.0f), glm::vec3(V4, H5, 0.0f), glm::vec3(V4, H6, 0.0f), glm::vec3(V3, H6, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V4, H5, 0.0f), glm::vec3(V5, H5, 0.0f), glm::vec3(V5, H6, 0.0f), glm::vec3(V4, H6, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V5, H5, 0.0f), glm::vec3(V6, H5, 0.0f), glm::vec3(V6, H6, 0.0f), glm::vec3(V5, H6, 0.0f)));
    //H6 -> H7 -> Fenster

    //H7 -> H8
    geometry.push_back(new Square(glm::vec3(V0, H7, 0.0f), glm::vec3(V1, H7, 0.0f), glm::vec3(V1, H8, 0.0f), glm::vec3(V0, H8, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V1, H7, 0.0f), glm::vec3(V2, H7, 0.0f), glm::vec3(V2, H8, 0.0f), glm::vec3(V1, H8, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V2, H7, 0.0f), glm::vec3(V3, H7, 0.0f), glm::vec3(V3, H8, 0.0f), glm::vec3(V2, H8, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V3, H7, 0.0f), glm::vec3(V4, H7, 0.0f), glm::vec3(V4, H8, 0.0f), glm::vec3(V3, H8, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V4, H7, 0.0f), glm::vec3(V5, H7, 0.0f), glm::vec3(V5, H8, 0.0f), glm::vec3(V4, H8, 0.0f)));
    geometry.push_back(new Square(glm::vec3(V5, H7, 0.0f), glm::vec3(V6, H7, 0.0f), glm::vec3(V6, H8, 0.0f), glm::vec3(V5, H8, 0.0f)));


    //Left Side
    //H0 -> H2
    geometry.push_back(new Square(glm::vec3(V0, H0, VS1), glm::vec3(V0, H0, VS0), glm::vec3(V0, H2, VS0), glm::vec3(V0, H2, VS1)));
    geometry.push_back(new Square(glm::vec3(V0, H0, VS2), glm::vec3(V0, H0, VS1), glm::vec3(V0, H2, VS1), glm::vec3(V0, H2, VS2)));
    geometry.push_back(new Square(glm::vec3(V0, H0, VS3), glm::vec3(V0, H0, VS2), glm::vec3(V0, H2, VS2), glm::vec3(V0, H2, VS3)));
    geometry.push_back(new Square(glm::vec3(V0, H0, VS4), glm::vec3(V0, H0, VS3), glm::vec3(V0, H2, VS3), glm::vec3(V0, H2, VS4)));

    //H2 -> H3
    geometry.push_back(new Square(glm::vec3(V0, H2, VS1), glm::vec3(V0, H2, VS0), glm::vec3(V0, H3, VS0), glm::vec3(V0, H3, VS1)));
    geometry.push_back(new Square(glm::vec3(V0, H2, VS2), glm::vec3(V0, H2, VS1), glm::vec3(V0, H3, VS1), glm::vec3(V0, H3, VS2)));
    geometry.push_back(new Square(glm::vec3(V0, H2, VS3), glm::vec3(V0, H2, VS2), glm::vec3(V0, H3, VS2), glm::vec3(V0, H3, VS3)));
    geometry.push_back(new Square(glm::vec3(V0, H2, VS4), glm::vec3(V0, H2, VS3), glm::vec3(V0, H3, VS3), glm::vec3(V0, H3, VS4)));

    //H3 -> H4
    geometry.push_back(new Square(glm::vec3(V0, H3, VS1), glm::vec3(V0, H3, VS0), glm::vec3(V0, H4, VS0), glm::vec3(V0, H4, VS1)));
    geometry.push_back(new Square(glm::vec3(V0, H3, VS2), glm::vec3(V0, H3, VS1), glm::vec3(V0, H4, VS1), glm::vec3(V0, H4, VS2)));
    geometry.push_back(new Square(glm::vec3(V0, H3, VS3), glm::vec3(V0, H3, VS2), glm::vec3(V0, H4, VS2), glm::vec3(V0, H4, VS3)));
    geometry.push_back(new Square(glm::vec3(V0, H3, VS4), glm::vec3(V0, H3, VS3), glm::vec3(V0, H4, VS3), glm::vec3(V0, H4, VS4)));

    //H4 -> H5 -> Windows
    //H5 -> H6
    geometry.push_back(new Square(glm::vec3(V0, H5, VS1), glm::vec3(V0, H5, VS0), glm::vec3(V0, H6, VS0), glm::vec3(V0, H6, VS1)));
    geometry.push_back(new Square(glm::vec3(V0, H5, VS2), glm::vec3(V0, H5, VS1), glm::vec3(V0, H6, VS1), glm::vec3(V0, H6, VS2)));
    geometry.push_back(new Square(glm::vec3(V0, H5, VS3), glm::vec3(V0, H5, VS2), glm::vec3(V0, H6, VS2), glm::vec3(V0, H6, VS3)));
    geometry.push_back(new Square(glm::vec3(V0, H5, VS4), glm::vec3(V0, H5, VS3), glm::vec3(V0, H6, VS3), glm::vec3(V0, H6, VS4)));

    //H6 -> H7 -> Windows
    //H7 -> H8
    geometry.push_back(new Square(glm::vec3(V0, H7, VS1), glm::vec3(V0, H7, VS0), glm::vec3(V0, H8, VS0), glm::vec3(V0, H8, VS1)));
    geometry.push_back(new Square(glm::vec3(V0, H7, VS2), glm::vec3(V0, H7, VS1), glm::vec3(V0, H8, VS1), glm::vec3(V0, H8, VS2)));
    geometry.push_back(new Square(glm::vec3(V0, H7, VS3), glm::vec3(V0, H7, VS2), glm::vec3(V0, H8, VS2), glm::vec3(V0, H8, VS3)));
    geometry.push_back(new Square(glm::vec3(V0, H7, VS4), glm::vec3(V0, H7, VS3), glm::vec3(V0, H8, VS3), glm::vec3(V0, H8, VS4)));

    //Right Side
    //Square(glm::vec3 bottom_left, glm::vec3 bottom_right, glm::vec3 top_right, glm::vec3 top_left);
    //H0 -> H2
    geometry.push_back(new Square(glm::vec3(V6, H0, VS0), glm::vec3(V6, H0, VS1), glm::vec3(V6, H2, VS1), glm::vec3(V6, H2, VS0)));
    geometry.push_back(new Square(glm::vec3(V6, H0, VS1), glm::vec3(V6, H0, VS2), glm::vec3(V6, H2, VS2), glm::vec3(V6, H2, VS1)));
    geometry.push_back(new Square(glm::vec3(V6, H0, VS2), glm::vec3(V6, H0, VS3), glm::vec3(V6, H2, VS3), glm::vec3(V6, H2, VS2)));
    geometry.push_back(new Square(glm::vec3(V6, H0, VS3), glm::vec3(V6, H0, VS4), glm::vec3(V6, H2, VS4), glm::vec3(V6, H2, VS3)));

    //H2 -> H3
    geometry.push_back(new Square(glm::vec3(V6, H2, VS0), glm::vec3(V6, H2, VS1), glm::vec3(V6, H3, VS1), glm::vec3(V6, H3, VS0)));
    geometry.push_back(new Square(glm::vec3(V6, H2, VS1), glm::vec3(V6, H2, VS2), glm::vec3(V6, H3, VS2), glm::vec3(V6, H3, VS1)));
    geometry.push_back(new Square(glm::vec3(V6, H2, VS2), glm::vec3(V6, H2, VS3), glm::vec3(V6, H3, VS3), glm::vec3(V6, H3, VS2)));
    geometry.push_back(new Square(glm::vec3(V6, H2, VS3), glm::vec3(V6, H2, VS4), glm::vec3(V6, H3, VS4), glm::vec3(V6, H3, VS3)));

    //H3 -> H4
    geometry.push_back(new Square(glm::vec3(V6, H3, VS0), glm::vec3(V6, H3, VS1), glm::vec3(V6, H4, VS1), glm::vec3(V6, H4, VS0)));
    geometry.push_back(new Square(glm::vec3(V6, H3, VS1), glm::vec3(V6, H3, VS2), glm::vec3(V6, H4, VS2), glm::vec3(V6, H4, VS1)));
    geometry.push_back(new Square(glm::vec3(V6, H3, VS2), glm::vec3(V6, H3, VS3), glm::vec3(V6, H4, VS3), glm::vec3(V6, H4, VS2)));
    geometry.push_back(new Square(glm::vec3(V6, H3, VS3), glm::vec3(V6, H3, VS4), glm::vec3(V6, H4, VS4), glm::vec3(V6, H4, VS3)));

    //H4 -> H5 -> Windows
    //H5 -> H6
    geometry.push_back(new Square(glm::vec3(V6, H5, VS0), glm::vec3(V6, H5, VS1), glm::vec3(V6, H6, VS1), glm::vec3(V6, H6, VS0)));
    geometry.push_back(new Square(glm::vec3(V6, H5, VS1), glm::vec3(V6, H5, VS2), glm::vec3(V6, H6, VS2), glm::vec3(V6, H6, VS1)));
    geometry.push_back(new Square(glm::vec3(V6, H5, VS2), glm::vec3(V6, H5, VS3), glm::vec3(V6, H6, VS3), glm::vec3(V6, H6, VS2)));
    geometry.push_back(new Square(glm::vec3(V6, H5, VS3), glm::vec3(V6, H5, VS4), glm::vec3(V6, H6, VS4), glm::vec3(V6, H6, VS3)));

    //H6 -> H7 -> Windows
    //H7 -> H8
    geometry.push_back(new Square(glm::vec3(V6, H7, VS0), glm::vec3(V6, H7, VS1), glm::vec3(V6, H8, VS1), glm::vec3(V6, H8, VS0)));
    geometry.push_back(new Square(glm::vec3(V6, H7, VS1), glm::vec3(V6, H7, VS2), glm::vec3(V6, H8, VS2), glm::vec3(V6, H8, VS1)));
    geometry.push_back(new Square(glm::vec3(V6, H7, VS2), glm::vec3(V6, H7, VS3), glm::vec3(V6, H8, VS3), glm::vec3(V6, H8, VS2)));
    geometry.push_back(new Square(glm::vec3(V6, H7, VS3), glm::vec3(V6, H7, VS4), glm::vec3(V6, H8, VS4), glm::vec3(V6, H8, VS3)));

    for(std::vector<ShapeBase*>::iterator itr = geometry.begin(); itr != geometry.end(); ++itr)
    {
        if((*itr)->getName() == "LED")
            (*itr)->setColor(glm::vec4(1.0,0.0,0.0,1.0));
        else
            (*itr)->setColor(glm::vec4(1.0,1.0,1.0,1.0));

        /*(*itr)->setTranslation(glm::vec3(-((H8/2.0f)*m_scale),0.0,0.0));*/
        (*itr)->setTranslation(glm::vec3(-(WIDTH/2.0)*SCALE,0.0,0.0));
    }
    this->setScale(SCALE);

}

Building::~Building() {
    for(unsigned int i = 0; i < geometry.size(); ++i)
    {
        delete geometry.at(i);
        geometry.at(i) = 0;
    }
    geometry.clear();
}


void Building::draw()
{
    for(std::vector<ShapeBase*>::iterator itr = geometry.begin(); itr != geometry.end(); ++itr)
    {
        (*itr)->draw();
    }
}

void Building::setScale(float scale)
{
    for(std::vector<ShapeBase*>::iterator itr = geometry.begin(); itr != geometry.end(); ++itr)
    {
        Building::SCALE = m_scale = scale;
        (*itr)->setScale(scale);
    }
    Building::HEIGHT *= Building::SCALE;
    Building::WIDTH *= Building::SCALE;
    Building::FLOOR_1_HEIGHT *= Building::SCALE;
    Building::FLOOR_2_HEIGHT *= Building::SCALE;
    Building::WINDOW_HEIGHT *= Building::SCALE;
    Building::SIDE_DEPTH *= Building::SCALE;
    Building::SIDE_MIDDLE_Z *= Building::SCALE;

    Building::LED_HEIGHT *= Building::SCALE;
    Building::LED_WIDTH *= Building::SCALE;
}
