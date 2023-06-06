#pragma once

#include "InteractiveInterface.h"

enum class EMenuSelection
{
	Game = 0,
	Settings,
	Quit
};

/*
* This class displays main game menu
* And handles different interfaces switching
*/
class Game : public InteractiveInterface
{

public:
	// Constructor
	Game();

	// Game start, loop menu screen drawing
	virtual void play() override;

protected:
	// Draws menu
	virtual void draw() override;

	// Handles user input
	virtual void input()override;

private:
	// Enum to display selected button
	EMenuSelection currentMenuSelection;

	// If player desides to start playing,
	// Game will create map
	class Map* map;

	// If player desides to go to settings,
	// Game will create settings
	class Settings* settings;

	// Game mode, where game information is stored
	class GameMode* gameMode;

	// Launches the map
	void launchMap();

	// Launches settings
	void launchSettings();

	// Flag for tracking if game should draw menu
	bool isDrawingMenu;

	// Draws a button
	void drawButton(EMenuSelection button);

	/** Button drawing information */
	int outerButtonWidth;
	int innerButtonWidth;

	// Exits the game
	void exitGame();
};