#pragma once
#include <unordered_map>
#include <vector>
#include <string>

namespace JDMC
{
	class CharBitmaps
	{
	public:
		static const std::unordered_map<char, std::vector<std::vector<bool>>> charBitmaps;
		static std::vector<std::wstring> scaleBitmap(const std::vector<std::vector<bool>>& bitmap, int scale);
		static std::wstring scaleLineBitmap(const std::vector<std::vector<bool>>& bitmap, int scale, int line);
	};
}
