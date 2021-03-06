#include "Include.h"
#include "GameBall.h"
#include "Game.h"
#include "PlayerPaddle.h"
#include "AIPaddle.h"
#include "AudioServiceLocator.h"

GameBall::GameBall() :
	_velocity(230.0f),
	_elapsedTimeSinceStart(0.0f)
{
	Load("images/ball.png");
	assert(IsLoaded());

	GetSprite().setOrigin(15, 15);

	_angle = GetRandomAngle();
}

GameBall::~GameBall()
{

}

void GameBall::Update(sf::Time elapsed)
{
	_elapsedTimeSinceStart += elapsed.asSeconds();

	if(_elapsedTimeSinceStart < 3.0f) 
	{
		return;
	}

	float moveAmount = _velocity * elapsed.asSeconds();

	float moveByX = LinearVelocityX(_angle) * moveAmount;
	float moveByY = LinearVelocityY(_angle) * moveAmount;

	// Wall collision
	if(GetPosition().x + moveByX <= 0 + GetWidth() / 2
		|| GetPosition().x + GetHeight() / 2 + moveByX >= Game::SCREEN_WIDTH)
	{
		_angle = 360.0f - _angle;
		if(_angle > 260.0f && _angle < 280.0f) 
		{
			_angle += 20.0f;
		}

		if(_angle > 80.0f && _angle < 100.0f) 
		{
			_angle += 20.0f;
		}

		moveByX = -moveByX;
	}

	PlayerPaddle* player1 = dynamic_cast<PlayerPaddle*>(Game::GetObjectManager().Get("Paddle1"));

	if(player1 != NULL)
	{
		sf::Rect<float> p1BB = player1->GetBoundingBox();
		sf::Rect<float> ballBB = GetBoundingBox();

		// Paddle collision
		if(p1BB.intersects(GetBoundingBox()))
		{
			AudioServiceLocator::GetAudioProvider()->PlaySound("audio/plop.ogg");

			_angle = 360.0f - (_angle - 180.0f);

			if(_angle > 360.0f)
			{
				_angle -= 360.0f;
			}

			moveByY = -moveByY;

			if(GetBoundingBox().top + GetBoundingBox().height > player1->GetBoundingBox().top)
			{
				SetPosition(GetPosition().x, player1->GetBoundingBox().top - GetHeight() - 1);
			}

			float playerVelocity = player1->GetVelocity();

			// Adjust angles for when the paddle is moving one way or another
			// Player moving left
			if(playerVelocity < 0)
			{
				_angle -= 20.0f;

				if(_angle > 360.0f) 
				{
					_angle -= 360.0f;
				}
			}
			// Player moving right
			else if(playerVelocity > 0) 
			{
				_angle += 20.0f;

				if(_angle > 360.0f) 
				{
					_angle -= 360.0f;
				}
			}

			_velocity += 50.0f;
		}
	}

	AIPaddle* player2 = dynamic_cast<AIPaddle*>(Game::GetObjectManager().Get("Paddle2"));

	if(player2 != NULL)
	{
		sf::Rect<float> p2BB = player2->GetBoundingBox();
		sf::Rect<float> ballBB = GetBoundingBox();

		// Paddle collision
		if(p2BB.intersects(GetBoundingBox()))
		{
			AudioServiceLocator::GetAudioProvider()->PlaySound("audio/plop.ogg");

			if(ballBB.top < p2BB.top + p2BB.height)
			{
				SetPosition(GetPosition().x, p2BB.top + p2BB.height + GetHeight() + 1);
			}

			_angle = 180 - _angle;
			moveByY = -moveByY;

			float playerVelocity = player1->GetVelocity();

			// Adjust angles for when the paddle is moving one way or another
			// Player moving left
			if(playerVelocity < 0)
			{
				_angle -= 20.0f;

				if(_angle > 360.0f) 
				{
					_angle -= 360.0f;
				}
			}
			// Player moving right
			else if(playerVelocity > 0) 
			{
				_angle += 20.0f;

				if(_angle > 360.0f) 
				{
					_angle -= 360.0f;
				}
			}

			_velocity += 50.0f;
		}
	}

	if(GetPosition().y - GetHeight() / 2 <= 0)
	{
		Reset();
	}

	if(GetPosition().y + GetHeight() / 2 + moveByY >= Game::SCREEN_HEIGHT)
	{
		Reset();
	}

	GetSprite().move(moveByX, moveByY);
}

void GameBall::Reset()
{
	GetSprite().setPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);

	_angle = GetRandomAngle();
	_velocity = 220.0f;
	_elapsedTimeSinceStart = 0.0f;
}

float GameBall::GetRandomAngle()
{
	return std::rand() % 360 + 1;
}

float GameBall::LinearVelocityX(float angle)
{
	angle -= 90;
	if(angle < 0)
	{
		angle = 360 + angle;
	}

	return (float)std::cos(angle * ( 3.1415926 / 180.0f ));
}

float GameBall::LinearVelocityY(float angle)
{
	angle -= 90;
	if(angle < 0)
	{
		angle = 360 + angle;
	}

	return (float)std::sin(angle * ( 3.1415926 / 180.0f ));
}