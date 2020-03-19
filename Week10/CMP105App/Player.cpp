#include "Player.h"

Player::Player()
{
	scale = 16.0f;
	gravity = sf::Vector2f(0, 9.8f) * scale;
	jumpVector = sf::Vector2f(0, -9.8f) * scale;
	isJumping = false;
}

void Player::handleInput(float dt)
{
	speed = 0.0f;
	
	if (input->isKeyDown(sf::Keyboard::D))
	{
		speed = 100.0f;
		velocity.x = speed * dt;
		move(velocity);
	}
	else if (input->isKeyDown(sf::Keyboard::A))
	{
		speed = -100.0f;
		velocity.x = speed * dt;
		move(velocity);
	}

	if (input->isKeyDown(sf::Keyboard::Space))
	{
		if (!isJumping)
		{
			stepVelocity = sf::Vector2f(velocity.x, jumpVector.y);
			isJumping = true;
		}
	}
}

void Player::update(float dt)
{

	if (stepVelocity.y == 0)
	{
		isJumping = false;
	}

	sf::Vector2f pos = stepVelocity * dt + 0.5f * gravity * dt * dt;
	stepVelocity += gravity * dt;
	setPosition(getPosition() + pos);

	if (getPosition().y >= 658)
	{
		setPosition(getPosition().x, 658);
		stepVelocity = sf::Vector2f(0, 0);
	}

	

}

void Player::collisionResponse(GameObject* collider)
{
	float diffX = (collider->getPosition().x + (collider->getSize().x/2)) - (getPosition().x + (getSize().x/2));
	float diffY = (collider->getPosition().y + (collider->getSize().x/2)) - (getPosition().y + (getSize().x/2));
	
	if (abs(diffX) < abs(diffY))
	{
		if (diffY < 0)
		{
			stepVelocity.y = -0.1;
			setPosition(getPosition().x, collider->getPosition().y + getSize().y*2);
		}
		else
		{
			if (stepVelocity.y > 0)
			{
				stepVelocity.y = 0;
				setPosition(getPosition().x, collider->getPosition().y - getSize().y);
			}
		}
	}
	else if (abs(diffX) > abs(diffY))
	{
		if (diffX < 0)
		{
			velocity.x = 0;
			setPosition(collider->getPosition().x + getSize().x*2, getPosition().y);
		}
		else
		{
			velocity.x = 0;
			setPosition(collider->getPosition().x - getSize().x, getPosition().y);
		}
	}
		
}

Player::~Player()
{

}