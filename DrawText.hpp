#pragma once

void draw_text(bool i_black, unsigned short i_x, unsigned short i_y, const std::string& i_text, sf::RenderWindow& i_window);


#include <SFML/Graphics.hpp>
#include <iostream>


void draw_text(bool i_black, unsigned short i_x, unsigned short i_y, const std::string& i_text, sf::RenderWindow& i_window)
{
	//We're gonna align the text ot the left top
	short character_x = i_x;
	short character_y = i_y;

	unsigned char character_width;

	sf::Sprite character_sprite;

	sf::Texture font_texture;
	std::cout << "loading font" << std::endl;
	if(!font_texture.loadFromFile("files\\Images\\Font.png")){
		std::cout << "err loading font" << std::endl;
	};

	//We're gonna calculate the width of the character based on the font image size
	//96 because there are 96 character in the image
	character_width = font_texture.getSize().x / 96;

	character_sprite.setTexture(font_texture);

	//We can use this to change the color of the text
	if (1 == i_black)
	{
		character_sprite.setColor(sf::Color(0, 0, 0));
	}

	for (const char a : i_text)
	{
		if ('\n' == a)
		{
			//After every newline we put increase the y-coordinate and reset the x-coordinate
			character_x = i_x;
			character_y += font_texture.getSize().y;

			continue;
		}

		//Change the position of the next character
		character_sprite.setPosition(character_x, character_y);
		//Pick the character from the font image
		character_sprite.setTextureRect(sf::IntRect(character_width * (a - 32), 0, character_width, font_texture.getSize().y));

		//Increase the x-coordinate
		character_x += character_width;

		//Draw the character
		i_window.draw(character_sprite);
	}
}