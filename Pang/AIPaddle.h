#include "Include.h"
#include "VisibleGameObject.h"
class AIPaddle :
	public VisibleGameObject
{
public:
	AIPaddle();
	~AIPaddle();

	void Update(sf::Time elapsed);
	void Draw(sf::RenderWindow& window);

	float GetVelocity() const;

private:
	float _velocity; // -- left ++ right
	float _maxVelocity;
};