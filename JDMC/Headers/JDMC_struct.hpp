#pragma once
#include <string>

namespace JDMC
{
	struct KeyState
	{
		bool isPressed  = false;
		bool isHeld     = false;
		bool isReleased = false;
	};

	struct Sprite
	{
		std::string SpriteName;
		std::wstring SpriteBody;
		short Width;
		short Height;
	};

	struct Vector2F  { float X, Y; };
	struct Vector3F  { float X, Y, Z; };
	struct Vector2D  { short X, Y; };
	struct Vector3D  { short X, Y, Z; };

	struct Size2D    { short Width, Height; };
	struct Size2F    { float Width, Height; };

	struct Pos2D     { short X, Y; };
	struct Pos4D     { short W, X, Y, Z; };
	struct Pos6D     { short U, V, W, X, Y, Z; };

	struct Pos2F     { float X, Y; };
	struct Pos4F     { float W, X, Y, Z; };
	struct Pos6F     { float U, V, W, X, Y, Z; };

	struct PosSizeD  { short X, Y, Width, Height; };
	struct PosSizeF  { float X, Y, Width, Height; };

	struct PosSizeFD { float X, Y; short Width, Height; };
	struct PosSizeDF { short X, Y; float Width, Height; };
}
