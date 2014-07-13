#pragma once
#include "VisibleGameObject.h"
class GameBall :
	public VisibleGameObject
{
public:
	GameBall();
	virtual ~GameBall();
	void Update(sf::Time);
	float GetRandomAngle();
	void Reset();

private:
	float _velocity;
	float _angle;
	float _elapsedTimeSinceStart;

	float LinearVelocityX(float angle);
	float LinearVelocityY(float angle);
};