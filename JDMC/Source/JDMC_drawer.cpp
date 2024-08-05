#include "JDMC_drawer.hpp"
#include "JDMC_keyboard.hpp"
#include "JDMC_window.hpp"
#include "JDMC_functions.hpp"

JDMC::Window* JDMC::Drawer::mWindow = nullptr;

void JDMC::Drawer::DrawBaseOnCycle(
	const JDMC::Pos2F Position,
	const short Character,
	const short Color,
	const bool  Alpha,
	const bool  Cycle)
{
	if (Cycle) Drawer::DrawCycle(Position, Character, Color, Alpha);
	else Drawer::Draw(Position, Character, Color, Alpha);
}

void JDMC::Drawer::Draw(
	const JDMC::Pos2F Position,
	const short Character,
	const short Color,
	const bool  Alpha)
{
	if (static_cast<int>(Position.X) >= 0 && static_cast<int>(Position.X) < Drawer::mWindow->GetWidth()
	 && static_cast<int>(Position.Y) >= 0 && static_cast<int>(Position.Y) < Drawer::mWindow->GetHeight())
	{
		if (Alpha && Character == JDMC::BLANK) return;
		Drawer::mWindow->Screen[Drawer::mWindow->GetWidth() * static_cast<int>(Position.Y) + static_cast<int>(Position.X)].Char.UnicodeChar = Character;
		Drawer::mWindow->Screen[Drawer::mWindow->GetWidth() * static_cast<int>(Position.Y) + static_cast<int>(Position.X)].Attributes       = Color;
	}
}

void JDMC::Drawer::DrawCycle(
	const JDMC::Pos2F Position,
	const short Character,
	const short Color,
	const bool  Alpha)
{
	if (Alpha && Character == JDMC::Pixel::BLANK) return;
	int posX = static_cast<int>(Position.X);
	int posY = static_cast<int>(Position.Y);

	if (posX < 0) posX = Drawer::mWindow->GetWidth()  - (std::abs(posX) % Drawer::mWindow->GetWidth());
	if (posY < 0) posY = Drawer::mWindow->GetHeight() - (std::abs(posY) % Drawer::mWindow->GetHeight());
	Drawer::mWindow->Screen[Drawer::mWindow->GetWidth() * (posY % Drawer::mWindow->GetHeight()) + (posX % Drawer::mWindow->GetWidth())].Char.UnicodeChar = Character;
	Drawer::mWindow->Screen[Drawer::mWindow->GetWidth() * (posY % Drawer::mWindow->GetHeight()) + (posX % Drawer::mWindow->GetWidth())].Attributes = Color;
}

void JDMC::Drawer::DrawString(
	const JDMC::Pos2F Position,
	const std::wstring &str,
	const short Color,
	const bool  Alpha,
	const bool  Cycle)
{
	short x_adder = 0, y_adder = 0;
	for (short i = 0; i < str.size(); i++)
	{
		if (str[i] == JDMC::Pixel::NEWLINE)
		{
			x_adder = 0;
			y_adder++;
			continue;
		}
		if (Alpha && str[i] == JDMC::Pixel::BLANK) continue;
		Drawer::DrawBaseOnCycle({Position.X + x_adder, Position.Y + y_adder}, str[i], Color, Alpha, Cycle);
		x_adder++;
	}
}


void JDMC::Drawer::DrawStringChar(
	const JDMC::Pos2F Position,
	const std::wstring &str,
	const short Character,
	const short Color,
	const bool  Alpha,
	const bool  Cycle)
{
	short x_adder = 0, y_adder = 0;
	for (short i = 0; i < str.size(); i++)
	{
		if (str[i] == JDMC::Pixel::NEWLINE)
		{
			x_adder = 0;
			y_adder++;
			continue;
		}
		if (Alpha && str[i] == JDMC::Pixel::BLANK) continue;
		Drawer::DrawBaseOnCycle({Position.X + x_adder, Position.Y + y_adder}, Character, Color, Cycle);
		x_adder++;
	}
}

