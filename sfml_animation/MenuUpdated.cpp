#include "MenuUpdated.h"

MenuUpdated::MenuUpdated()
	: _isActive(false)
{
	_textureBtn.loadFromFile(BUTTON_FILE);
	_btn.setTexture(_textureBtn);
	_btn.setPosition(10, 10);
	_btn.setScale(0.2, 0.2);
	_btn.setColor(sf::Color(75, 170, 211, 128));

	_workspace.setFillColor(sf::Color(75, 170, 211, 64));

	_blocks.push_back(MenuBlock());
	_blocks[0].txt->setString(L"Рамка");
	_blocks[0].load("images/frames");
	_blocks[0].selectedSprite = std::shared_ptr<AnimatedSprite>(_blocks[0].sprites[0]);
	_blocks.push_back(MenuBlock());
	_blocks[1].txt->setString(L"Эффект");
	_blocks[1].load("images/effects");
	_blocks[1].selectedSprite = std::shared_ptr<AnimatedSprite>(_blocks[1].sprites[0]);
	_blocks.push_back(MenuBlock());
	_blocks[2].txt->setString(L"Фон");
	_blocks[2].load("images/backgrounds");
	_blocks[2].selectedSprite = std::shared_ptr<AnimatedSprite>(_blocks[2].sprites[0]);
}

void MenuUpdated::draw(sf::RenderWindow& window)
{
	if (_isActive)
	{
		window.draw(_workspace);
		for (auto& block : _blocks)
		{
			block.draw(window);
		}
	}
	else
	{
		window.draw(_btn);
	}
}

void MenuUpdated::update(sf::RenderWindow& window)
{
	if (clock.getElapsedTime().asMilliseconds() > 50.0f)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			if (_isActive)
			{
				// retrieve the bounding box of the sprite
				sf::FloatRect bounds = _workspace.getGlobalBounds();
				// hit test
				if (bounds.contains(mouse))
				{
					//clicking in menu field
					for (auto& block : _blocks)
					{
						block.update(window);
					}
				}
				else
					_isActive = false;
			}
			else
			{
				// retrieve the bounding box of the sprite
				sf::FloatRect bounds = _btn.getGlobalBounds();
				// hit test
				if (bounds.contains(mouse))
				{
					//show menu field
					sf::Vector2u wSize = window.getSize();
					_workspace.setSize(sf::Vector2f(200, wSize.y - 20));
					_workspace.setPosition(10, 10);
					sf::Vector2f wgPos = _workspace.getPosition();
					sf::FloatRect wlPos = _workspace.getLocalBounds();
					wlPos.left = wgPos.x;
					wlPos.top = wgPos.y;
					float padding = 20;
					for (int i = 0; i < _blocks.size(); i++)
					{
						_blocks[i].setPosition(sf::Vector2f(wgPos.x + wlPos.width / 2, wgPos.y + ((i + 1) * wlPos.height) / _blocks.size()), padding, wlPos);
					}
					_isActive = true;
				}
			}
		}
		clock.restart();
	}
}
