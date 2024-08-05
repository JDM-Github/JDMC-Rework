#include "Sprites/JDMC_EntitySprite.hpp"
#include "JDMC_drawer.hpp"
#include "JDMC_functions.hpp"

JDMC::EntitySprite::EntitySprite(JDMC::Pos2F position, const JDMC::Sprite &sprite)
{
	this->SetPosition(position);
	this->LoadSprite(sprite);
}

JDMC::EntitySprite::EntitySprite(JDMC::Pos2F position, const std::string &sprite)
{
	this->SetPosition(position);
	this->LoadSprite(sprite);
}
JDMC::EntitySprite::EntitySprite(const JDMC::Sprite &sprite)
{
	this->SetPosition({0, 0});
	this->LoadSprite(sprite);
}
JDMC::EntitySprite::EntitySprite(const std::string &file)
{
	this->SetPosition({0, 0});
	this->LoadSprite(file);
}
JDMC::EntitySprite::EntitySprite(const char *file)
{
	this->SetPosition({0, 0});
	this->LoadSprite(std::string(file));
}

JDMC::EntitySprite::EntitySprite()
{
	this->SetPosition({0, 0});

	this->Sprite.SpriteName = "_";
	this->Sprite.SpriteBody = L"";
	this->Sprite.Width = 0;
	this->Sprite.Height = 0;
}

void JDMC::EntitySprite::Render(
	const bool Alpha,
	const bool Cycle)
{
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
		if (x_adder >= this->Sprite.Width
		|| (Alpha && str == JDMC::Pixel::BLANK))
			continue;

		Drawer::DrawBaseOnCycle({this->Position.X + x_adder, this->Position.Y + y_adder},
			JDMC::PIXEL_SOLID, (JDMC::Function::getColor(
				str) | JDMC::BG_BLACK), Cycle);

		x_adder++;
	}
}

void JDMC::EntitySprite::SetPosition(JDMC::Pos2F Position)
{
	this->Position = Position;
}

void JDMC::EntitySprite::SetX(float x)
{
	this->Position.X = x;
}

void JDMC::EntitySprite::SetY(float y)
{
	this->Position.Y = y;
}

void JDMC::EntitySprite::SetWidth (short Width)
{
	this->Sprite.Width = Width;
}

void JDMC::EntitySprite::SetHeight(short Height)
{
	this->Sprite.Height = Height;
}

void JDMC::EntitySprite::SetName  (const std::string &spriteName)
{
	this->Sprite.SpriteName = spriteName;
}

void JDMC::EntitySprite::SetBody(const std::wstring &spriteBody)
{
	this->Sprite.SpriteBody = spriteBody;
}

void JDMC::EntitySprite::LoadSprite(const JDMC::Sprite &sprite)
{
	this->Sprite = sprite;
}

void JDMC::EntitySprite::LoadSprite(const std::string &file)
{
	this->Sprite = JDMC::Function::LoadSprite(file);
}