void JDMC::Drawer::DrawCString(
	const JDMC::Pos2F Position,
	const std::wstring &str,
	const bool Alpha,
	const bool Cycle)
{
	short x_adder = 0, y_adder = 0;
	for (short i = 0; i < str.size(); i++)
	{
		if (str[i] == JDMC::Pixel::NEWLINE)
		{
			x_adder = 0;
			y_adder++;
			continue;
		}
		if (Alpha && str[i] == JDMC::Pixel::BLANK) continue;
		Drawer::DrawBaseOnCycle({Position.X + x_adder, Position.Y + y_adder},
			JDMC::PIXEL_SOLID, (JDMC::Function::getColor(str[i]) | JDMC::BG_BLACK), Cycle);
		x_adder++;
	}
}

void JDMC::Drawer::DrawCStringChar(
	const JDMC::Pos2F Position,
	const std::wstring &str,
	const short Character,
	const bool  Alpha,
	const bool  Cycle)
{
	short x_adder = 0, y_adder = 0;
	for (short i = 0; i < str.size(); i++)
	{
		if (str[i] == JDMC::Pixel::NEWLINE)
		{
			x_adder = 0;
			y_adder++;
			continue;
		}
		if (Alpha && str[i] == JDMC::Pixel::BLANK) continue;
		Drawer::DrawBaseOnCycle({Position.X + x_adder, Position.Y + y_adder},
			Character, (JDMC::Function::getColor(str[i]) | JDMC::BG_BLACK), Cycle);
		x_adder++;
	}
}

void JDMC::Drawer::DrawHorizontal(
	const JDMC::Pos2F Position,
	const int   Width,
	const short Character,
	const short color,
	const bool  Alpha,
	const bool  Cycle)
{
	for (int i = static_cast<int>(Position.X); i < Width; i++)
	{
		Drawer::DrawBaseOnCycle({Position.X + i, Position.Y}, Character, color, Alpha, Cycle);
	}
}


void JDMC::Drawer::DrawVertical(
	const JDMC::Pos2F Position,
	const int   Height,
	const short Character,
	const short color,
	const bool  Alpha,
	const bool  Cycle)
{
	for (int i = static_cast<int>(Position.Y); i < Height; i++)
	{
		Drawer::DrawBaseOnCycle({Position.X, Position.Y + i}, Character, color, Alpha, Cycle);
	}
}

void JDMC::Drawer::DrawLine(
	const JDMC::Pos4F Position,
	const short Character,
	const short color,
	const bool  Alpha,
	const bool  Cycle)
{
	float xCurrent = Position.W;
	float yCurrent = Position.X;
	float xDistant = (Position.W > Position.Y) ? (Position.W - Position.Y) : (Position.Y - Position.W);
	float yDistant = (Position.X > Position.Z) ? (Position.X - Position.Z) : (Position.Z - Position.X);
	float distance = std::sqrt(xDistant * xDistant + yDistant * yDistant);

	int numberSamp = std::max(xDistant, yDistant);
	float samplePX = xDistant / numberSamp;
	float samplePY = yDistant / numberSamp;
	for (int i = 0; i < numberSamp; i++)
	{
		Drawer::DrawBaseOnCycle({xCurrent, yCurrent}, Character, color, Alpha, Cycle);
		xCurrent += (Position.W > Position.Y) ? -samplePX : samplePX;
		yCurrent += (Position.X > Position.Z) ? -samplePY : samplePY;
	}
}

void JDMC::Drawer::DrawTriangle(
	const JDMC::Pos6F Position,
	const short Character,
	const short color,
	const bool  Alpha,
	const bool  Cycle)
{
	Drawer::DrawLine({Position.U, Position.U, Position.W, Position.X}, Character, color, Alpha, Cycle);
	Drawer::DrawLine({Position.W, Position.X, Position.Y, Position.Z}, Character, color, Alpha, Cycle);
	Drawer::DrawLine({Position.Y, Position.Z, Position.U, Position.U}, Character, color, Alpha, Cycle);
}

