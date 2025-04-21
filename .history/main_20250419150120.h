#pragma once
void drawGameBoard(Board &newBoard, sf::Sprite &mineSprite, sf::Texture &mineTexture, sf::Texture &num1Txture, sf::Texture &num2Txture, sf::Texture &num3Txture, sf::Texture &num4Txture, sf::Texture &num5Txture, sf::Texture &num6Txture, sf::Texture &num7Txture, sf::Texture &num8Txture, sf::Texture &flagTexture, sf::Texture &revealedTexture, sf::RenderWindow &gameWindow);

void drawGameBoardBase(sf::Sprite &gameSprite, sf::Texture &happyTexture, int numColumns, int numRows, sf::RenderWindow &gameWindow, sf::Texture &debugTexture, sf::Texture &pauseTexture);
