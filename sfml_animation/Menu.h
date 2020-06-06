#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "AnimatedSprite.h"
#define MAX_NUM_MASKS 2
#define MAX_NUM_FRAMES 2
#define MAX_NUM_BACKGROUNDS 2

class Menu
{
public:
	Menu(std::string);
	void draw(sf::RenderWindow&);
	void update(sf::RenderWindow&);
private:
	struct MenuField
	{
		sf::RectangleShape workspace;

		sf::Text frameTxt;
		sf::Font frameFont;
		AnimatedSprite frameSprite;
		sf::Sprite frameLeft;
		sf::Texture frameLeftTexture;
		sf::Sprite frameRight;
		sf::Texture frameRightTexture;

		sf::Text maskTxt;
		sf::Font maskFont;
		AnimatedSprite maskSprite;
		sf::Sprite maskLeft;
		sf::Texture maskLeftTexture;
		sf::Sprite maskRight;
		sf::Texture maskRightTexture;

		sf::Text backgroundTxt;
		sf::Font backgroundFont;
		AnimatedSprite backgroundSprite;
		sf::Sprite backgroundLeft;
		sf::Texture backgroundLeftTexture;
		sf::Sprite backgroundRight;
		sf::Texture backgroundRightTexture;
	} _menuField;
	sf::Texture _texture;
	sf::Sprite _btn;
	bool _isActive;

	void _updatePositions();

	unsigned int _selectedMask;
	unsigned int _selectedFrame;
	unsigned int _selectedBackground;

	AnimatedSprite _masks[MAX_NUM_MASKS];
	AnimatedSprite _frames[MAX_NUM_FRAMES];
	AnimatedSprite _backgrounds[MAX_NUM_BACKGROUNDS];
};

