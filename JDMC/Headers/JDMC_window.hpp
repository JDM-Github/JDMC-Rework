#pragma once
#include <Windows.h>
#include <string>
#include <chrono>
#include "JDMC_struct.hpp"
#include "JDMC_enum.hpp"

namespace JDMC
{
	class Drawer;
	class Keyboard;
	class Window
	{
	public:
		void Start();

	protected:
		Window(
			const char *Title,
			const short Width,
			const short Height,
			const short fontWidth = 5,
			const short fontHeight = 5
		);
		~Window();

		void Clear(
			const short Character = JDMC::Pixel::BLANK,
			const short Color = (JDMC::FG_BLACK | JDMC::BG_BLACK)
		);
		bool isHeld    (JDMC::Keys key);
		bool isPressed (JDMC::Keys key);
		bool isReleased(JDMC::Keys key);

		virtual bool onUserUpdate() = 0;
		virtual bool onUserCreate() = 0;
		
		constexpr int GetMouseX() const { return this->MousePos.x / this->FontWidth;  }
		constexpr int GetMouseY() const { return this->MousePos.y / this->FontHeight; }

		constexpr const short GetWidth()  const { return this->ScreenWidth;  }
		constexpr const short GetHeight() const { return this->ScreenHeight; }
		constexpr int GetMouseIndex(int BlockWidth, int Pitch ) const
		{
			return (this->GetMouseY() / BlockWidth) * Pitch + (this->GetMouseX() / BlockWidth);
		}

	protected:
		JDMC::Keyboard keyboard;
		POINT MousePos;
		Pos2D ExactMousePos;
	
		CHAR_INFO *Screen;
		float ElapseTime;

	private:
		void SetConsoleWindowSize(
			HANDLE console,
			const short Width,
			const short Height,
			const short FontWidth,
			const short FontHeight
		);
		bool gameLoop();

	private:
		const short       ScreenWidth, ScreenHeight;
		const short       FontWidth, FontHeight;
		const std::string WTitle;
		bool              Running;

		HANDLE                       originalConsole;
		HANDLE                       hConsole;
		HANDLE                       hConsoleI;
		SMALL_RECT                   screenBufferCorners;
		CONSOLE_SCREEN_BUFFER_INFOEX bufferInfo;
		DWORD                        PrevMode;
		CONSOLE_CURSOR_INFO          CursorInfo;

		using Timepoint = std::chrono::_V2::system_clock::time_point;
		Timepoint timePoint1;
		Timepoint timePoint2;

	private:
		friend class Drawer;
	};
}
