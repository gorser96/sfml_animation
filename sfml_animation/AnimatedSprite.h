#pragma once
#include<SFML/Graphics.hpp>
#include "VectorHelper.h"

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
	AnimatedSprite(sf::Sprite*, float, float);
	~AnimatedSprite();
	sf::Sprite* getSprite();
	void setScale(sf::Vector2f);
	void move(sf::Vector2f);
	void moveTo(sf::Vector2f);
	sf::Vector2f getLocalPosition();
	sf::Vector2f getGlobalPosition();
	float getRotation();
	void setRotation(float);

private:
	sf::Sprite* _sprite;
	sf::IntRect _rect;
	SpriteMetaData _meta;
	int _current;
	float _baseRotation;
	float _speed;

	int getSumPixels(sf::Image, sf::IntRect);
	SpriteMetaData getSpriteMetaData(sf::Texture, int, int);
};

AnimatedSprite::AnimatedSprite(sf::Sprite* sprite, float baseRotation = 0, float speed = 5)
	:_sprite(sprite),
	_rect(sprite->getTextureRect()),
	_baseRotation(baseRotation),
	_current(0),
	_speed(speed)
{
	_meta = getSpriteMetaData(*sprite->getTexture(), _rect.width, _rect.height);
	_sprite->setOrigin(sf::Vector2f(_sprite->getLocalBounds().width / 2, _sprite->getLocalBounds().height / 2));
}

AnimatedSprite::~AnimatedSprite()
{
}

sf::Sprite* AnimatedSprite::getSprite()
{
	_sprite->setTextureRect(_rect);
	_current = (_current + 1) % _meta.totalNum;
	_rect.left = (_current % _meta.colNum) * _rect.width;
	_rect.top = (_current / _meta.colNum) * _rect.height;
	return _sprite;
}

int AnimatedSprite::getSumPixels(sf::Image img, sf::IntRect rect)
{
	int result = 0;
	for (size_t x = rect.left + 1; x < rect.left + rect.width - 1; x++)
	{
		for (size_t y = rect.top + 1; y < rect.top + rect.height - 1; y++)
		{
			sf::Color cPixel = img.getPixel(x, y);
			result += cPixel.a * (cPixel.r + cPixel.g + cPixel.b);
		}
	}
	return result;
}

SpriteMetaData AnimatedSprite::getSpriteMetaData(sf::Texture texture, int width, int height)
{
	SpriteMetaData result;
	result.totalNum = 0;
	result.rowNum = 0;
	result.colNum = 0;

	sf::Image image = texture.copyToImage();
	sf::Vector2u size = texture.getSize();
	sf::IntRect rectSourceSprite(0, 0, width, height);
	for (size_t i = 0; i < size.y; i += height, result.rowNum++)
	{
		rectSourceSprite.top = i;
		result.colNum = 0;
		for (size_t j = 0; j < size.x; j += width, result.colNum++)
		{
			rectSourceSprite.left = j;
			if (getSumPixels(image, rectSourceSprite) != 0)
			{
				result.totalNum++;
			}
			else
			{
				result.last = sf::Vector2u(result.rowNum, result.colNum - 1);
				break;
			}
		}
	}
	result.rowNum = size.y / height;
	result.colNum = size.x / width;
	return result;
}

void AnimatedSprite::setScale(sf::Vector2f scale)
{
	_sprite->setScale(scale);
}

void AnimatedSprite::move(sf::Vector2f target)
{
	sf::Vector2f lPos = getLocalPosition();
	setRotation(RadToDeg(AngleTo(lPos, lPos + target)));
	_sprite->move(target);
}

sf::Vector2f AnimatedSprite::getLocalPosition()
{
	sf::FloatRect rect = _sprite->getGlobalBounds();
	return sf::Vector2f(rect.left + rect.width / 2, rect.top + rect.height / 2);
}

sf::Vector2f AnimatedSprite::getGlobalPosition()
{
	return _sprite->getPosition();
}

float AnimatedSprite::getRotation()
{
	return _sprite->getRotation() + _baseRotation;
}

void AnimatedSprite::setRotation(float angle)
{
	return _sprite->setRotation(angle + _baseRotation);
}

void AnimatedSprite::moveTo(sf::Vector2f target)
{
	sf::Vector2f pos = getLocalPosition();
	float distance = sqrt(pow(target.x - pos.x, 2) + pow(target.y - pos.y, 2));
	float rot = getRotation();
	float angle = DegToRad(rot - 180);
	if (distance < _speed)
	{
		return;
	}
	if (std::abs(angle) < M_PI / 2)
	{
		pos.x -= fabs(_speed * std::cos(angle));
	}
	else
	{
		if (abs(angle) > M_PI / 2)
		{
			pos.x += std::fabs(_speed * std::cos(angle));
		}
	}
	if (angle > 0 && angle < M_PI)
	{
		pos.y -= std::fabs(_speed * std::sin(angle));
	}
	else
	{
		if (angle < 0 || angle > M_PI)
		{
			pos.y += std::fabs(_speed * std::sin(angle));
		}
	}
	_sprite->setPosition(pos);
}