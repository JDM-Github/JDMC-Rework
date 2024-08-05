#include "Sprites/JDMC_LabelSprite.hpp"
#include "Sprites/JDMC_CharBitmaps.hpp"
#include "JDMC_drawer.hpp"
#include "JDMC_functions.hpp"
#include <fstream>
#include <iostream>

JDMC::LabelSprite::LabelSprite(JDMC::Pos2F position, const std::string& text, short fontSize)
	: JDMC::EntitySprite()
{
	this->text = text;
	this->SetPosition(position);
	this->SetFontSize(fontSize);
}

JDMC::LabelSprite::LabelSprite(JDMC::Pos2F position, const std::string& text)
	: JDMC::EntitySprite()
{
	this->text = text;
	this->SetPosition(position);
	this->SetFontSize(1);
}

JDMC::LabelSprite::LabelSprite(const std::string& text, short fontSize)
	: JDMC::EntitySprite()
{
	this->text = text;
	this->SetPosition({0, 0});
	this->SetFontSize(fontSize);
}

JDMC::LabelSprite::LabelSprite(const std::string& text)
	: JDMC::EntitySprite()
{
	this->text = text;
	this->SetPosition({0, 0});
	this->SetFontSize(1);
}

JDMC::LabelSprite::LabelSprite(const char *text)
	: JDMC::EntitySprite()
{
	this->text = std::string(text);
	this->SetPosition({0, 0});
	this->SetFontSize(1);
}

void JDMC::LabelSprite::Render(
	const JDMC::Color Color,
	const bool Alpha,
	const bool Cycle)
{
	short x_adder = 0, y_adder = 0;
	for (short i = 0; i < this->Sprite.SpriteBody.size() && y_adder < this->Sprite.Height; i++)
	{
		if (this->Sprite.SpriteBody[i] == JDMC::Pixel::NEWLINE)
		{
			x_adder = 0;
			y_adder++;
			continue;
		}
		if (x_adder >= this->Sprite.Width
		|| (Alpha && this->Sprite.SpriteBody[i] == JDMC::Pixel::BLANK))
			continue;

		Drawer::DrawBaseOnCycle({this->Position.X + x_adder, this->Position.Y + y_adder},
			this->Sprite.SpriteBody[i], Color, Alpha, Cycle);

		x_adder++;
	}
}


void JDMC::LabelSprite::SetText(const std::string &text)
{
	this->text = text;
	this->SetFontSize(this->fontSize);
}

void JDMC::LabelSprite::SetFontSize(short fontSize)
{
	this->fontSize = fontSize;
	// this->Sprite.Width = this->text.length() * 4 * fontSize;
	this->Sprite.Height = 5 * fontSize;
	this->updateFont();
}

void JDMC::LabelSprite::updateFont()
{
	std::wstring spriteBody;
	for (int row = 0; row < 5; row++)
	{
		std::wstring line; // Prepare the line
		for (char c : text) 
		{
			if (JDMC::CharBitmaps::charBitmaps.find(c) != JDMC::CharBitmaps::charBitmaps.end())
			{
				// Create the line based on row, example first line of A {0, 1, 1, 0}
				auto scaledBitmap = JDMC::CharBitmaps::scaleLineBitmap(
					JDMC::CharBitmaps::charBitmaps.at(c), this->fontSize, row);

				// Add to line
				this->Sprite.Width += scaledBitmap.length();
				line += scaledBitmap;
				continue;
			}
			// If not recognised, act like it's a blank letter
			for (int i = 0; i < 3 * this->fontSize; ++i)
				line += JDMC::Pixel::BLANK;

			line += L' ';
		}

		// Scale to height, since we already get the line
		for (int i = 0; i < this->fontSize; i++)
		{
			spriteBody += line;
			spriteBody += L'\n';
		}
	}
	this->Sprite.Width = spriteBody.length() - 1;
	this->Sprite.SpriteBody = spriteBody;
}
