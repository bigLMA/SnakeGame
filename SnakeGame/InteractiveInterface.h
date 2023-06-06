#pragma once

/*
* This class represents objects, that are responsible for
* representation of information on console
*/
class InteractiveInterface
{
public:
	// Play loop
	virtual void play() = 0;

protected:
	// This function would be overided in derived classes
	// However, they all use code to hide cursor and set it's position
	// From this function in override
	virtual void draw();

	// Input handle
	virtual void input() = 0;
};