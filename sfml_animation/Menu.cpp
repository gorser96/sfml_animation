#include "Menu.h"
#include <iostream>
#include "SpriteHelper.h"

Menu::Menu(std::string fileName)
	: _isActive(false)
{
	_texture.loadFromFile(fileName);
	_btn.setTexture(_texture);
	_btn.setPosition(10, 10);
	_btn.setScale(0.2, 0.2);
	_btn.setColor(sf::Color(75, 170, 211, 128));

	_selectedFrame = 0;
	_frames[1].setSprite("images\\frame.png", sf::IntRect(0, 0, 514, 663));
	_masks[1].setBaseRotation(0);
	_masks[1].setSpeed(5);

	_selectedMask = 0;
	_masks[1].setSprite("images\\lovers_398_198_5_4.png", sf::IntRect(0, 0, 398, 198));
	_masks[1].setBaseRotation(0);
	_masks[1].setSpeed(5);

	_selectedBackground = 0;
	_backgrounds[1].setSprite("images\\background1.jpg", sf::IntRect(0, 0, 1920, 1440));
	_backgrounds[1].setBaseRotation(0);
	_backgrounds[1].setSpeed(5);
	_backgrounds[2].setSprite("images\\background2.jpg", sf::IntRect(0, 0, 2758, 1919));
	_backgrounds[2].setBaseRotation(0);
	_backgrounds[2].setSpeed(5);

	_menuField.workspace.setFillColor(sf::Color(75, 170, 211, 64));

	_menuField.frameFont.loadFromFile("Caveat-Regular.ttf");
	_menuField.frameTxt.setFont(_menuField.frameFont);
	_menuField.frameTxt.setString(L"Рамка");
	sf::FloatRect ftPos = _menuField.frameTxt.getLocalBounds();
	_menuField.frameTxt.setOrigin(
		ftPos.left + ftPos.width / 2.0f,
		ftPos.top + ftPos.height / 2.0f);

	_menuField.frameTxt.setCharacterSize(24);
	_menuField.frameTxt.setFillColor(sf::Color::Black);

	_menuField.frameLeftTexture.loadFromFile("images\\left.png");
	_menuField.frameLeft.setTexture(_menuField.frameLeftTexture);
	_menuField.frameLeft.setScale(sf::Vector2f(0.1, 0.1));
	sf::FloatRect flPos = _menuField.frameLeft.getLocalBounds();
	_menuField.frameLeft.setOrigin(
		flPos.left + flPos.width / 2.0f,
		flPos.top + flPos.height / 2.0f);

	_menuField.frameRightTexture.loadFromFile("images\\right.png");
	_menuField.frameRight.setTexture(_menuField.frameRightTexture);
	_menuField.frameRight.setScale(sf::Vector2f(0.1, 0.1));
	sf::FloatRect frPos = _menuField.frameRight.getLocalBounds();
	_menuField.frameRight.setOrigin(
		frPos.left + frPos.width / 2.0f,
		frPos.top + frPos.height / 2.0f);

	_frames[1].setScale(getScaling(_frames[1].getSize(),
		sf::Vector2f(_menuField.frameLeft.getLocalBounds().width * _menuField.frameLeft.getScale().x, _menuField.frameLeft.getLocalBounds().height * _menuField.frameLeft.getScale().y)
	));
	_menuField.frameSprite = _masks[_selectedMask];
	if (_menuField.frameSprite.isInit())
	{
		_menuField.frameSprite.setScale(
			getScaling(sf::Vector2f(_menuField.frameSprite.getSprite().getTextureRect().width, _menuField.frameSprite.getSprite().getTextureRect().height),
				sf::Vector2f(_menuField.frameLeft.getTextureRect().width * _menuField.frameLeft.getScale().x, _menuField.frameLeft.getTextureRect().height * _menuField.frameLeft.getScale().y))
		);
	}

	_menuField.maskFont.loadFromFile("Caveat-Regular.ttf");
	_menuField.maskTxt.setFont(_menuField.maskFont);
	_menuField.maskTxt.setString(L"Маска");
	sf::FloatRect mtPos = _menuField.maskTxt.getLocalBounds();
	_menuField.maskTxt.setOrigin(
		mtPos.left + mtPos.width / 2.0f,
		mtPos.top + mtPos.height / 2.0f);

	_menuField.maskTxt.setCharacterSize(24);
	_menuField.maskTxt.setFillColor(sf::Color::Black);

	_menuField.maskLeftTexture.loadFromFile("images\\left.png");
	_menuField.maskLeft.setTexture(_menuField.maskLeftTexture);
	_menuField.maskLeft.setScale(sf::Vector2f(0.1, 0.1));
	sf::FloatRect mlPos = _menuField.maskLeft.getLocalBounds();
	_menuField.maskLeft.setOrigin(
		mlPos.left + mlPos.width / 2.0f,
		mlPos.top + mlPos.height / 2.0f);

	_menuField.maskRightTexture.loadFromFile("images\\right.png");
	_menuField.maskRight.setTexture(_menuField.maskRightTexture);
	_menuField.maskRight.setScale(sf::Vector2f(0.1, 0.1));
	sf::FloatRect mrPos = _menuField.maskRight.getLocalBounds();
	_menuField.maskRight.setOrigin(
		mrPos.left + mrPos.width / 2.0f,
		mrPos.top + mrPos.height / 2.0f);

	_masks[1].setScale(getScaling(_masks[1].getSize(),
		sf::Vector2f(_menuField.maskLeft.getLocalBounds().width * _menuField.maskLeft.getScale().x, _menuField.maskLeft.getLocalBounds().height * _menuField.maskLeft.getScale().y)
	));

	_menuField.maskSprite = _masks[_selectedMask];
	if (_menuField.maskSprite.isInit())
	{
		_menuField.maskSprite.setScale(
			getScaling(sf::Vector2f(_menuField.maskSprite.getSprite().getTextureRect().width, _menuField.maskSprite.getSprite().getTextureRect().height),
				sf::Vector2f(_menuField.maskLeft.getTextureRect().width * _menuField.maskLeft.getScale().x, _menuField.maskLeft.getTextureRect().height * _menuField.maskLeft.getScale().y))
		);
	}

	_menuField.backgroundFont.loadFromFile("Caveat-Regular.ttf");
	_menuField.backgroundTxt.setFont(_menuField.backgroundFont);
	_menuField.backgroundTxt.setString(L"Фон");
	sf::FloatRect btPos = _menuField.backgroundTxt.getLocalBounds();
	_menuField.backgroundTxt.setOrigin(
		btPos.left + btPos.width / 2.0f,
		btPos.top + btPos.height / 2.0f);

	_menuField.backgroundTxt.setCharacterSize(24);
	_menuField.backgroundTxt.setFillColor(sf::Color::Black);

	_menuField.backgroundLeftTexture.loadFromFile("images\\left.png");
	_menuField.backgroundLeft.setTexture(_menuField.backgroundLeftTexture);
	_menuField.backgroundLeft.setScale(sf::Vector2f(0.1, 0.1));
	sf::FloatRect blPos = _menuField.backgroundLeft.getLocalBounds();
	_menuField.backgroundLeft.setOrigin(
		blPos.left + blPos.width / 2.0f,
		blPos.top + blPos.height / 2.0f);

	_menuField.backgroundRightTexture.loadFromFile("images\\right.png");
	_menuField.backgroundRight.setTexture(_menuField.backgroundRightTexture);
	_menuField.backgroundRight.setScale(sf::Vector2f(0.1, 0.1));
	sf::FloatRect brPos = _menuField.backgroundRight.getLocalBounds();
	_menuField.backgroundRight.setOrigin(
		brPos.left + brPos.width / 2.0f,
		brPos.top + brPos.height / 2.0f);

	_backgrounds[1].setScale(getScaling(_backgrounds[1].getSize(),
		sf::Vector2f(_menuField.backgroundLeft.getLocalBounds().width * _menuField.backgroundLeft.getScale().x, _menuField.backgroundLeft.getLocalBounds().height * _menuField.backgroundLeft.getScale().y)
	));
	_backgrounds[2].setScale(getScaling(_backgrounds[2].getSize(),
		sf::Vector2f(_menuField.backgroundLeft.getLocalBounds().width * _menuField.backgroundLeft.getScale().x, _menuField.backgroundLeft.getLocalBounds().height * _menuField.backgroundLeft.getScale().y)
	));

	_menuField.backgroundSprite = _backgrounds[_selectedMask];
	if (_menuField.backgroundSprite.isInit())
	{
		_menuField.backgroundSprite.setScale(
			getScaling(sf::Vector2f(_menuField.backgroundSprite.getSprite().getTextureRect().width, _menuField.backgroundSprite.getSprite().getTextureRect().height),
				sf::Vector2f(_menuField.backgroundLeft.getTextureRect().width * _menuField.backgroundLeft.getScale().x, _menuField.backgroundLeft.getTextureRect().height * _menuField.backgroundLeft.getScale().y))
		);
	}
}

