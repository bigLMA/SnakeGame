#include "Snake.h"

// Constructor
// Width and height are for determining initial coordinates
Snake::Snake(int width, int height)
	:tailLength(1)
{
	x = width / 2;
	y = height / 2;
	designation = 'O';
	tailDesignation = 'o';
	tailX.resize(3);
	tailY.resize(3);
}

// Moves the snake by updating its x and y coordinates
void Snake::moveSnake(int xChange, int yChange)
{
	// Update coordinates
	x += xChange;
	y += yChange;

	// Move tail after head
	moveTail();
}

// Increases tail length
// Adjusts size of tail vectors if needed
void Snake::consume()
{
	++tailLength;

	if (tailX.size() - tailLength <= 5)
	{
		int newLength = tailX.size() + tailLength;
		tailX.resize(newLength);
		tailY.resize(newLength);
	}
}

// Gets the x and y coordinates of the snake's tail at the specified index
void Snake::getTailCoordinatesAtIndex(int& tailXLoc, int& tailYLoc, int index)
{
	tailXLoc = tailX[index];
	tailYLoc = tailY[index];
}

// Moves the tail of the snake by shifting the previous tail positions
void Snake::moveTail()
{
	int prevHeadX = tailX[0];
	int prevHeadY = tailY[0];
	int prevTailX;
	int prevTailY;

	// First elements of array is head location
	tailX[0] = x;
	tailY[0] = y;

	// Shift position
	for (int i = 1; i < tailLength; ++i)
	{
		prevTailX = tailX[i];
		prevTailY = tailY[i];
		tailX[i] = prevHeadX;
		tailY[i] = prevHeadY;
		prevHeadX = prevTailX;
		prevHeadY = prevTailY;
	}
}

// Returns tail length
int Snake::getTailLength() const
{
	return tailLength;
}

// Returns tail designation
char Snake::getTailDesignation() const
{
	return tailDesignation;
}
