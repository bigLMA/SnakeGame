#pragma once

enum class EMapSize
{
	Small, Medium, Big
};

enum class EGameSpeed
{
	Slow, Medium, Fast
};

/*
* This class contains information about different game conditions
* That can be changed
*/
class GameMode
{
public:
	// Constructor
	GameMode();

	// Toggles game map size between small, medium, and big
	void toggleMapSize();

	// Gets the width and height of the current map size
	// Takes references which will be updated with actual size
	void getMapSize(int& inX, int& inY);

	// Returns the game map size status
	EMapSize getMapSizeStatus() const;

	// Toggles game speed between slow, medium, and fast
	void toggleGameSpeed();

	// Returns game speed value
	int getGameSpeed() const;

	// Returns game speed status
	EGameSpeed getGameSpeedStatus() const;

private:
	// Enum to track current map size
	EMapSize currentMapSize;

	// Enum to track current game speed
	EGameSpeed currentGameSpeed;

	/** Small map size values */
	int smallMapSizeWidth;
	int smallMapSizeHeight;

	/** Medium map size values */
	int mediumMapSizeWidth;
	int mediumMapSizeHeight;

	/** Big map size values */
	int bigMapSizeWidth;
	int bigMapSizeHeight;

	/** Different game speed values */
	int slowGameSpeed;
	int mediumGameSpeed;
	int fastGameSpeed;
};