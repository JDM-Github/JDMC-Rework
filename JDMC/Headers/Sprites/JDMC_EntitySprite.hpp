#pragma once
#include <type_traits>
#include "JDMC_enum.hpp"
#include "JDMC_struct.hpp"

namespace JDMC
{
	class EntitySprite
	{
	public:
		EntitySprite(JDMC::Pos2F position, const JDMC::Sprite &sprite);
		EntitySprite(JDMC::Pos2F position, const std::string &file);
		EntitySprite(const JDMC::Sprite &sprite);
		EntitySprite(const std::string &file);
		EntitySprite(const char *file);
		EntitySprite();
		virtual ~EntitySprite() {}

		virtual void Render(const bool Alpha = false, const bool Cycle = false);
		
		constexpr bool CollidePoint(JDMC::Pos2F position)
		{
			return (this->Position.X <= position.X
				 && position.X < this->Position.X + this->Sprite.Width
				 && this->Position.Y <= position.Y
				 && position.Y < this->Position.Y + this->Sprite.Height);
		}
		template <typename T, typename U>
		typename std::enable_if<std::is_arithmetic<T>::value && std::is_arithmetic<U>::value, bool>::type
		CollidePoint(T x, U y)
		{
			return (this->Position.X <= x
				 && x < this->Position.X + this->Sprite.Width
				 && this->Position.Y <= y
				 && y < this->Position.Y + this->Sprite.Height);
		}
	
		virtual void SetPosition(JDMC::Pos2F Position);
		virtual void SetX       (float x);
		virtual void SetY       (float y);
		virtual void SetWidth   (short Width);
		virtual void SetHeight  (short Height);
		virtual void SetName    (const std::string &spriteName);
		virtual void SetBody    (const std::wstring &spriteBody);

		virtual JDMC::Pos2F  GetPosition() const { return this->Position; }
		virtual float        GetX       () const { return this->Position.X; }
		virtual float        GetY       () const { return this->Position.Y; }
		virtual float        GetWidth   () const { return this->Sprite.Width; }
		virtual float        GetHeight  () const { return this->Sprite.Height; }
		virtual std::string  GetName    () const { return this->Sprite.SpriteName; }
		virtual std::wstring GetBody    () const { return this->Sprite.SpriteBody; }
		virtual JDMC::Sprite GetSprite  () const { return this->Sprite; }

		virtual void LoadSprite(const JDMC::Sprite &sprite);
		virtual void LoadSprite(const std::string &file);

	protected:
		JDMC::Sprite Sprite;
		JDMC::Pos2F Position;
	};
}
