/*
 * building.h
 *
 *  Created on: Jan 8, 2013
 *      Author: arend
 */

#ifndef BUILDING_H_
#define BUILDING_H_

#include <vector>
#include "line.hpp"
#include "square.hpp"

class Building {
    public:
        Building();
        virtual ~Building();

        void draw();

        void setScale(float scale);

        static float SCALE;

        //All Dimensions in Meter
        static float HEIGHT;
        static float WIDTH;
        static float FLOOR_1_HEIGHT;  // bottom of windows 1 floor (y axis)
        static float FLOOR_2_HEIGHT;  // bottom of windows 2 floor (y axis)
        static float WINDOW_HEIGHT;   // FLOOR_1_HEIGHT + WINDOW_HEIGHT = WINDOW top pos (Y Axis)

        //static float LEFT_FRONT_MIDDLE_X;
        //static float LEFT_FRONT_MIDDLE_Y;
        //static float RIGHT_FRONT_MIDDLE_X;
        //static float RIGHT_FRONT_MIDDLE_Y;


        static float LEFT_SIDE_MIDDLE_Y;
        static float SIDE_DEPTH;
        static float SIDE_MIDDLE_Z;
        static float LEFT_SIDE_DISTANCE_X;  // -(WIDTH / 2)
        static float RIGHT_SIDE_DISTANCE_X;  // +(WIDTH / 2)

        static float FRONT_Z; //distance front

        static float LED_HEIGHT;
        static float LED_WIDTH;

    private:
        std::vector<ShapeBase*>  geometry;
        float m_scale;
};

#endif /* BUILDING_H_ */
