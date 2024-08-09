#include "JDMC.hpp"
#include "Sprites/JDMC_EntitySprite.hpp"
#include "Sprites/JDMC_LabelSprite.hpp"
#include <vector>
#include <stack>

using namespace JDMC;
class ConsoleApplication : public JDMC::Window
{
private:

	enum ToolAvailable {
		TOOL_PEN    = 0x0,
		TOOL_BUCKET = 0x1,
		TOOL_ERASER = 0x2
	};

	// Setup
	short maxRow = 50;
	short maxCol = 50;

	short pixelSize = 1;
	short cameraX = 0.f;
	short cameraY = 0.f;
	float zoomMultiplier = 1;
	bool  drawingStarted = false;

	std::vector<unsigned int> currentMove;
	std::stack<std::vector<unsigned int>> undoStack;
	std::stack<std::vector<unsigned int>> redoStack;

	// Coords
	float blink = 0.3;
	float hideCursor = 3;
	bool showCoords = true;
	Pos2F boxCoords{0, 0};

	ToolAvailable toolUsed = ToolAvailable::TOOL_PEN;
	Color currentPen = Color::FG_BLACK;

	LabelSprite *saveLabel;
	LabelSprite *openLabel;
	std::vector<std::vector<short>> canvas;

	std::wstring toolDesign[7];

private:
	void drawCanvas();
	void drawPixel(short x, short y);
	void drawPixel(short x, short y, Color penColor);

	void endDrawing();
	void reDrawPixel(const std::vector<unsigned int> &lastMove);
	void undo();
	void redo();
	void checkChange(short mouseX, short mouseY);

	void handleKeys();
	void updateCamera();
	void cappedCamera();
	void cappedCoords();


	void FloodFill(int x, int y, short targetColor);
	void handleDraw(short x, short y);	

public:
	ConsoleApplication();
	~ConsoleApplication();

	bool onUserCreate();
	bool onUserUpdate();
};
