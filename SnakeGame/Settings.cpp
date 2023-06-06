#include "Settings.h"
#include "GameMode.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <iomanip>

// Constuctor
Settings::Settings(GameMode* inGameMode)
	:currentSettingsSelection(ECurrentSettingsSelection::MapSize),
	gameMode(inGameMode),
	outerButtonWidth(55),
	innerButtonWidth(45),
	isDrawnigSettings(true)
{
}

// Destructor
Settings::~Settings()
{
	if (gameMode)
	{
		gameMode = nullptr;
	}
}

// Start playing settings, loop settings menu drawing
void Settings::play()
{
	// Clear console
	system("cls");

	currentSettingsSelection = ECurrentSettingsSelection::MapSize;

	isDrawnigSettings = true;

	// Loop settings until player makes decision
	while (isDrawnigSettings)
	{
		draw();
		input();

		// Delay
		Sleep(10);
	}
}

// Draws the settings menu
void Settings::draw()
{
	// Call base class draw function
	InteractiveInterface::draw();

	// Draw buttons
	drawButton(ECurrentSettingsSelection::MapSize);
	drawButton(ECurrentSettingsSelection::GameSpeed);
	drawButton(ECurrentSettingsSelection::BACK_TO_MENU);
}

// Handles user input in the settings menu
void Settings::input()
{
	if (!gameMode)
	{
		return;
	}

	// Check if key is pressed
	if (_kbhit())
	{
		// Get input
		char input = _getch();
		const char enter = static_cast<char>(13); // ASCII value for the Enter key
		switch (input)
		{
		case'w':
		case 'W':
			// Buttons selection upwards
			if (currentSettingsSelection != ECurrentSettingsSelection::MapSize)
			{
				currentSettingsSelection = static_cast<ECurrentSettingsSelection>(static_cast<int>(currentSettingsSelection) - 1);
			}
			else
			{
				currentSettingsSelection = ECurrentSettingsSelection::BACK_TO_MENU;
			}
			break;
		case 's':
		case 'S':
			// Buttons selection downwards
			if (currentSettingsSelection != ECurrentSettingsSelection::BACK_TO_MENU)
			{
				currentSettingsSelection = static_cast<ECurrentSettingsSelection>(static_cast<int>(currentSettingsSelection) + 1);
			}
			else
			{
				currentSettingsSelection = ECurrentSettingsSelection::MapSize;
			}
			break;

			// if Enter button is pressed, launch necessary commands based on player selection
		case enter:
			switch (currentSettingsSelection)
			{
			case ECurrentSettingsSelection::MapSize:
				gameMode->toggleMapSize();
				break;
			case ECurrentSettingsSelection::GameSpeed:
				gameMode->toggleGameSpeed();
				break;
			case ECurrentSettingsSelection::BACK_TO_MENU:
				isDrawnigSettings = false;
				backToMenu();
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

// Draws button
void Settings::drawButton(ECurrentSettingsSelection button)
{
	if (!gameMode) { return; }

	// Check if the button is currently selected
	bool isSelected = (button == currentSettingsSelection) ? true : false;

	// Determine button text and button contents
	std::string buttonText;
	std::string buttonContents;
	buttonContents = " ";

	switch (button)
	{
	case ECurrentSettingsSelection::MapSize:
		buttonText = "Map Size";

		switch (gameMode->getMapSizeStatus())
		{
		case EMapSize::Small:
			buttonContents = "Small";
			break;
		case EMapSize::Medium:
			buttonContents = "Medium";
			break;
		case EMapSize::Big:
			buttonContents = "Big";
			break;
		default:
			break;
		}

		break;
	case ECurrentSettingsSelection::GameSpeed:
		buttonText = "Game Speed";

		switch (gameMode->getGameSpeedStatus())
		{
		case EGameSpeed::Slow:
			buttonContents = "Slow";
			break;
		case EGameSpeed::Medium:
			buttonContents = "Medium";
			break;
		case EGameSpeed::Fast:
			buttonContents = "Fast";
			break;
		default:
			break;
		}

		break;
	case ECurrentSettingsSelection::BACK_TO_MENU:
		buttonText = "Back to menu";
		buttonContents = "  ";
		break;
	default:
		break;
	}

	// Draw button
	std::cout << std::setw(outerButtonWidth) << std::left
		<< "+--------------------------------------------------------+\n";
	std::cout << std::setw(outerButtonWidth) << "| " << "  |\n";

	if (isSelected&& button != ECurrentSettingsSelection::BACK_TO_MENU)
	{
		std::cout << "| " << std::setw(innerButtonWidth)
			<< "+--------------------------------------------------+" << "   |\n";
		std::cout << "| " << "|" << std::right << buttonText << ": " <<
			buttonContents << std::setw(innerButtonWidth - (
				buttonContents.length() + buttonText.length()) + 5) << "|\n";
		std::cout << "| " << std::setw(innerButtonWidth)
			<< "+--------------------------------------------------+" << "   |\n";

	}
	else if (isSelected && button == ECurrentSettingsSelection::BACK_TO_MENU)
	{
		std::cout << "| " << std::setw(innerButtonWidth)
			<< "+--------------------------------------------------+" << "   |\n";
		std::cout << "| " << "|" << std::setw(innerButtonWidth - 1)
			<< buttonText << buttonContents << "    |\n";
		std::cout << "| " << std::setw(innerButtonWidth)
			<< "+--------------------------------------------------+" << "   |\n";
	}
	else
	{
		std::cout << "| " << std::setw(outerButtonWidth) << buttonText << "|\n";
	}

	std::cout << std::left << std::setw(outerButtonWidth) << "| " << "  |\n";
	std::cout << std::setw(outerButtonWidth)
		<< "+--------------------------------------------------------+\n";
}
