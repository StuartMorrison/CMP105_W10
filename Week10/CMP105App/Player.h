#pragma once
#include "Framework/GameObject.h"
class Player :
	public GameObject
{
public:

	float scale;
	float speed;
	bool isJumping;
	sf::Vector2f gravity;
	sf::Vector2f stepVelocity;
	sf::Vector2f direction;
	sf::Vector2f jumpVector;

	Player();
	void handleInput(float dt);
	void update(float dt) override;
	void collisionResponse(GameObject* collider);
	~Player();
};

