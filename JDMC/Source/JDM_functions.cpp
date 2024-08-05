#include "JDMC_functions.hpp"
#include "Nlohmann_json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using json = nlohmann::json;

namespace JDMC
{
	namespace Function
	{
		const JDMC::Color getColor(short Index)
		{
			switch (Index)
			{
				case L'0': return JDMC::FG_BLACK;
				case L'1': return JDMC::FG_BLUE;
				case L'2': return JDMC::FG_GREEN;
				case L'3': return JDMC::FG_CYAN;
				case L'4': return JDMC::FG_RED;
				case L'5': return JDMC::FG_MAGENTA;
				case L'6': return JDMC::FG_YELLOW;
				case L'7': return JDMC::FG_GRAY;
				case L'8': return JDMC::FG_DARK_GRAY;
				case L'9': return JDMC::FG_DARK_BLUE;
				case L'A': return JDMC::FG_DARK_GREEN;
				case L'B': return JDMC::FG_DARK_CYAN;
				case L'C': return JDMC::FG_DARK_RED;
				case L'D': return JDMC::FG_SKIN;
				case L'E': return JDMC::FG_DARK_SKIN;
				default  : return JDMC::FG_WHITE;
			}
		}

		const JDMC::Sprite LoadSprite(const std::string &file)
		{
			std::ifstream ifs(file);
			if (!ifs.is_open())
				throw std::runtime_error("Could not open file");

			std::string jsonStr((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
			json jsonData = json::parse(jsonStr);

			JDMC::Sprite sprite;
			sprite.SpriteName = jsonData.value("SpriteName", "DefaultName");
			sprite.Width      = jsonData.value("Width" , 0);
			sprite.Height     = jsonData.value("Height", 0);

			std::wstring SpriteBody;
			for (const auto& line : jsonData.value("SpriteBody", std::vector<std::string>{}))
			{
				std::wstring wline(line.begin(), line.end());
				SpriteBody += wline + L'\n';
			}
			sprite.SpriteBody = SpriteBody;
		
			return sprite;
		}
	}

}
