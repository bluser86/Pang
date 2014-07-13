#include "Include.h"
#include "Menu.h"

Menu::MenuResult Menu::Show(sf::RenderWindow& window) 
{
	sf::Texture texture;
	texture.loadFromFile("images/menu.png");
	sf::Sprite sprite(texture);

	MenuItem playButton;
	playButton.rect.top = 145;
	playButton.rect.height = 380 - 145;
	playButton.rect.left = 0;
	playButton.rect.width = 1023 - 0;
	playButton.action = Play;
	
	MenuItem exitButton;
	exitButton.rect.top = 383;
	exitButton.rect.height = 560 - 380;
	exitButton.rect.left = 0;
	exitButton.rect.width = 1023 - 0;
	exitButton.action = Exit;

	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);

	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}

Menu::MenuResult Menu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;
	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if (menuItemRect.top < y
			&& menuItemRect.top + menuItemRect.height > y
			&& menuItemRect.left < x
			&& menuItemRect.left + menuItemRect.width > x)
		{
			return (*it).action;
		}
	}

	return Nothing;
}

Menu::MenuResult Menu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;
	
	while (window.pollEvent(menuEvent))
	{
		if (menuEvent.type == sf::Event::MouseButtonPressed) {
			return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
		}

		if (menuEvent.type == sf::Event::Closed) {
			return Exit;
		}
	}
}