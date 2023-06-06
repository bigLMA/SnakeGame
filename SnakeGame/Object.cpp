#include "Object.h"

// Function to get object coordinates
// Takes references which will be updated with actual coordinates
void Object::getCoordinates(int& xLoc, int& yLoc)
{
	xLoc = x;
	yLoc = y;
}

// Function to get the designation of the object.
char Object::getDesignation() const
{
	return designation;
}
