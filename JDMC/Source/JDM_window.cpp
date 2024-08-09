#include "JDMC_keyboard.hpp"
#include "JDMC_window.hpp"
#include "JDMC_config.hpp"
#include "JDMC_drawer.hpp"
#include <cassert>

JDMC::Window::Window(
	const char *Title,
	const short Width,
	const short Height,
	const short fontWidth,
	const short fontHeight
) :
	WTitle      (Title),
	ScreenWidth (Width),
	ScreenHeight(Height), 
	FontWidth   (fontWidth),
	FontHeight  (fontHeight)
{
	auto console = GetConsoleWindow();
	this->originalConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	this->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	this->hConsoleI = GetStdHandle(STD_INPUT_HANDLE);
	this->bufferInfo.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	assert(SetConsoleActiveScreenBuffer(this->hConsole));

	SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	MoveWindow(console, 0, 0, 0, 0, true);
	GetConsoleMode(this->hConsoleI, &this->PrevMode);
	SetConsoleMode(this->hConsoleI, ENABLE_EXTENDED_FLAGS | (this->PrevMode & ~ENABLE_QUICK_EDIT_MODE));
	SetConsoleWindowSize(this->hConsole, ScreenWidth, ScreenHeight, fontWidth, fontHeight);

	ShowScrollBar(console, SB_VERT, false);
	GetConsoleCursorInfo(this->hConsole, &this->CursorInfo);
	this->CursorInfo.dwSize = 100;
	this->CursorInfo.bVisible = false;
	SetConsoleCursorInfo(this->hConsole, &this->CursorInfo);
	GetConsoleScreenBufferInfoEx(this->hConsole, &bufferInfo);

	SetConsoleWindowSize(this->hConsole, ScreenWidth, ScreenHeight, fontWidth, fontHeight);
	this->Screen = new CHAR_INFO[ScreenWidth * ScreenHeight];

	ShowCursor(FALSE);

	JDMC::Drawer::mWindow = this;
}

JDMC::Window::~Window()
{
	this->Clear();
	WriteConsoleOutputW(this->hConsole, this->Screen, {this->GetWidth(), this->GetHeight()}, {0, 0}, &this->screenBufferCorners);
	SetConsoleWindowSize(this->originalConsole, 120, 50, 8, 10);
	SetConsoleActiveScreenBuffer(this->originalConsole);
	ShowScrollBar(GetConsoleWindow(), SB_VERT, true);
	SetConsoleCursorPosition(this->originalConsole, {0, 0});
	SetConsoleMode(this->hConsoleI, this->PrevMode);

	this->CursorInfo.dwSize   = 100;
	this->CursorInfo.bVisible = true;
	SetConsoleCursorInfo(this->hConsole, &this->CursorInfo);
	SetConsoleTextAttribute(this->originalConsole, JDMC::FG_WHITE | JDMC::BG_BLACK);
	delete [] this->Screen;
}

// void JDMC::Window::hideMouse()
// {
//    static bool bCursorVisible = TRUE;
//             if( ((HWND)wParam)!=hwD3DArea && !bCursorVisible )
//             {
//                 ShowCursor((bCursorVisible=TRUE));
//             }
//             else if( ((HWND)wParam)==hwD3DArea && bCursorVisible )
//             {
//                 ShowCursor((bCursorVisible=FALSE));
//                 return TRUE;
//             }
// }

void JDMC::Window::SetConsoleWindowSize(
	HANDLE console,
	const short Width,
	const short Height,
	const short FontWidth,
	const short FontHeight)
{
	this->screenBufferCorners = {0, 0, 1, 1};
	SetConsoleWindowInfo(console, true, &this->screenBufferCorners);
	assert(SetConsoleScreenBufferSize(console, {Width, Height}));
	assert(SetConsoleActiveScreenBuffer(console));

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = FontWidth;
	cfi.dwFontSize.Y = FontHeight;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Lucida Console");
	assert(SetCurrentConsoleFontEx(console, false, &cfi));
	this->screenBufferCorners = {0, 0, static_cast<short>(Width - 1), static_cast<short>(Height - 1)};
	assert(SetConsoleWindowInfo(console, true, &this->screenBufferCorners));
}

void JDMC::Window::Start()
{
	assert(this->onUserCreate());
	this->Running = true;
	this->timePoint1 = std::chrono::system_clock::now();
	this->timePoint2 = std::chrono::system_clock::now();
	while (this->Running)
		this->Running = this->gameLoop();

	JDMC::Drawer::mWindow = nullptr;
}

bool JDMC::Window::gameLoop()
{
	this->timePoint2 = std::chrono::system_clock::now();
	std::chrono::duration<float> elapseTime = this->timePoint2 - this->timePoint1;
	this->timePoint1 = this->timePoint2;
	this->ElapseTime = elapseTime.count();

	if (this->onUserUpdate())
	{
		GetCursorPos(&this->MousePos);
		ScreenToClient(GetConsoleWindow(), &this->MousePos);

		this->ExactMousePos.X = this->MousePos.x / this->FontWidth;
		this->ExactMousePos.Y = this->MousePos.y / this->FontHeight;
		if (this->isReleased(JDMC::Keys::ESC))
			return false;

		wchar_t updater[0xff];
		swprintf(
			updater, 0xff,
			L"%s - FPS: %4.2f", this->WTitle.c_str(),
			1.f / this->ElapseTime
		);
		SetConsoleTitleW(updater);

		WriteConsoleOutputW(
			this->hConsole,
			this->Screen,
			{this->GetWidth(), this->GetHeight()},
			{0, 0},
			&this->screenBufferCorners
		);

		this->keyboard.resetUpdateCycle();
		return true;
	}
	return false;
}

void JDMC::Window::Clear(const short Character, const short Color)
{
	for (short i = 0; i < this->GetHeight(); i++)
		for (short j = 0; j < this->GetWidth(); j++)
		{
			this->Screen[i * this->GetWidth() + j].Char.UnicodeChar = Character;
			this->Screen[i * this->GetWidth() + j].Attributes = Color;
		}
}
bool JDMC::Window::isHeld    (JDMC::Keys key) { return this->keyboard.getState(key).isHeld;     }
bool JDMC::Window::isPressed (JDMC::Keys key) { return this->keyboard.getState(key).isPressed;  }
bool JDMC::Window::isReleased(JDMC::Keys key) { return this->keyboard.getState(key).isReleased; }