void Menu::draw(sf::RenderWindow& window)
{
	if (_isActive)
	{
		window.draw(_menuField.workspace);
		window.draw(_menuField.frameTxt);
		window.draw(_menuField.frameLeft);
		window.draw(_menuField.frameRight);
		if (_menuField.frameSprite.isInit())
		{
			window.draw(_menuField.frameSprite.getSprite());
		}
		window.draw(_menuField.maskTxt);
		window.draw(_menuField.maskLeft);
		window.draw(_menuField.maskRight);
		if (_menuField.maskSprite.isInit())
		{
			window.draw(_menuField.maskSprite.getSprite());
		}
		window.draw(_menuField.backgroundTxt);
		window.draw(_menuField.backgroundLeft);
		window.draw(_menuField.backgroundRight);
		if (_menuField.backgroundSprite.isInit())
		{
			window.draw(_menuField.backgroundSprite.getSprite());
		}
	}
	else
	{
		window.draw(_btn);
	}
}

void Menu::update(sf::RenderWindow& window)
{
	if (clock.getElapsedTime().asMilliseconds() > 50.0f)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			// transform the mouse position from window coordinates to world coordinates
			sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

			if (_isActive)
			{
				// retrieve the bounding box of the sprite
				sf::FloatRect bounds = _menuField.workspace.getGlobalBounds();
				// hit test
				if (bounds.contains(mouse))
				{
					//clicking in menu field
					sf::FloatRect flbg = _menuField.frameLeft.getGlobalBounds();
					if (flbg.contains(mouse))
					{
						//clicking in frame left
						if (_selectedFrame > 0)
						{
							_selectedFrame--;
							_menuField.frameSprite = _frames[_selectedFrame];
						}
					}
					else
					{
						sf::FloatRect frbg = _menuField.frameRight.getGlobalBounds();
						if (frbg.contains(mouse))
						{
							//clicking in frame right
							if (_selectedFrame < MAX_NUM_FRAMES - 1)
							{
								_selectedFrame++;
								_menuField.frameSprite = _frames[_selectedFrame];
							}
						}
						else
						{
							sf::FloatRect mlbg = _menuField.maskLeft.getGlobalBounds();
							if (mlbg.contains(mouse))
							{
								//clicking in mask left
								if (_selectedMask > 0)
								{
									_selectedMask--;
									_menuField.maskSprite = _masks[_selectedMask];
								}
							}
							else
							{
								sf::FloatRect mrbg = _menuField.maskRight.getGlobalBounds();
								if (mrbg.contains(mouse))
								{
									//clicking in mask right
									if (_selectedMask < MAX_NUM_MASKS - 1)
									{
										_selectedMask++;
										_menuField.maskSprite = _masks[_selectedMask];
									}
								}
								else
								{
									sf::FloatRect blbg = _menuField.backgroundLeft.getGlobalBounds();
									if (blbg.contains(mouse))
									{
										//clicking in background left
										if (_selectedBackground > 0)
										{
											_selectedBackground--;
											_menuField.backgroundSprite = _backgrounds[_selectedBackground];
										}
									}
									else
									{
										sf::FloatRect brbg = _menuField.backgroundRight.getGlobalBounds();
										if (brbg.contains(mouse))
										{
											//clicking in background right
											if (_selectedBackground < MAX_NUM_BACKGROUNDS - 1)
											{
												_selectedBackground++;
												_menuField.backgroundSprite = _backgrounds[_selectedBackground];
											}
										}
										else
										{

										}
									}
								}
							}
						}
					}
				}
				else
				{
					//hide menu field
					_isActive = false;
					_btn.setPosition(10, 10);
				}
				_updatePositions();
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
					_menuField.workspace.setSize(sf::Vector2f(200, wSize.y - 20));
					_updatePositions();
					_isActive = true;
				}
			}
		}
		clock.restart();
	}
}

