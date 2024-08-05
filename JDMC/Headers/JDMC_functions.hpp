#pragma once
#include "JDMC_enum.hpp"
#include "JDMC_struct.hpp"

namespace JDMC
{
	namespace Function
	{
		const JDMC::Color getColor(short Index);
		const JDMC::Sprite LoadSprite(const std::string &file);
	}
}

