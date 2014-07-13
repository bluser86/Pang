#include "Include.h"
#include "Game.h"
#include "SplashScreen.h"
#include "Menu.h"
#include "PlayerPaddle.h"
#include "GameBall.h"

void Game::Start(void)
{
	if (_gameState != Uninitialized)
	{
		return;
	}

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Pang!");

	PlayerPaddle *player1 = new PlayerPaddle();
	player1->SetPosition((SCREEN_WIDTH/2),700);

	GameBall *ball = new GameBall();
	ball->SetPosition((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));

	_objectManager.Add("Paddle1", player1);
	_objectManager.Add("Ball", ball);

	_gameState = Game::ShowingSplash;

	sf::Clock clock;
	while (!IsExiting())
	{
		GameLoop(clock.restart());
	}

	_mainWindow.close();
}

bool Game::IsExiting()
{
	return _gameState == Game::Exiting;
}

void Game::GameLoop(sf::Time elapsed)
{
	sf::Event currentEvent;
	while (_mainWindow.pollEvent(currentEvent)) {
		if (currentEvent.type == sf::Event::Closed)
		{
			_gameState = Game::Exiting;
		}

		if (currentEvent.type == sf::Event::KeyPressed)
		{
			if (currentEvent.key.code == sf::Keyboard::Escape)
			{
				ShowMenu();
			}

			if (currentEvent.key.code == sf::Keyboard::D)
			{
				_showDebug = !_showDebug;
			}
		}
	}

	switch (_gameState)
	{
	case Game::Playing:
		_mainWindow.clear(sf::Color(0, 0, 0));
		_objectManager.UpdateAll(elapsed);
		_objectManager.DrawAll(_mainWindow);
		_mainWindow.display();
		break;
	case Game::ShowingSplash:
		ShowSplashScreen();
		break;
	case Game::ShowingMenu:
		ShowMenu();
		break;
	}
}

sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	_gameState = ShowingSplash;
	splashScreen.Show(_mainWindow);
}

void Game::ShowMenu()
{
	Menu menu;
	_gameState = ShowingMenu;
	Menu::MenuResult result = menu.Show(_mainWindow);
	switch (result)
	{
	case Menu::Exit:
		_gameState = Exiting;
		break;
	case Menu::Play:
		_gameState = Playing;
		break;
	}
}

GameObjectManager& Game::GetObjectManager()
{
	return _objectManager;
}

bool Game::IsDebug()
{
	return _showDebug;
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_objectManager;
bool Game::_showDebug = false;