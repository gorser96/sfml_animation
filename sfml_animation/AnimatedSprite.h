#pragma once
#include<SFML/Graphics.hpp>
#include <string>

struct SpriteMetaData
{
	int totalNum;
	int colNum;
	int rowNum;
	sf::Vector2u last;
};

class AnimatedSprite
{
public:
	AnimatedSprite();
	AnimatedSprite(std::string, sf::IntRect, float, float);
	~AnimatedSprite();
	sf::Sprite getSprite();
	void setScale(sf::Vector2f);
	void move(sf::Vector2f);
	void moveTo(sf::Vector2f);
	sf::Vector2f getLocalPosition();
	sf::Vector2f getGlobalPosition();
	float getRotation();
	sf::Vector2f getSize();
	sf::FloatRect getLocalBounds();
	sf::Vector2f getScale();
	void setRotation(float);
	void setPosition(sf::Vector2f);
	void setPosition(float, float);
	void setSprite(std::string, sf::IntRect);
	void setBaseRotation(float);
	void setSpeed(float);
	bool isInit();

private:
	sf::Texture _texture;
	sf::Sprite _sprite;
	sf::IntRect _rect;
	SpriteMetaData _meta;
	int _current;
	float _baseRotation;
	float _speed;
	bool _isInit;

	int getSumPixels(sf::Image, sf::IntRect);
	SpriteMetaData getSpriteMetaData();
};
