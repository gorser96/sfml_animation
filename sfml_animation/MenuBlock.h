#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "AnimatedSprite.h"
#include <vector>
#include <memory>

class MenuBlock
{
public:
	MenuBlock();
	void update(sf::RenderWindow&);
	void setPosition(sf::Vector2f, float, sf::FloatRect);
	void load(std::string);
	void draw(sf::RenderWindow&);
	int selectedIndex;
	std::shared_ptr<sf::Text> txt;
	std::shared_ptr<sf::Font> font;
	std::shared_ptr<AnimatedSprite> selectedSprite;
	std::shared_ptr<sf::Sprite> left;
	std::shared_ptr<sf::Texture> leftTexture;
	std::shared_ptr<sf::Sprite> right;
	std::shared_ptr<sf::Texture> rightTexture;
	std::vector<std::shared_ptr<AnimatedSprite>> sprites;
};
