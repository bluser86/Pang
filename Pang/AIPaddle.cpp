#include "Include.h"
#include "AIPaddle.h"
#include "Game.h"
#include "GameBall.h"

AIPaddle::AIPaddle() :
	_velocity(0),
	_maxVelocity(600.0f)
{
	Load("images/paddle.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getGlobalBounds().width/2, GetSprite().getGlobalBounds().height/2);
}

AIPaddle::~AIPaddle()
{
}

void AIPaddle::Draw(sf::RenderWindow& window)
{	
	VisibleGameObject::Draw(window);
}

float AIPaddle::GetVelocity() const
{
	return _velocity;
}

void AIPaddle::Update(sf::Time elapsed)
{
	const GameBall* gameball = static_cast<GameBall*>(Game::GetObjectManager().Get("Ball"));

	sf::Vector2f ballPosition = gameball->GetPosition();

	if (GetPosition().x - 20 < ballPosition.x)
	{
		float x = GetPosition().x;
		_velocity += 10.0f;
	}
	else if (GetPosition().x + 20 > ballPosition.x)
	{
		float x = GetPosition().x;
		_velocity -= 10.0f;
	}
	else 
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