void Menu::_updatePositions()
{
	_menuField.workspace.setPosition(10, 10);
	sf::Vector2f wgPos = _menuField.workspace.getPosition();
	sf::FloatRect wlPos = _menuField.workspace.getLocalBounds();

	float padding = 20;

	sf::Vector2f blockPoint1(wgPos.x + wlPos.width / 2, wgPos.y + (1 * wlPos.height) / 3);
	sf::Vector2f blockPoint2(wgPos.x + wlPos.width / 2, wgPos.y + (2 * wlPos.height) / 3);
	sf::Vector2f blockPoint3(wgPos.x + wlPos.width / 2, wgPos.y + (3 * wlPos.height) / 3);

	_menuField.frameTxt.setPosition(
		blockPoint1.x,
		wgPos.y + _menuField.frameTxt.getLocalBounds().height + padding);
	_menuField.frameLeft.setPosition(
		wgPos.x + _menuField.frameLeft.getLocalBounds().width * _menuField.frameLeft.getScale().x,
		blockPoint1.y - _menuField.frameLeft.getLocalBounds().height * _menuField.frameLeft.getScale().y - padding);
	_menuField.frameRight.setPosition(
		wgPos.x + wlPos.width - _menuField.frameRight.getLocalBounds().width * _menuField.frameRight.getScale().x,
		blockPoint1.y - _menuField.frameRight.getLocalBounds().height * _menuField.frameRight.getScale().y - padding);
	_menuField.frameSprite.setPosition(
		blockPoint1.x,
		blockPoint1.y - _menuField.frameSprite.getLocalBounds().height * _menuField.frameSprite.getScale().y - padding);

	_menuField.maskTxt.setPosition(
		blockPoint2.x,
		blockPoint1.y + _menuField.maskTxt.getLocalBounds().height + padding);
	_menuField.maskLeft.setPosition(
		wgPos.x + _menuField.maskLeft.getLocalBounds().width * _menuField.maskLeft.getScale().x,
		blockPoint2.y - _menuField.maskLeft.getLocalBounds().height * _menuField.maskLeft.getScale().y - padding);
	_menuField.maskRight.setPosition(
		wgPos.x + wlPos.width - _menuField.maskRight.getLocalBounds().width * _menuField.maskRight.getScale().x,
		blockPoint2.y - _menuField.maskRight.getLocalBounds().height * _menuField.maskRight.getScale().y - padding);
	_menuField.maskSprite.setPosition(
		blockPoint2.x,
		blockPoint2.y - _menuField.maskSprite.getLocalBounds().height * _menuField.maskSprite.getScale().y - padding);

	_menuField.backgroundTxt.setPosition(
		blockPoint3.x,
		blockPoint2.y + _menuField.backgroundTxt.getLocalBounds().height + padding);
	_menuField.backgroundLeft.setPosition(
		wgPos.x + _menuField.backgroundLeft.getLocalBounds().width * _menuField.backgroundLeft.getScale().x,
		blockPoint3.y - _menuField.backgroundLeft.getLocalBounds().height * _menuField.backgroundLeft.getScale().y - padding);
	_menuField.backgroundRight.setPosition(
		wgPos.x + wlPos.width - _menuField.backgroundRight.getLocalBounds().width * _menuField.backgroundRight.getScale().x,
		blockPoint3.y - _menuField.backgroundRight.getLocalBounds().height * _menuField.backgroundRight.getScale().y - padding);
	_menuField.backgroundSprite.setPosition(
		blockPoint3.x,
		blockPoint3.y - _menuField.backgroundSprite.getLocalBounds().height * _menuField.backgroundSprite.getScale().y - padding);
}