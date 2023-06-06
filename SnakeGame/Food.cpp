#include "Food.h"
#include <cstdlib>
#include <ctime>

// Food constructor
// Width and height are to get initial coordinates
Food::Food(int width, int height)
{
	designation = 'F';
	setNewCoordinates(width, height);
}

// Generates a new random coordinates for the food object within the specified width and height.
void Food::setNewCoordinates(int width, int height)
{
	// Seed the random number generator
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// Generate random coordinates for the new location whithin Map
	int newX = std::rand() % width;
	int newY = std::rand() % height;

	// Ensure that the new coordinates does not fall on the boundaries
	if (newX == 0)
	{
		++newX;
	}
	else if (newY == height)
	{
		--newY;
	}

	// Update coordinates
	x = newX;
	y = newY;
}
