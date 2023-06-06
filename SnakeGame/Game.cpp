#include "Game.h"
#include "GameMode.h"
#include "Map.h"
#include "Settings.h"
#include <functional>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <iomanip>
#include <string>

// Constructor
Game::Game()
	:map(nullptr),
	settings(nullptr),
	isDrawingMenu(true),
	currentMenuSelection(EMenuSelection::Game),
	outerButtonWidth(25),
	innerButtonWidth(20)
{
	// Create game mode
	gameMode = new GameMode();
}

// Game start, loop menu screen drawing
void Game::play()
{
	// Clear console
	system("cls");

	isDrawingMenu = true;
	currentMenuSelection = EMenuSelection::Game;

	// Delete existing Map object if exists
	if (map)
	{
		delete map;
		map = nullptr;
	}

	// Delete existing Settings objects if exists
	if (settings)
	{
		delete settings;
		settings = nullptr;
	}

	// Loop menu drawing until player makes decision
	while (isDrawingMenu)
	{
		draw();
		input();

		// Delay
		Sleep(10);
	}
}


// Draws menu
void Game::draw()
{
	// Call base class draw function
	InteractiveInterface::draw();

	// Draw buttons
	drawButton(EMenuSelection::Game);
	drawButton(EMenuSelection::Settings);
	drawButton(EMenuSelection::Quit);

	// Display instructions
	std::cout << "\n W/S -> change buttons selection\n";
}

// Handles user input
void Game::input()
{
	// Check if key is pressed
	if (_kbhit())
	{
		// Get input
		char input = _getch();
		const char enter = static_cast<char>(13);	// ASCII value for the Enter key

		switch (input)
		{
		case'w':
		case 'W':
			// Buttons selection upwards
			if (currentMenuSelection != EMenuSelection::Game)
			{
				EMenuSelection newSelection = static_cast<EMenuSelection>(static_cast<int>(currentMenuSelection) - 1);
				currentMenuSelection = newSelection;
			}
			else
			{
				currentMenuSelection = EMenuSelection::Quit;
			}
			break;
		case 's':
		case 'S':
			// Buttons selection downwards
			if (currentMenuSelection != EMenuSelection::Quit)
			{
				EMenuSelection newSelection = static_cast<EMenuSelection>(static_cast<int>(currentMenuSelection) + 1);
				currentMenuSelection = newSelection;
			}
			else
			{
				currentMenuSelection = EMenuSelection::Game;
			}
			break;

			// if Enter button is pressed, launch necessary commands based on player selection
		case enter:

			switch (currentMenuSelection)
			{
			case EMenuSelection::Game:
				launchMap();
				break;
			case EMenuSelection::Settings:
				launchSettings();
				break;
			case EMenuSelection::Quit:
				exitGame();
				break;
			default:
				break;
			}

			return;

		default:
			break;
		}
	}
}

// Launches the map
void Game::launchMap()
{
	// Stop drawing menu
	isDrawingMenu = false;

	// Get map size and speed from gamemode
	int width, height;
	gameMode->getMapSize(width, height);
	int speed = gameMode->getGameSpeed();

	// Create new Map object
	map = new Map(width, height, speed);

	// Bind beck to menu delegate
	map->backToMenu = std::bind(&Game::play, this);

	// Launch game play loop
	map->play();
}

// Launches settings
void Game::launchSettings()
{
	if (!gameMode) { return; }

	// Stop drawing menu
	isDrawingMenu = false;

	// Create new Settings object
	settings = new Settings(gameMode);

	// Bind beck to menu delegate
	settings->backToMenu = std::bind(&Game::play, this);

	// Launch settings play loop
	settings->play();
}

// Draws a button
void Game::drawButton(EMenuSelection button)
{
	// Check if button is currently selected
	bool isSelected = (button == currentMenuSelection) ? true : false;

	// Determine button text
	std::string buttonText;

	switch (button)
	{
	case EMenuSelection::Game:
		buttonText = "Play Game";
		break;
	case EMenuSelection::Settings:
		buttonText = "Settings";
		break;
	case EMenuSelection::Quit:
		buttonText = "Quit";
		break;
	default:
		break;
	}

	// Draw Button
	std::cout << std::setw(outerButtonWidth) << std::left << "+--------------------------+\n";
	std::cout << std::setw(outerButtonWidth) << "| " << "  |\n";

	if (isSelected)
	{
		std::cout << "| " << std::setw(innerButtonWidth) << "+--------------------+" << "   |\n";
		std::cout << "| " << "|" << std::setw(innerButtonWidth) << buttonText << "|   |\n";
		std::cout << "| " << std::setw(innerButtonWidth) << "+--------------------+" << "   |\n";

	}
	else
	{
		std::cout << "| " << std::setw(outerButtonWidth) << buttonText << "|\n";
	}

	std::cout << std::setw(outerButtonWidth) << "| " << "  |\n";
	std::cout << std::setw(outerButtonWidth) << "+--------------------------+\n";
}

// Exits the game
void Game::exitGame()
{
	// Delete gamemode
	if (gameMode)
	{
		delete gameMode;
		gameMode = nullptr;
	}

	// Delete map
	if (map)
	{
		delete map;
		map = nullptr;
	}

	// Delete settings
	if (settings)
	{
		delete settings;
		settings = nullptr;
	}

	// Exit game
	exit(0);
}
