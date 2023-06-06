#pragma once

/*
*  This class represents objects, pictured by Map (Snake, Food)
*/
class Object
{
public:
	// Function to get object coordinates
	// Takes references which will be updated with actual coordinates
	void getCoordinates(int& xLoc, int& yLoc);

	// Function to get the designation of the object.
	char getDesignation()const;

protected:
	/** Object coordinates */
	int x;
	int y;

	// Object designation
	char designation;
};