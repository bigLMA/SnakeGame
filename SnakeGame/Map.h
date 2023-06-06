#pragma once

#include "InteractiveInterface.h"
#include <mutex>
#include <functional>


enum class EInput
{
	Right, Left, Up, Down, BACK_TO_MENU
};

/*
* This class is responsible for displaying map, arena where Snake is moving
* This class also has input functionality to control Snake movement
*/
class Map : public InteractiveInterface
{
public:
	// Constructor
	Map(int inWidth, int inHeight, int inSpeed);

	// Destructor
	~Map();

	// Start playing map, loop game map drawing
	virtual void play()override;

	// Back to menu delegate
	std::function<void()> backToMenu;

protected:
	// Draw game map
	virtual void draw() override;

	// Handles user input
	virtual void input()override;

private:
	// Snake
	class Snake* snake;

	// Food
	class Food* food;

	/** Map size */
	int width;
	int height;

	// Player score
	int playerScore;

	/** Hame status flags */
	bool isGameOver;
	bool isGameWon;
	bool isPlayerWantsToPlay;

	// Delta time
	int deltaTime;

	// Symbol to designate a wall
	char wallDesignation;

	// Enum for user input
	EInput curretInput;

	// Checks for collision between the snake and food/walls
	// Checks if player has won the game
	void checkForCollision();

	// Set up the game state
	void setup();

	// Mutex to protect threads
	std::mutex mtx;

	// Free space remaining
	int freeSpace;
};