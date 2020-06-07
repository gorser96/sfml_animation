#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include "AnimatedSprite.h"
#include "MenuBlock.h"
#define BUTTON_FILE "images/menu_btn.png"
#define ARROW_LEFT_FILE "images/left.png"
#define ARROW_RIGHT_FILE "images/right.png"

class MenuUpdated
{
public:
	MenuUpdated();
	void draw(sf::RenderWindow&);
	void update(sf::RenderWindow&);
private:
	sf::RectangleShape _workspace;
	std::vector<MenuBlock> _blocks;
	sf::Texture _textureBtn;
	sf::Sprite _btn;
	bool _isActive;
	sf::Clock clock;
};

