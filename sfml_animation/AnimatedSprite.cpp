#include "AnimatedSprite.h"
#include "VectorHelper.h"
#include <math.h>

AnimatedSprite::AnimatedSprite()
{
	_isInit = false;
	_current = 0;
}

AnimatedSprite::AnimatedSprite(std::string spriteFile, sf::IntRect rect, float baseRotation = 0, float speed = 5)
	: _baseRotation(baseRotation),
	_current(0),
	_speed(speed),
	_rect(rect)
{
	_texture.loadFromFile(spriteFile);
	_sprite.setTexture(_texture);
	_sprite.setTextureRect(_rect);
	_meta = getSpriteMetaData();
	_sprite.setOrigin(sf::Vector2f(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2));
	_isInit = true;
}

AnimatedSprite::~AnimatedSprite()
{
}

sf::Sprite AnimatedSprite::getSprite()
{
	_sprite.setTextureRect(_rect);
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

SpriteMetaData AnimatedSprite::getSpriteMetaData()
{
	SpriteMetaData result;
	result.totalNum = 0;
	result.rowNum = 0;
	result.colNum = 0;

	sf::Image image = _texture.copyToImage();
	sf::Vector2u size = _texture.getSize();
	sf::IntRect rectSourceSprite(_rect);
	for (size_t i = 0; i < size.y; i += _rect.height, result.rowNum++)
	{
		rectSourceSprite.top = i;
		result.colNum = 0;
		for (size_t j = 0; j < size.x; j += _rect.width, result.colNum++)
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
	result.rowNum = size.y / _rect.height;
	result.colNum = size.x / _rect.width;
	return result;
}

void AnimatedSprite::setScale(sf::Vector2f scale)
{
	_sprite.setScale(scale);
}

void AnimatedSprite::move(sf::Vector2f target)
{
	sf::Vector2f lPos = getLocalPosition();
	setRotation(RadToDeg(AngleTo(lPos, lPos + target)));
	_sprite.move(target);
}

sf::Vector2f AnimatedSprite::getLocalPosition()
{
	sf::FloatRect rect = _sprite.getGlobalBounds();
	return sf::Vector2f(rect.left + rect.width / 2, rect.top + rect.height / 2);
}

sf::Vector2f AnimatedSprite::getGlobalPosition()
{
	return _sprite.getPosition();
}

float AnimatedSprite::getRotation()
{
	return _sprite.getRotation() + _baseRotation;
}

sf::Vector2f AnimatedSprite::getSize()
{
	return sf::Vector2f(_sprite.getLocalBounds().width * _sprite.getScale().x, _sprite.getLocalBounds().height * _sprite.getScale().y);
}

sf::FloatRect AnimatedSprite::getLocalBounds()
{
	return _sprite.getLocalBounds();
}

sf::Vector2f AnimatedSprite::getScale()
{
	return _sprite.getScale();
}

void AnimatedSprite::setRotation(float angle)
{
	return _sprite.setRotation(angle + _baseRotation);
}

void AnimatedSprite::setPosition(sf::Vector2f position)
{
	_sprite.setPosition(position);
}

void AnimatedSprite::setPosition(float x, float y)
{
	_sprite.setPosition(x, y);
}

void AnimatedSprite::setSprite(std::string spriteName, sf::IntRect rect)
{
	_rect = rect;
	_texture.loadFromFile(spriteName);
	_sprite.setTexture(_texture);
	_sprite.setTextureRect(_rect);
	_meta = getSpriteMetaData();
	_sprite.setOrigin(sf::Vector2f(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2));
	_current = 0;
	_isInit = true;
}

void AnimatedSprite::setBaseRotation(float baseRotation)
{
	_baseRotation = baseRotation;
}

void AnimatedSprite::setSpeed(float speed)
{
	_speed = speed;
}

void AnimatedSprite::setOrigin(float x, float y)
{
	_sprite.setOrigin(x, y);
}
void AnimatedSprite::setOrigin(sf::Vector2f origin)
{
	_sprite.setOrigin(origin);
}

bool AnimatedSprite::isInit()
{
	return _isInit;
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
	_sprite.setPosition(pos);
}