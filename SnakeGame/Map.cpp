#include "Map.h"
#include "Snake.h"
#include "Food.h"
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <thread>
#include <iomanip>

// Constructor
Map::Map(int inWidth, int inHeight, int inSpeed)
	:
	snake(nullptr),
	food(nullptr),
	width(inWidth),
	height(inHeight),
	playerScore(0),
	isGameOver(false),
	isPlayerWantsToPlay(true),
	deltaTime(inSpeed),
	wallDesignation('#'),
	curretInput(EInput::Right)
{
}

// Destructor
Map::~Map()
{
	delete snake;
	snake = nullptr;

	delete food;
	food = nullptr;
}

// Start playing map, loop game map drawing
void Map::play()
{
	char ans = '\0';

	// Loop until the player wants to quit
	while (isPlayerWantsToPlay)
	{
		// Setup game
		setup();

		// Loop until player wins or loses
		while (!isGameOver && !isGameWon)
		{
			// Start drawing and input threads
			std::thread dr(&Map::draw, this);
			std::thread inp(&Map::input, this);

			// Check for collision
			checkForCollision();

			// Wait for threads to finish
			inp.join();
			dr.join();
		}

		// Clear cosole
		system("cls");

		// Display game over or victory message
		if (isGameOver)
		{
			std::cout << "Game is over! Your score: " << playerScore << ".\n";// TODO function
		}
		else
		{
			std::cout << "You won! Congratulations! Your score: " << playerScore << ".\n";
		}

		// Ask player to play again
		std::cout << "Do you want to play again(y/n)?\n";
		delete snake;
		snake = nullptr;
		delete food;
		food = nullptr;

		ans = _getch();

		if (ans == 'n' || ans == 'N')
		{
			isPlayerWantsToPlay = false;
		}
	}

	// Go back to main menu
	backToMenu();
}

// Draw game map
void Map::draw()
{
	// Lock the mutex to ensure thread safety
	std::lock_guard<std::mutex> guard(mtx);

	if (!snake || !food) { return; }

	// Call base class draw function
	InteractiveInterface::draw();

	// Display the player's score
	std::cout << std::setw(width / 2) << std::left << "Score: " << playerScore << '\n';

	// Display controls
	std::cout << "\nWASD -> move, X -> back to main menu\n";

	// Get Snake variables to dispslay on map
	char headDesignation = snake->getDesignation();
	char tailDesignation = snake->getTailDesignation();
	int tailLength = snake->getTailLength();

	int headX, headY;
	snake->getCoordinates(headX, headY);
	int currentTailX, currentTailY;

	// Get Food variables to display on manp
	int foodX, foodY;
	food->getCoordinates(foodX, foodY);
	char foodDesignation = food->getDesignation();

	// Draw the upper wall
	for (int i = 0; i < width + 2; ++i)
	{
		std::cout << wallDesignation;
	}

	std::cout << '\n';

	// Draw the map
	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width + 2; ++i)
		{
			if (i == 0 || i == width + 1)
			{
				// Draw left and right walls
				std::cout << wallDesignation;
			}
			else if (j == headY && i == headX)
			{
				// Draw Snake head
				std::cout << headDesignation;
			}
			else if (j == foodY && i == foodX)
			{
				// Draw Food
				std::cout << foodDesignation;
			}
			else
			{
				// Draw tail or empty space
				bool shouldPrintTail = false;

				for (int k = 1; k < tailLength; ++k)
				{
					snake->getTailCoordinatesAtIndex(currentTailX, currentTailY, k);

					if (currentTailX == i && currentTailY == j)
					{
						std::cout << tailDesignation;
						shouldPrintTail = true;
					}
				}

				if (!shouldPrintTail)
				{
					std::cout << ' ';
				}
			}
		}

		std::cout << '\n';
	}

	// Draw lower wall
	for (int i = 0; i < width + 2; ++i)
	{
		std::cout << wallDesignation;
	}

	// Delay thread for 
	std::this_thread::sleep_for(std::chrono::milliseconds(deltaTime));
}

// Handles user input
void Map::input()
{
	// Lock the mutex to ensure thread safety
	std::lock_guard<std::mutex> guard(mtx);

	// Check if key is pressed
	if (_kbhit())
	{
		// Set Snake direction
		switch (_getch())
		{
		case 'a':
		case'A':
			if (curretInput != EInput::Right)
			{
				curretInput = EInput::Left;
			}
			break;
		case 'd':
		case'D':
			if (curretInput != EInput::Left)
			{
				curretInput = EInput::Right;
			}
			break;
		case 'w':
		case 'W':
			if (curretInput != EInput::Down)
			{
				curretInput = EInput::Up;
			}
			break;
		case 's':
		case 'S':
			if (curretInput != EInput::Up)
			{
				curretInput = EInput::Down;
			}
			break;
		case 'x':
		case 'X':
			curretInput = EInput::BACK_TO_MENU;
			break;
		}
	}

	if (!snake) { return; }

	// Move the snake based on the current input direction
	// Or get back to main menu
	switch (curretInput)
	{
	case EInput::Right:
		snake->moveSnake(1, 0);
		break;
	case EInput::Left:
		snake->moveSnake(-1, 0);
		break;
	case EInput::Up:
		snake->moveSnake(0, -1);
		break;
	case EInput::Down:
		snake->moveSnake(0, 1);
		break;
	case EInput::BACK_TO_MENU:
		mtx.unlock();
		backToMenu();
		break;
	default:
		break;
	}

	// Thread delay
	std::this_thread::sleep_for(std::chrono::milliseconds(deltaTime));
}

// Checks for collision between the snake and food/walls
// Checks if player has won the game
void Map::checkForCollision()
{
	// Lock the mutex to ensure thread safety
	std::lock_guard<std::mutex> guard(mtx);

	// Get head coordinates
	int headX, headY;
	snake->getCoordinates(headX, headY);

	// Get food coordinates
	int foodX, foodY;
	food->getCoordinates(foodX, foodY);

	// Check if the snake's head collided with the food
	if (headX == foodX && headY == foodY)
	{
		playerScore += 5;
		--freeSpace;

		// Check if game is won
		if (freeSpace <= 0)
		{
			isGameWon = true;
			return;
		}

		// set new Food coordinates
		food->setNewCoordinates(width, height);

		// Increase Snake
		snake->consume();

		return;
	}

	// Check if the snake's head collided with the walls
	if (headX <= 0 || headX >= width + 1 || headY < 0 || headY >= height)
	{
		isGameOver = true;
		return;
	}

	int currentTailX, currentTailY;

	// Check if the snake's head collided with its own tail
	for (int j = 1; j < snake->getTailLength(); ++j)
	{
		snake->getTailCoordinatesAtIndex(currentTailX, currentTailY, j);

		if (foodX == currentTailX && foodY == currentTailY)
		{
			food->setNewCoordinates(width, height);
		}

		if (headX == currentTailX && headY == currentTailY)
		{
			isGameOver = true;
			return;
		}
	}
}

// Set up the game state
void Map::setup()
{
	// Clear console
	system("cls");

	// Create a new snake and food object
	snake = new Snake(width, height);
	food = new Food(width, height);

	// Reset score
	playerScore = 0;

	// Reset flags
	isGameOver = false;
	isGameWon = false;

	// Calculate free space
	freeSpace = width * height - 2;

	// Set default snake direction
	curretInput = EInput::Right;
}
