#include "GameMode.h"

// Constructor
GameMode::GameMode()
	: currentMapSize(EMapSize::Medium),
	currentGameSpeed(EGameSpeed::Medium),
	smallMapSizeWidth(25),
	smallMapSizeHeight(15),
	mediumMapSizeWidth(30),
	mediumMapSizeHeight(20),
	bigMapSizeWidth(35),
	bigMapSizeHeight(25),
	slowGameSpeed(25),
	mediumGameSpeed(10),
	fastGameSpeed(5)
{}

// Toggles game map size between small, medium, and big
void GameMode::toggleMapSize()
{
	switch (currentMapSize)
	{
	case EMapSize::Small:
		currentMapSize = EMapSize::Medium;
		break;
	case EMapSize::Medium:
		currentMapSize = EMapSize::Big;
		break;
	case EMapSize::Big:
		currentMapSize = EMapSize::Small;
		break;
	default:
		break;
	}
}

// Gets the width and height of the current map size
// Takes references which will be updated with actual size
void GameMode::getMapSize(int& inX, int& inY)
{
	switch (currentMapSize)
	{
	case EMapSize::Small:
		inX = smallMapSizeWidth;
		inY = smallMapSizeHeight;
		break;
	case EMapSize::Medium:
		inX = mediumMapSizeWidth;
		inY = mediumMapSizeHeight;
		break;
	case EMapSize::Big:
		inX = bigMapSizeWidth;
		inY = bigMapSizeHeight;
		break;
	default:
		break;
	}
}

// Returns the game map size status
EMapSize GameMode::getMapSizeStatus() const
{
	return currentMapSize;
}

// Toggles game speed between slow, medium, and fast
void GameMode::toggleGameSpeed()
{
	switch (currentGameSpeed)
	{
	case EGameSpeed::Slow:
		currentGameSpeed = EGameSpeed::Medium;
		break;
	case EGameSpeed::Medium:
		currentGameSpeed = EGameSpeed::Fast;
		break;
	case EGameSpeed::Fast:
		currentGameSpeed = EGameSpeed::Slow;
		break;
	default:
		break;
	}
}

// Returns game speed value
int GameMode::getGameSpeed() const
{
	switch (currentGameSpeed)
	{
	case EGameSpeed::Slow:
		return slowGameSpeed;
		break;
	case EGameSpeed::Medium:
		return mediumGameSpeed;
		break;
	case EGameSpeed::Fast:
		return fastGameSpeed;
		break;
	default:
		return -1;
		break;
	}
}

// Returns game speed status
EGameSpeed GameMode::getGameSpeedStatus() const
{
	return currentGameSpeed;
}