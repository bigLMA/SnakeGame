#pragma once

#include "Object.h"
#include <vector>

/*
* Snake is main character of the game
* This class contains all the information to picture snake, including
* Both snake head and tail
*/
class Snake : public Object
{

public:
	// Constructor
	// Width and height are for determining initial coordinates
	Snake(int width, int height);

	// Moves the snake by updating its x and y coordinates
	void moveSnake(int xChange = 0, int yChange = 0);

	// Increases tail length
	// Adjusts size of tail vectors if needed
	void consume();

	// Gets the x and y coordinates of the snake's tail at the specified index
	void getTailCoordinatesAtIndex(int& tailXLoc, int& tailYLoc, int index);

	int getTailLength() const;

	// Returns tail designation
	char getTailDesignation() const;

private:
	// How much elements of tail to show in Map
	int tailLength;

	/** Tail coordinates */
	std::vector<int> tailX;
	std::vector<int> tailY;

	// Char to picture tail
	char tailDesignation;

	// Moves the tail of the snake by shifting the previous tail positions
	void moveTail();
};