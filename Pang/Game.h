#pragma once
#include "GameObjectManager.h"

class Game
{
public:
	static void Start();
	static sf::RenderWindow& GetWindow();
	static GameObjectManager& GetObjectManager();
	static bool IsDebug();

	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;

private:
	static bool IsExiting();
	static void GameLoop(sf::Time elapsed);

	static void ShowSplashScreen();
	static void ShowMenu();

	enum GameState { Uninitialized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting };

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	static GameObjectManager _objectManager;

	static bool _showDebug;
};