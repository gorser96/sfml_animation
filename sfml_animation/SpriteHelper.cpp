#include "SpriteHelper.h"

sf::Vector2f getScaling(sf::Vector2f sizeFrom, sf::Vector2f sizeTo)
{
	return sf::Vector2f(sizeTo.x / sizeFrom.x, sizeTo.y / sizeFrom.y);
}