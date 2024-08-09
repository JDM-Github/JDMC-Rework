#pragma once
#include "JDMC_struct.hpp"
#include "JDMC_enum.hpp"
#include <string>
#include <cmath>

namespace JDMC
{
	class Window;
	class Drawer
	{
	private:
		static Window *mWindow;

	public:
		static void DrawBaseOnCycle(
			const JDMC::Pos2F Position,
			const short Character = JDMC::Pixel::PIXEL_SOLID,
			const short Color     = (JDMC::Color::FG_WHITE | JDMC::Color::BG_BLACK),
			const bool  Alpha     = false,
			const bool  Cycle     = false);

		static void Draw(
			const JDMC::Pos2F Position,
			const short Character = JDMC::Pixel::PIXEL_SOLID,
			const short Color     = (JDMC::Color::FG_WHITE | JDMC::Color::BG_BLACK),
			const bool  Alpha     = false);

		static void DrawCycle(
			const JDMC::Pos2F Position,
			const short Character = JDMC::Pixel::PIXEL_SOLID,
			const short Color     = (JDMC::Color::FG_WHITE | JDMC::Color::BG_BLACK),
			const bool  Alpha     = false);

		static void DrawString( 
			const JDMC::Pos2F Position,
			const std::wstring &str,
			const short Color  = (JDMC::Color::FG_WHITE | JDMC::Color::BG_BLACK),
			const bool  Alpha  = false,
			const bool  Cycle  = false);

		static void DrawStringChar(
			const JDMC::Pos2F Position,
			const std::wstring &str,
			const short Character = JDMC::Pixel::PIXEL_SOLID,
			const short Color     = (JDMC::Color::FG_WHITE | JDMC::Color::BG_BLACK),
			const bool  Alpha     = false,
			const bool  Cycle     = false);

		static void DrawCString(
			const JDMC::Pos2F Position,
			const std::wstring &str,
			const bool Alpha  = false,
			const bool Cycle  = false);

		static void DrawCStringChar(
			const JDMC::Pos2F Position,
			const std::wstring &str,
			const short Character = JDMC::Pixel::PIXEL_SOLID,
			const bool  Alpha     = false,
			const bool  Cycle     = false);

		static void DrawHorizontal(
			const JDMC::Pos2F Position,
			const int Width,
			const short Character = JDMC::Pixel::PIXEL_SOLID,
			const short Color     = (JDMC::Color::FG_WHITE | JDMC::Color::BG_BLACK),
			const bool  Alpha     = false,
			const bool  Cycle     = false);

		static void DrawVertical(
			const JDMC::Pos2F Position,
			const int Height,
			const short Character = JDMC::Pixel::PIXEL_SOLID,
			const short Color     = (JDMC::Color::FG_WHITE | JDMC::Color::BG_BLACK),
			const bool  Alpha     = false,
			const bool  Cycle     = false);

		static void DrawLine(
			const JDMC::Pos4F Position,
			const short Character = JDMC::Pixel::PIXEL_SOLID,
			const short Color     = (JDMC::Color::FG_WHITE | JDMC::Color::BG_BLACK),
			const bool  Alpha     = false,
			const bool  Cycle     = false);

		static void DrawTriangle(
			const JDMC::Pos6F Position,
			const short Character = JDMC::Pixel::PIXEL_SOLID,
			const short Color     = (JDMC::Color::FG_WHITE | JDMC::Color::BG_BLACK),
			const bool  Alpha     = false,
			const bool  Cycle     = false);

		static void DrawBox(
			const JDMC::PosSizeF SizePosition,
			const short Character = JDMC::Pixel::PIXEL_SOLID,
			const short Color     = (JDMC::Color::FG_WHITE | JDMC::Color::BG_BLACK),
			const short Radius    = 0,
			const bool  Alpha     = false,
			const bool  Cycle     = false);

		static void DrawBoxHollow(
			const JDMC::PosSizeF PosSize,
			const int   thickness,
			const short Character = JDMC::Pixel::PIXEL_SOLID,
			const short Color     = (JDMC::FG_WHITE | JDMC::BG_BLACK),
			const short Radius    = 0,
			const bool  Alpha     = false,
			const bool  Cycle     = false);

		static void DrawBoxHollowWH(
			const JDMC::PosSizeF PosSize,
			const int   thicknessW,
			const int   thicknessH,
			const short Character = JDMC::Pixel::PIXEL_SOLID,
			const short Color     = (JDMC::FG_WHITE | JDMC::BG_BLACK),
			const bool  Alpha     = false,
			const bool  Cycle     = false);

		static void DrawBoxHollowHV(
			const JDMC::PosSizeF PosSize,
			const int   LEFT,
			const int   RIGHT,
			const int   UP,
			const int   DOWN, 
			const short Character = JDMC::Pixel::PIXEL_SOLID,
			const short Color     = (JDMC::FG_WHITE | JDMC::BG_BLACK),
			const bool  Alpha     = false,
			const bool  Cycle     = false);

		static void DrawCircle(
			const JDMC::Pos2F Position,
			const int   radius,
			const short Character = JDMC::Pixel::PIXEL_SOLID,
			const short Color     = (JDMC::FG_WHITE | JDMC::BG_BLACK),
			const bool  Alpha     = false,
			const bool  Cycle     = false);

		static void DrawHallowCircle(
			const JDMC::Pos2F Position,
			const int   radius,
			const int   Thickness,
			const short Character = JDMC::Pixel::PIXEL_SOLID,
			const short Color     = (JDMC::FG_WHITE | JDMC::BG_BLACK),
			const bool  Alpha     = false,
			const bool  Cycle     = false);

		static void DrawColoredHallowCircle(
			const JDMC::Pos2F Position,
			const int   radius,
			const int   Thickness,
			const short Character = JDMC::Pixel::PIXEL_SOLID,
			const short OutColor  =  (JDMC::FG_WHITE | JDMC::BG_BLACK),
			const short Color     = (JDMC::FG_GRAY | JDMC::BG_BLACK),
			const bool  Alpha     = false,
			const bool  Cycle     = false);
	private:
		friend class Window;
	};
}
