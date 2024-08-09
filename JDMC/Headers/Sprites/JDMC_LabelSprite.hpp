#pragma once
#include "JDMC_enum.hpp"
#include "JDMC_struct.hpp"
#include "Sprites/JDMC_EntitySprite.hpp"

namespace JDMC
{
	class LabelSprite : public EntitySprite
	{
	public:
		LabelSprite(JDMC::Pos2F position, const std::string &text, unsigned short fontSize = 1, unsigned short thick = 1);
		LabelSprite(const std::string& text, unsigned short fontSize = 1, unsigned short thick = 1);
		LabelSprite(const char *text, unsigned short fontSize = 1, unsigned short thick = 1);
		inline void Update() { this->updateFont(); }

		void Render(
			const JDMC::Color Color = Color::FG_WHITE,
			const JDMC::Color OutColor = Color::DEFAULT,
			const bool Cycle = false);

		void SetText    (const std::string &text);
		void SetThick   (unsigned short thick);
		void SetFontSize(unsigned short fontSize);

		std::string GetText    () const { return this->text; }
		short       GetThick   () const { return this->thick; }
		short       GetFontSize() const { return this->fontSize; }

	private:
		void updateFont();

	private:
		void SetName(const std::string  &spriteName) override {}
		void SetBody(const std::wstring &spriteBody) override {}
		std::string  GetName    () const override { return this->Sprite.SpriteName; }
		void LoadSprite(const JDMC::Sprite &sprite) override {}
		void LoadSprite(const std::string  &file  ) override {}

	private:
		bool updated;
		unsigned short thick, fontSize;
		std::string text;
	};
}
