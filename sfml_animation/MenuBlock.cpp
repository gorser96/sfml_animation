#include "MenuBlock.h"
#include <filesystem>
#include "SpriteHelper.h"

namespace filesys = std::filesystem;

MenuBlock::MenuBlock()
	: txt(std::make_shared<sf::Text>()),
	font(std::make_shared<sf::Font>()),
	left(std::make_shared<sf::Sprite>()),
	right(std::make_shared<sf::Sprite>()),
	leftTexture(std::make_shared<sf::Texture>()),
	rightTexture(std::make_shared<sf::Texture>())
{
	font->loadFromFile("Caveat-Regular.ttf");
	txt->setFont(*font);
	txt->setCharacterSize(24);
	txt->setFillColor(sf::Color::Black);
	leftTexture->loadFromFile("images\\left.png");
	left->setTexture(*leftTexture);
	left->setScale(sf::Vector2f(0.1, 0.1));
	rightTexture->loadFromFile("images\\right.png");
	right->setTexture(*rightTexture);
	right->setScale(sf::Vector2f(0.1, 0.1));
	selectedIndex = 0;
}

void MenuBlock::update(sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// transform the mouse position from window coordinates to world coordinates
		sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		sf::FloatRect lgb = left->getGlobalBounds();
		if (lgb.contains(mouse))
		{
			if (selectedIndex > 0)
			{
				selectedIndex--;
				selectedSprite = std::shared_ptr(sprites[selectedIndex]);
			}
		}
		else
		{
			sf::FloatRect rbg = right->getGlobalBounds();
			if (rbg.contains(mouse))
			{
				//clicking in frame right
				if (selectedIndex < sprites.size() - 1)
				{
					selectedIndex++;
					selectedSprite = std::shared_ptr(sprites[selectedIndex]);
				}
			}
		}
	}
}

void MenuBlock::setPosition(sf::Vector2f basePosition, float padding, sf::FloatRect workspaceSize)
{
	sf::FloatRect flPos = left->getLocalBounds();
	left->setOrigin(
		flPos.left + flPos.width / 2.0f,
		flPos.top + flPos.height / 2.0f);
	left->setPosition(
		workspaceSize.left + flPos.width * left->getScale().x,
		basePosition.y - flPos.height * left->getScale().y - padding);

	sf::FloatRect frPos = right->getLocalBounds();
	right->setOrigin(
		frPos.left + frPos.width / 2.0f,
		frPos.top + frPos.height / 2.0f);
	right->setPosition(
		workspaceSize.left + workspaceSize.width - frPos.width * right->getScale().x,
		basePosition.y - frPos.height * right->getScale().y - padding);

	sf::FloatRect ftPos = txt->getLocalBounds();
	txt->setOrigin(
		ftPos.left + ftPos.width / 2.0f,
		ftPos.top + ftPos.height / 2.0f);
	txt->setPosition(
		basePosition.x,
		basePosition.y - frPos.height * right->getScale().y - padding - ftPos.height - padding);

	for (auto& sprite : sprites)
	{
		auto sPos = sprite->getLocalBounds();
		sprite->setOrigin(
			sPos.left + sPos.width / 2.0f,
			sPos.top + sPos.height / 2.0f);
		sprite->setScale(getScaling(sprite->getScale(), sprite->getSize(), sf::Vector2f(flPos.left + flPos.width * left->getScale().x, frPos.top + frPos.height * right->getScale().y)));
		sprite->setPosition(
			basePosition.x,
			basePosition.y - sprite->getLocalBounds().height * sprite->getScale().y - padding);
	}
}

void MenuBlock::load(std::string path)
{
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		sf::IntRect rect;
		rect.left = 0;
		rect.top = 0;
		auto filename = entry.path().stem().string();

		//tomato_128_128_5_6_0.png
		//background1_1920_1440_1_1_0.jpg
		//frame1_514_663_1_1_0.png

		std::string delimiter = "_";

		size_t pos = filename.find(delimiter);
		std::string name = filename.substr(0, pos);
		filename.erase(0, pos + delimiter.length());

		pos = filename.find(delimiter);
		std::string width = filename.substr(0, pos);
		filename.erase(0, pos + delimiter.length());

		pos = filename.find(delimiter);
		std::string height = filename.substr(0, pos);
		filename.erase(0, pos + delimiter.length());

		pos = filename.find(delimiter);
		std::string col = filename.substr(0, pos);
		filename.erase(0, pos + delimiter.length());

		pos = filename.find(delimiter);
		std::string row = filename.substr(0, pos);
		filename.erase(0, pos + delimiter.length());

		pos = filename.find(delimiter);
		std::string rotate = filename.substr(0, pos);
		filename.erase(0, pos + delimiter.length());

		rect.width = std::stoi(width);
		rect.height = std::stoi(height);

		sprites.push_back(std::make_shared<AnimatedSprite>(entry.path().string(), rect, std::stoi(rotate), 5));
	}
}

void MenuBlock::draw(sf::RenderWindow& window)
{
	window.draw(*txt);
	window.draw(*left);
	window.draw(*right);
	if (selectedSprite->isInit())
	{
		window.draw(selectedSprite->getSprite());
	}
}
