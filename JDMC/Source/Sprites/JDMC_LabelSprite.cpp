#include "Sprites/JDMC_LabelSprite.hpp"
#include "Sprites/JDMC_CharBitmaps.hpp"
#include "JDMC_drawer.hpp"
#include "JDMC_functions.hpp"
#include <fstream>
#include <iostream>


JDMC::LabelSprite::LabelSprite(JDMC::Pos2F position, const std::string& text, unsigned short fontSize, unsigned short thick)
	: updated(false), thick(thick), text(text), fontSize(fontSize)
{
	this->SetPosition(position);
	this->Update();
}

JDMC::LabelSprite::LabelSprite(const std::string& text, unsigned short fontSize, unsigned short thick)
	: updated(false), thick(thick), text(text), fontSize(fontSize)
{
	this->SetPosition({0, 0});
	this->Update();
}

JDMC::LabelSprite::LabelSprite(const char *text, unsigned short fontSize, unsigned short thick)
	: updated(false), thick(thick), text(std::string(text)), fontSize(fontSize)
{
	this->SetPosition({0, 0});
	this->Update();
}

void JDMC::LabelSprite::Render(
	const JDMC::Color Color,
	const JDMC::Color OutColor,
	const bool Cycle)
{
	if (!updated) this->updateFont();

	short x_adder = 0, y_adder = 0;
	for (short i = 0; i < this->Sprite.SpriteBody.size() && y_adder < this->Sprite.Height; i++)
	{
		auto str = this->Sprite.SpriteBody[i];
		if (str == JDMC::Pixel::NEWLINE)
		{
			x_adder = 0;
			y_adder++;
			continue;
		}

		if (x_adder >= this->Sprite.Width)
			continue;

		if (str == JDMC::Pixel::BLANK)
		{
			if (OutColor != JDMC::Color::DEFAULT)
				Drawer::DrawBaseOnCycle({this->Position.X + x_adder, this->Position.Y + y_adder},
					Pixel::PIXEL_SOLID, OutColor, true, Cycle);
		}
		else
			Drawer::DrawBaseOnCycle({this->Position.X + x_adder, this->Position.Y + y_adder}, Pixel::PIXEL_SOLID, Color, true, Cycle);

		x_adder++;
	}
}

void JDMC::LabelSprite::SetText(const std::string &text)
{
	this->text = text;
	this->updated = false;
}

void JDMC::LabelSprite::SetThick(const unsigned short thick)
{
	this->thick = thick;
	this->updated = false;
}

void JDMC::LabelSprite::SetFontSize(unsigned short fontSize)
{
	this->fontSize = fontSize;
	this->updated = false;
}

void JDMC::LabelSprite::updateFont()
{
	short width = -1;
	std::wstring spriteBody;
	// for 
	for (int row = 0; row < 5; row++)
	{
		std::wstring line(this->thick, L' '); // Prepare the line
		for (char c : text) 
		{
			if (JDMC::CharBitmaps::charBitmaps.find(c) != JDMC::CharBitmaps::charBitmaps.end())
			{
				// Create the line based on row, example first line of A {0, 1, 1, 0}
				auto scaledBitmap = JDMC::CharBitmaps::scaleLineBitmap(
					JDMC::CharBitmaps::charBitmaps.at(c), this->fontSize, row);

				// Add to line
				line += scaledBitmap;
				continue;
			}
			// If not recognised, act like it's a blank letter
			for (int i = 0; i < 3 * this->fontSize; ++i)
				line += JDMC::Pixel::BLANK;

			line += L' ';
		}
		line.pop_back();
		line.append(this->thick, L' ');

		if (width < 0) width = line.length();

		// Scale to height, since we already get the line
		for (int i = 0; i < this->fontSize; i++)
		{
			spriteBody += line;
			spriteBody += L'\n';
		}
	}
	this->Sprite.Height = (5 * this->fontSize) + (2 * this->thick);
	this->Sprite.Width = width;

	auto emptyLine = std::wstring(width, L' ');
	std::wstring spaceTopBot;
	for (int i = 0; i < this->thick; i++)
	{
		spaceTopBot += emptyLine;
		spaceTopBot += L'\n';
	}
	this->Sprite.SpriteBody += spaceTopBot;
	this->Sprite.SpriteBody += spriteBody;
	this->Sprite.SpriteBody += spaceTopBot;
	this->updated = true;
}
