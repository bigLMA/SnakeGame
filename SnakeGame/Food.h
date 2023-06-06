#pragma once

#include "Object.h"

/*
* This class represents food
* Once it is consumed by Snake, food will be placed to new coordinates
*/
class Food : public Object
{
public:
	// Food constructor
	// Width and height are to get initial coordinates
	Food(int width, int height);

	// Generates a new random coordinates for the food object within the specified width and height.
	void setNewCoordinates(int width, int height);
};