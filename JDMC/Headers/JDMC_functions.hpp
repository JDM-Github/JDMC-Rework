#pragma once
#include "JDMC_enum.hpp"
#include "JDMC_struct.hpp"

namespace JDMC
{
	namespace Function
	{
		const JDMC::Color getColor(short Index);
		const JDMC::Sprite LoadSprite(const std::string &file);

		void SetRandomSeed();

		constexpr int GetIndex(int x, int y, int Pitch) { return x + (y * Pitch); }
		constexpr bool collidePoint(const JDMC::PosSizeFD position, float x1, float y1)
		{
			return (position.X <= x1 && x1 < position.X + position.Width && position.Y <= y1 && y1 < position.Y + position.Height);
		}
		constexpr bool collidePoint(const JDMC::PosSizeFD position, const JDMC::Pos2D MousePosition)
		{
			return (position.X <= MousePosition.X && MousePosition.X < position.X + position.Width
				 && position.Y <= MousePosition.Y && MousePosition.Y < position.Y + position.Height);
		}
		constexpr bool collide_box(
			const JDMC::PosSizeFD firstPosition,
			const JDMC::PosSizeFD secondPosition)
		{
			if (firstPosition.X + firstPosition.Width  < secondPosition.X     ) return false;
			if (firstPosition.X > secondPosition.X     + secondPosition.Width ) return false;
			if (firstPosition.Y + firstPosition.Height < secondPosition.Y     ) return false;
			if (firstPosition.Y > secondPosition.Y     + secondPosition.Height) return false;
			return true;
		}

		const int Randint(int first, int second);
		const float Randfloat(int first, int second);

	}
}

