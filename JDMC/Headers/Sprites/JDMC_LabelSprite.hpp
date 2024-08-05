#pragma once
#include "JDMC_enum.hpp"
#include "JDMC_struct.hpp"
#include "Sprites/JDMC_EntitySprite.hpp"

namespace JDMC
{
	class LabelSprite : public EntitySprite
	{
	public:
		LabelSprite(JDMC::Pos2F position, const std::string &text, short fontSize);
		LabelSprite(JDMC::Pos2F position, const std::string &text);
		LabelSprite(const std::string& text, short fontSize);
		LabelSprite(const std::string &text);
		LabelSprite(const char *text);

		void Render(const JDMC::Color Color = Color::FG_WHITE, const bool Alpha = false, const bool Cycle = false);

		void SetText(const std::string &text);
		void SetFontSize(short fontSize);

		std::string GetText() const { return this->text; }
		short GetFontSize() const { return this->fontSize; }

	private:
		void updateFont();

	private:
		void SetName(const std::string  &spriteName) override {}
		void SetBody(const std::wstring &spriteBody) override {}
		std::string  GetName    () const override { return this->Sprite.SpriteName; }
		void LoadSprite(const JDMC::Sprite &sprite) override {}
		void LoadSprite(const std::string  &file  ) override {}

	private:
		short fontSize;
		std::string text;
	};
}
