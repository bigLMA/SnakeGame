#pragma once

#include "InteractiveInterface.h"
#include <functional>

enum class ECurrentSettingsSelection
{
	MapSize = 0, GameSpeed /*walls lethal*/, BACK_TO_MENU
};

/*
* This class handles game mode parameters switching
*/
class Settings :public InteractiveInterface
{

public:
	// Constructor
	Settings(class GameMode* inGameMode);

	// Destructor
	~Settings();

	// Start playing settings, loop settings menu drawing
	virtual void play() override;

	// Back to menu delegate
	std::function<void()> backToMenu;

protected:
	// Draws the settings menu
	virtual void draw() override;

	// Handles user input in the settings menu
	virtual void input()override;

private:
	// Enum for display selected button
	ECurrentSettingsSelection currentSettingsSelection;

	// Draws button
	void drawButton(ECurrentSettingsSelection button);

	// Game mode pointer
	class GameMode* gameMode;

	/** Button drawing information */
	int outerButtonWidth;
	int innerButtonWidth;

	// Flag for tracking if game should draw settings
	bool isDrawnigSettings;
};