void JDMC::Drawer::DrawBox(
	const JDMC::PosSizeF SizePosition,
	const short Character,
	const short color,
	const bool  Alpha,
	const bool  Cycle)
{
	for (int i = 0; i < static_cast<short>(SizePosition.Height); i++)
	{
		for (int j = 0; j < static_cast<short>(SizePosition.Width); j++)
		{
			Drawer::DrawBaseOnCycle({SizePosition.X + j, SizePosition.Y + i}, Character, color, Alpha, Cycle);
		}
	}
}

void JDMC::Drawer::DrawBoxHollow(
	const JDMC::PosSizeF PosSize,
	const int   thickness,
	const short Character,
	const short Color,
	const bool  Alpha,
	const bool  Cycle)
{
	short Width  = static_cast<short>(PosSize.Width);
	short Height = static_cast<short>(PosSize.Height);

	for (int px = PosSize.X; px < PosSize.X + Width; px++)
		for (int py = PosSize.Y; py < PosSize.Y + thickness; py++)
			Drawer::DrawBaseOnCycle({static_cast<float>(px), static_cast<float>(py)}, Character, Color, Alpha, Cycle);

	for (int px = PosSize.X; px < PosSize.X + Width; px++)
		for (int py = PosSize.Y + Height - 1; py > PosSize.Y + Height - 1 - thickness; py--)
			Drawer::DrawBaseOnCycle({static_cast<float>(px), static_cast<float>(py)}, Character, Color, Alpha, Cycle);

	for (int py = PosSize.Y; py < PosSize.Y + Height; py++)
		for (int px = PosSize.X; px < PosSize.X + thickness; px++)
			Drawer::DrawBaseOnCycle({static_cast<float>(px), static_cast<float>(py)}, Character, Color, Alpha, Cycle);

	for (int py = PosSize.Y; py < PosSize.Y + Height; py++)
		for (int px = PosSize.X + Width - 1; px > PosSize.X + Width - 1 - thickness; px--)
			Drawer::DrawBaseOnCycle({static_cast<float>(px), static_cast<float>(py)}, Character, Color, Alpha, Cycle);
}

void JDMC::Drawer::DrawBoxHollowWH(
	const JDMC::PosSizeF PosSize,
	const int   thicknessW,
	const int   thicknessH,
	const short Character,
	const short Color,
	const bool  Alpha,
	const bool  Cycle)
{
	short Width  = static_cast<short>(PosSize.Width);
	short Height = static_cast<short>(PosSize.Height);

	for (int px = PosSize.X; px < PosSize.X + Width; px++)
		for (int py = PosSize.Y; py < PosSize.Y + thicknessH; py++)
			Drawer::DrawBaseOnCycle({static_cast<float>(px), static_cast<float>(py)}, Character, Color, Alpha, Cycle);

	for (int px = PosSize.X; px < PosSize.X + Width; px++)
		for (int py = PosSize.Y + Height - 1; py > PosSize.Y + Height - 1 - thicknessH; py--)
			Drawer::DrawBaseOnCycle({static_cast<float>(px), static_cast<float>(py)}, Character, Color, Alpha, Cycle);

	for (int py = PosSize.Y; py < PosSize.Y + Height; py++)
		for (int px = PosSize.X; px < PosSize.X + thicknessW; px++)
			Drawer::DrawBaseOnCycle({static_cast<float>(px), static_cast<float>(py)}, Character, Color, Alpha, Cycle);

	for (int py = PosSize.Y; py < PosSize.Y + Height; py++)
		for (int px = PosSize.X + Width - 1; px > PosSize.X + Width - 1 - thicknessW; px--)
			Drawer::DrawBaseOnCycle({static_cast<float>(px), static_cast<float>(py)}, Character, Color, Alpha, Cycle);
}

