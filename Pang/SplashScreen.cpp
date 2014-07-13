#include "Include.h"
#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow& renderWindow)
{
	sf::Texture texture;
	if (texture.loadFromFile("images/splash.png") != true)
	{
		return;
	}

	sf::Sprite sprite(texture);

	renderWindow.draw(sprite);
	renderWindow.display();
}