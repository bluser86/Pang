#pragma once
#include "VisibleGameObject.h"

class PlayerPaddle :
	public VisibleGameObject
{
public:
	PlayerPaddle();
	~PlayerPaddle();

	void Update(sf::Time elapsed);
	void Draw(sf::RenderWindow& window);

	float GetVelocity() const;

private:
	float _velocity; // -- left ++ right
	float _maxVelocity;
};