void JDMC::Drawer::DrawBoxHollowHV(
	const JDMC::PosSizeF PosSize,
	const int   LEFT,
	const int   RIGHT,
	const int   UP,
	const int   DOWN, 
	const short Character,
	const short Color,
	const bool  Alpha,
	const bool  Cycle)
{
	short Width  = static_cast<short>(PosSize.Width);
	short Height = static_cast<short>(PosSize.Height);

	for (int px = PosSize.X; px < PosSize.X + Width; px++)
		for (int py = PosSize.Y; py < PosSize.Y + UP; py++)
			Drawer::DrawBaseOnCycle({static_cast<float>(px), static_cast<float>(py)}, Character, Color, Alpha, Cycle);

	for (int px = PosSize.X; px < PosSize.X + Width; px++)
		for (int py = PosSize.Y + Height - 1; py > PosSize.Y + Height - 1 - DOWN; py--)
			Drawer::DrawBaseOnCycle({static_cast<float>(px), static_cast<float>(py)}, Character, Color, Alpha, Cycle);

	for (int py = PosSize.Y; py < PosSize.Y + Height; py++)
		for (int px = PosSize.X; px < PosSize.X + RIGHT; px++)
			Drawer::DrawBaseOnCycle({static_cast<float>(px), static_cast<float>(py)}, Character, Color, Alpha, Cycle);

	for (int py = PosSize.Y; py < PosSize.Y + Height; py++)
		for (int px = PosSize.X + Width - 1; px > PosSize.X + Width - 1 - LEFT; px--)
			Drawer::DrawBaseOnCycle({static_cast<float>(px), static_cast<float>(py)}, Character, Color, Alpha, Cycle);
}

void JDMC::Drawer::DrawCircle(
	const JDMC::Pos2F Position,
	const int   radius,
	const short Character,
	const short Color,
	const bool  Alpha,
	const bool  Cycle)
{
	for (int h = 0; h < radius * 2; h++)
	{
		for (int w = 0; w < radius * 2; w++)
		{
			int dx = radius - w;
			int dy = radius - h;
			if (!((dx * dx) + (dy * dy) >= (radius * radius)))
			{
				Drawer::DrawBaseOnCycle({
					Position.X + radius + dx - 1,
					Position.Y + radius + dy - 1},
					Character, Color, Alpha, Cycle);
			}
		}
	}
}

void JDMC::Drawer::DrawHallowCircle(
	const JDMC::Pos2F Position,
	const int   radius,
	const int   Thickness,
	const short Character,
	const short Color,
	const bool  Alpha,
	const bool  Cycle)
{
	for (int h = 0; h < radius * 2; h++)
	{
		for (int w = 0; w < radius * 2; w++)
		{
			int dx = radius - w;
			int dy = radius - h;
			if (!((dx * dx) + (dy * dy) >= (radius * radius)) && !((dx * dx) + (dy * dy) <= ((radius - Thickness) * (radius - Thickness))))
			{
				Drawer::DrawBaseOnCycle({
					Position.X + radius + dx - 1,
					Position.Y + radius + dy - 1},
					Character, Color, Alpha, Cycle);
			}
		}
	}
}

void JDMC::Drawer::DrawColoredHallowCircle(
	const JDMC::Pos2F Position,
	const int   radius,
	const int   Thickness,
	const short Character,
	const short OutColor,
	const short Color,
	const bool  Alpha,
	const bool  Cycle)
{
	for (int h = 0; h < radius * 2; h++)
	{
		for (int w = 0; w < radius * 2; w++)
		{
			int dx = radius - w;
			int dy = radius - h;

			if (!((dx * dx) + (dy * dy) >= (radius * radius)))
				Drawer::DrawBaseOnCycle({Position.X + radius + dx - 1, Position.Y + radius + dy - 1}, Character, Color, Alpha, Cycle);

			if (!((dx * dx) + (dy * dy) >= (radius * radius)) && !((dx * dx) + (dy * dy) <= ((radius - Thickness) * (radius - Thickness))))
				Drawer::DrawBaseOnCycle({Position.X + radius + dx - 1, Position.Y + radius + dy - 1}, Character, OutColor, Alpha, Cycle);

		}
	}
}
