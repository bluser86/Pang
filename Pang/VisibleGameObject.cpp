#include "Include.h"
#include "VisibleGameObject.h"
#include "Game.h"

VisibleGameObject::VisibleGameObject()
	:_isLoaded(false)
{
}

VisibleGameObject::~VisibleGameObject() {}

void VisibleGameObject::Load(std::string filename)
{
	if (_texture.loadFromFile(filename) == false)
	{
		_filename = "";
		_isLoaded = false;
	}
	else 
	{
		_filename = filename;
		_sprite.setTexture(_texture);
		_isLoaded = true;
	}
}

void VisibleGameObject::Draw(sf::RenderWindow& window)
{
	if (_isLoaded)
	{
		window.draw(_sprite);
	}

	if (Game::IsDebug())
	{
		// Draw boundingboxes in debug mode
		sf::RectangleShape rectangle(sf::Vector2f(GetBoundingBox().width, GetBoundingBox().height));
		rectangle.setOrigin(_sprite.getOrigin());
		rectangle.setOutlineThickness(1);
		rectangle.setOutlineColor(sf::Color(255, 0, 0));
		rectangle.setFillColor(sf::Color::Transparent);
		rectangle.setPosition(GetPosition());
		window.draw(rectangle);
	}
}

void VisibleGameObject::Update(sf::Time elapsed) {}

float VisibleGameObject::GetWidth() const
{
	return _sprite.getGlobalBounds().width;
}

float VisibleGameObject::GetHeight() const
{
	return _sprite.getGlobalBounds().height;
}

sf::Rect<float> VisibleGameObject::GetBoundingBox() const
{
	sf::FloatRect size = _sprite.getGlobalBounds();

	return sf::Rect<float>(size.left, size.top, size.width, size.height);
}

void VisibleGameObject::SetPosition(float x, float y)
{
	if (_isLoaded)
	{
		_sprite.setPosition(x,y);
	}
}

sf::Vector2f VisibleGameObject::GetPosition() const
{
	if (_isLoaded)
	{
		return _sprite.getPosition();
	}
	return sf::Vector2f();
}

sf::Sprite& VisibleGameObject::GetSprite()
{
	return _sprite;
}

bool VisibleGameObject::IsLoaded() const
{
	return _isLoaded;
}