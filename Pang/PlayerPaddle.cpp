#include "Include.h"
#include "PlayerPaddle.h"
#include "Game.h"

PlayerPaddle::PlayerPaddle() :
	_velocity(0),
	_maxVelocity(600.0f)
{
	Load("images/paddle.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getGlobalBounds().width/2, GetSprite().getGlobalBounds().height/2);
}

PlayerPaddle::~PlayerPaddle()
{

}

void PlayerPaddle::Draw(sf::RenderWindow& window)
{
	VisibleGameObject::Draw(window);
}

float PlayerPaddle::GetVelocity() const
{
	return _velocity;
}

void PlayerPaddle::Update(sf::Time elapsed)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_velocity -= 10.0f;
		printf("Left Pressed\n");
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_velocity += 10.0f;
		printf("Right Pressed\n");
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_velocity = 0.0f;
	}

	if (_velocity > _maxVelocity)
	{
		_velocity = _maxVelocity;
	}

	if (_velocity < -_maxVelocity)
	{
		_velocity = -_maxVelocity;
	}

	sf::Vector2f pos = this->GetPosition();

	// Collision with the side of the screen
	if (pos.x < GetSprite().getGlobalBounds().width / 2
		|| pos.x > (Game::SCREEN_WIDTH - GetSprite().getGlobalBounds().width / 2))
	{
		if(pos.x > (Game::SCREEN_WIDTH - GetSprite().getGlobalBounds().width / 2))
		{			
			this->SetPosition((Game::SCREEN_WIDTH - GetSprite().getGlobalBounds().width / 2) - 1, pos.y);
		}
		if(pos.x < GetSprite().getGlobalBounds().width / 2)
		{			
			this->SetPosition(GetSprite().getGlobalBounds().width / 2 + 1, pos.y);
		}

		_velocity = -_velocity;
	}

	GetSprite().move(_velocity * elapsed.asSeconds(), 0);
}