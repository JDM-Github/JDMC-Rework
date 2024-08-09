#include "ConsoleApplication.hpp"

using namespace JDMC;

ConsoleApplication::ConsoleApplication()
	: JDMC::Window("SpriteMaker", 114, 115, 6, 6), canvas(maxRow, std::vector<short>(maxCol, Color::DEFAULT))
{}

ConsoleApplication::~ConsoleApplication()
{
	this->canvas.clear();
}


bool ConsoleApplication::onUserCreate()
{
	this->saveLabel = new LabelSprite({80, 106}, "SAVE");
	this->saveLabel->SetX(102 - this->saveLabel->GetWidth());

	this->openLabel = new LabelSprite({80, 106}, "OPEN");
	this->openLabel->SetX(98 - this->saveLabel->GetWidth() - this->openLabel->GetWidth());

	// Pen
	this->toolDesign[0] += L"88888888\n";
	this->toolDesign[0] += L"0FFFFF88\n";
	this->toolDesign[0] += L"80788078\n";
	this->toolDesign[0] += L"80788078\n";
	this->toolDesign[0] += L"807FFF88\n";
	this->toolDesign[0] += L"80788888\n";
	this->toolDesign[0] += L"80788888\n";
	this->toolDesign[0] += L"88888888\n";

	// Bucket
	this->toolDesign[1] += L"88000088\n";
	this->toolDesign[1] += L"80777708\n";
	this->toolDesign[1] += L"07888870\n";
	this->toolDesign[1] += L"08888880\n";
	this->toolDesign[1] += L"00888800\n";
	this->toolDesign[1] += L"07000070\n";
	this->toolDesign[1] += L"807FFF08\n";
	this->toolDesign[1] += L"8807F088\n";

	// Eraser
	this->toolDesign[2] += L"88888888\n";
	this->toolDesign[2] += L"88800008\n";
	this->toolDesign[2] += L"88090770\n";
	this->toolDesign[2] += L"80991003\n";
	this->toolDesign[2] += L"09910B30\n";
	this->toolDesign[2] += L"8010BB08\n";
	this->toolDesign[2] += L"88000088\n";
	this->toolDesign[2] += L"88888888\n";

	// UP
	this->toolDesign[3] += L"88844888\n";
	this->toolDesign[3] += L"884FF488\n";
	this->toolDesign[3] += L"84FFFF48\n";
	this->toolDesign[3] += L"4FFFFFF4\n";
	this->toolDesign[3] += L"888FF888\n";
	this->toolDesign[3] += L"888FF888\n";
	this->toolDesign[3] += L"888FF888\n";
	this->toolDesign[3] += L"888FF888\n";

	// DOWN
	this->toolDesign[4] += L"888FF888\n";
	this->toolDesign[4] += L"888FF888\n";
	this->toolDesign[4] += L"888FF888\n";
	this->toolDesign[4] += L"888FF888\n";
	this->toolDesign[4] += L"4FFFFFF4\n";
	this->toolDesign[4] += L"84FFFF48\n";
	this->toolDesign[4] += L"884FF488\n";
	this->toolDesign[4] += L"88844888\n";

	// LEFT
	this->toolDesign[5] += L"88848888\n";
	this->toolDesign[5] += L"884F8888\n";
	this->toolDesign[5] += L"84FF8888\n";
	this->toolDesign[5] += L"4FFFFFFF\n";
	this->toolDesign[5] += L"4FFFFFFF\n";
	this->toolDesign[5] += L"84FF8888\n";
	this->toolDesign[5] += L"884F8888\n";
	this->toolDesign[5] += L"88848888\n";

	// RIGHT
	this->toolDesign[6] += L"88884888\n";
	this->toolDesign[6] += L"8888F488\n";
	this->toolDesign[6] += L"8888FF48\n";
	this->toolDesign[6] += L"FFFFFFF4\n";
	this->toolDesign[6] += L"FFFFFFF4\n";
	this->toolDesign[6] += L"8888FF48\n";
	this->toolDesign[6] += L"8888F488\n";
	this->toolDesign[6] += L"88884888\n";

	return true;
}


void ConsoleApplication::drawCanvas()
{
	float newPixel = this->pixelSize * this->zoomMultiplier;
	for (int y = 0; y < this->maxRow; ++y)
	{
		for (int x = 0; x < this->maxCol; ++x)
		{
			float newX = x * this->zoomMultiplier + 2 + this->cameraX;
			float newY = y * this->zoomMultiplier + 2 + this->cameraY;
			if (newX > 102 || newY > 102)
				break;

			if (newX + this->zoomMultiplier < 0 || newY + this->zoomMultiplier < 0)
				continue;

			Drawer::DrawBox({newX, newY, newPixel, newPixel},
			Pixel::PIXEL_SOLID, ((this->canvas[y][x] != Color::DEFAULT) ?
				this->canvas[y][x] : Color::FG_DARK_GRAY));
		}
	}
}

void ConsoleApplication::drawPixel(short x, short y)
{
	this->drawPixel(x, y, this->currentPen);
}

void ConsoleApplication::drawPixel(short x, short y, Color penColor)
{
	if (this->canvas[y][x] == penColor)
		return;

	unsigned int encodedMove = this->canvas[y][x] * 10000 + x * 100 + y;
	this->currentMove.push_back(encodedMove);
	this->canvas[y][x] = penColor;
}

void ConsoleApplication::endDrawing()
{
	if (!this->currentMove.empty())
	{
		this->undoStack.push(this->currentMove);
		while (!this->redoStack.empty())
			this->redoStack.pop();
	}
}

void ConsoleApplication::reDrawPixel(const std::vector<unsigned int> &lastMove)
{
	this->currentMove.clear();
	for (unsigned int encodedMove : lastMove)
	{
		short penColor = encodedMove / 10000;
		short x = encodedMove % 10000 / 100;
		short y = encodedMove % 100;
		this->currentMove.push_back(this->canvas[y][x] * 10000 + x * 100 + y);
		this->canvas[y][x] = penColor;
	}
}

void ConsoleApplication::undo()
{
	if (!this->undoStack.empty())
	{
		std::vector<unsigned int> lastMove = this->undoStack.top();
		this->undoStack.pop();

		this->reDrawPixel(lastMove);
		this->redoStack.push(this->currentMove);
	}
}

void ConsoleApplication::redo()
{
	if (!this->redoStack.empty())
	{
		std::vector<unsigned int> lastMove = this->redoStack.top();
		this->redoStack.pop();

		this->reDrawPixel(lastMove);
		this->undoStack.push(this->currentMove);
	}
}

void ConsoleApplication::cappedCamera()
{
	short cappedMin = 52;
	short cappedMax = -(this->maxCol * this->zoomMultiplier + 2 - 50);
	if (this->cameraX >= cappedMin)
		this->cameraX = cappedMin;
	else if (this->cameraX <= cappedMax)
		this->cameraX = cappedMax;

	cappedMin = 52;
	cappedMax = -(this->maxRow * this->zoomMultiplier + 2 - 50);
	if (this->cameraY >= cappedMin)
		this->cameraY = cappedMin;
	else if (this->cameraY <= cappedMax)
		this->cameraY = cappedMax;
}

void ConsoleApplication::cappedCoords()
{
	this->blink = 0.1;
	this->hideCursor = 3;
	if      (this->boxCoords.X < 0             ) this->boxCoords.X = 0;
	else if (this->boxCoords.X > this->maxCol-1) this->boxCoords.X = this->maxCol-1;
	if      (this->boxCoords.Y < 0             ) this->boxCoords.Y = 0;
	else if (this->boxCoords.Y > this->maxRow-1) this->boxCoords.Y = this->maxRow-1;
}

void ConsoleApplication::updateCamera()
{
	if (this->zoomMultiplier == 1)
	{
		this->cameraX = 0;
		this->cameraY = 0;
		return;
	}

	float oldX = this->cameraX;
	float oldY = this->cameraY;

	float minusX = (this->maxCol * this->zoomMultiplier / 2) / 2;
	float minusY = (this->maxRow * this->zoomMultiplier / 2) / 2;

	this->cameraX = -minusX + (oldX / 2);
	this->cameraY = -minusY + (oldY / 2);
}

void ConsoleApplication::FloodFill(int x, int y, short targetColor)
{
	if (x < 0 || x >= this->maxCol || y < 0 || y >= this->maxRow)
		return;

	if (this->canvas[y][x] != targetColor)
		return;

	if (this->canvas[y][x] == this->currentPen)
		return;

	this->drawPixel(x, y);
	this->FloodFill(x + 1, y, targetColor); // Right
	this->FloodFill(x - 1, y, targetColor); // Left
	this->FloodFill(x, y + 1, targetColor); // Down
	this->FloodFill(x, y - 1, targetColor); // Up
}

void ConsoleApplication::checkChange(short mouseX, short mouseY)
{
	for (short y = 0; y < 2; y++)
	{
		for (short x = 0; x < 8; x++)
		{
			short sep = 3;
			short width = 2;
			short height = 2;
			if (Function::collidePoint({
				3.f   + (sep * x) + (width * x),
				106.f + (sep * y) + (width * y),
				width, height}, mouseX, mouseY))
			{
				this->currentPen = static_cast<Color>(Function::GetIndex(x, y, 8));
				return;
			}
		}
	}

	for (short i = 0; i < 3; i++)
	{
		float y = 12 * i + 2;
		if (Function::collidePoint({105, y, 8, 8}, mouseX, mouseY))
		{
			this->toolUsed = static_cast<ToolAvailable>(i);
			break;
		}
	}

	// UP
	if (Function::collidePoint({105, 12 * 3 + 2, 8, 8}, mouseX, mouseY))
	{
		this->maxRow--;
		this->canvas.pop_back();
	}

	// DOWN
	else if (Function::collidePoint({105, 12 * 4 + 2, 8, 8}, mouseX, mouseY))
	{
		this->maxRow++;
		std::vector<short> v(this->maxCol, Color::DEFAULT);
		this->canvas.push_back(v);
	}

	// LEFT
	else if (Function::collidePoint({105, 12 * 5 + 2, 8, 8}, mouseX, mouseY))
	{
		this->maxCol--;
		for (short i = 0; i < this->maxRow; i++)
			this->canvas[i].pop_back();
	}

	// RIGHT
	else if (Function::collidePoint({105, 12 * 6 + 2, 8, 8}, mouseX, mouseY))
	{
		this->maxCol++;
		for (short i = 0; i < this->maxRow; i++)
			this->canvas[i].push_back(Color::DEFAULT);
	}

}

void ConsoleApplication::handleDraw(short x, short y)
{
	switch (this->toolUsed)
	{
	case ToolAvailable::TOOL_PEN:
		return this->drawPixel(x, y);
	case ToolAvailable::TOOL_BUCKET:
		return this->FloodFill(x, y, this->canvas[y][x]);
	case ToolAvailable::TOOL_ERASER:
		return this->drawPixel(x, y, Color::DEFAULT);
	}
}

void ConsoleApplication::handleKeys()
{
	///////////////////////////////////
	//  Keyboard | Touch
	///////////////////////////////////
	this->blink -= this->ElapseTime;
	this->hideCursor -= this->ElapseTime;
	if (this->isHeld(Keys::LCTRL) ^ this->isHeld(Keys::RCTRL))
	{
		if (this->drawingStarted)
		{
			this->drawingStarted = false;
			this->endDrawing();
		}

		if (this->isReleased(Keys::ADD))
		{
			this->zoomMultiplier++;
			this->updateCamera();
		}
		else if (this->isReleased(Keys::MINUS))
		{
			this->zoomMultiplier--;
			if (this->zoomMultiplier <= 0)
				this->zoomMultiplier = 1;
			this->updateCamera();
		}

		else if (this->isReleased(Keys::ZKEY))
			this->undo();
		else if (this->isReleased(Keys::YKEY))
			this->redo();
	}
	else
	{
		if (((this->toolUsed == ToolAvailable::TOOL_PEN || this->toolUsed == ToolAvailable::TOOL_ERASER) && this->isHeld(Keys::PKEY))
		 ||  (this->toolUsed == ToolAvailable::TOOL_BUCKET && this->isReleased(Keys::PKEY)))
		{
			if (!this->drawingStarted)
			{
				this->currentMove.clear();
				this->drawingStarted = true;
			}
			this->handleDraw(this->boxCoords.X, this->boxCoords.Y);
		}

		else if (this->isPressed(Keys::MOUSE_LEFT))
		{
			short mouseX = this->GetMouseX();
			short mouseY = this->GetMouseY();
			if (!(mouseX > 2 && mouseX <= 102 && mouseY > 2 && mouseY <= 102))
				this->checkChange(mouseX, mouseY);
		}
		else if (((this->toolUsed == ToolAvailable::TOOL_PEN || this->toolUsed == ToolAvailable::TOOL_ERASER) && this->isHeld(Keys::MOUSE_LEFT))
			  ||  (this->toolUsed == ToolAvailable::TOOL_BUCKET && this->isReleased(Keys::MOUSE_LEFT)))
		{
			short mouseX = this->GetMouseX();
			short mouseY = this->GetMouseY();
			if (mouseX > 2 && mouseX <= 102 && mouseY > 2 && mouseY <= 102)
			{
				mouseX -= this->cameraX;
				mouseY -= this->cameraY;
				if (!this->drawingStarted)
				{
					this->currentMove.clear();
					this->drawingStarted = true;
				}
				short xPos = ((mouseX - 2) / this->zoomMultiplier);
				short yPos = ((mouseY - 2) / this->zoomMultiplier);
				if (xPos >= 0 && xPos < this->maxCol && yPos >= 0 && yPos < this->maxRow)
				{
					this->handleDraw(xPos, yPos);
					this->boxCoords.X = xPos;
					this->boxCoords.Y = yPos;
					this->hideCursor = 3;
				}
			}
		}
		else if (this->drawingStarted)
		{
			this->drawingStarted = false;
			this->endDrawing();
		}
		if (this->blink <= 0)
		{
			if      (this->isHeld(Keys::AKEY)) { this->boxCoords.X -= 1; this->cappedCoords(); }
			else if (this->isHeld(Keys::DKEY)) { this->boxCoords.X += 1; this->cappedCoords(); }
			if      (this->isHeld(Keys::WKEY)) { this->boxCoords.Y -= 1; this->cappedCoords(); }
			else if (this->isHeld(Keys::SKEY)) { this->boxCoords.Y += 1; this->cappedCoords(); }	
		}

		if (this->isHeld(Keys::LEFTKEY))
			this->cameraX++;
		else if (this->isHeld(Keys::RIGHTKEY))
			this->cameraX--;
		else if (this->isHeld(Keys::UPKEY))
			this->cameraY++;
		else if (this->isHeld(Keys::DOWNKEY))
			this->cameraY--;

	}
	this->cappedCamera();
}

bool ConsoleApplication::onUserUpdate()
{
	short mouseX = this->GetMouseX();
	short mouseY = this->GetMouseY();
	this->Clear(Pixel::BLANK, Color::BG_BLACK);

	///////////////////////////////////
	//  Draw Top
	///////////////////////////////////

	// DrawCanvas
	this->drawCanvas();
	if (showCoords && this->hideCursor > 0) Drawer::DrawBoxHollow({
		2 + (this->boxCoords.X * this->zoomMultiplier) - 1 + this->cameraX,
		2 + (this->boxCoords.Y * this->zoomMultiplier) - 1 + this->cameraY,
		this->zoomMultiplier + 2, this->zoomMultiplier + 2},
		1, Pixel::PIXEL_SOLID, Color::FG_RED);

	Drawer::DrawBoxHollow({0, 0, 104, static_cast<float>(this->GetHeight()) - 11},
		2, Pixel::PIXEL_SOLID, Color::FG_GRAY);

	///////////////////////////////////
	//  Draw Bottom
	///////////////////////////////////

	Drawer::DrawBox({0, 104, 104, 11}, Pixel::PIXEL_SOLID, Color::FG_WHITE);
	Drawer::DrawBox({104, 0, 10, static_cast<float>(this->GetHeight())}, Pixel::PIXEL_SOLID, Color::FG_DARK_GRAY);

	for (short y = 0; y < 2; y++)
	{
		for (short x = 0; x < 8; x++)
		{
			float xPos = 3.f   + (3 * x) + (2 * x);
			float yPos = 106.f + (3 * y) + (2 * y);
			Color active = static_cast<Color>(Function::GetIndex(x, y, 8));
			Drawer::DrawBoxHollow({xPos-1, yPos-1, 4, 4}, 1, Pixel::PIXEL_SOLID,
				(this->currentPen == active ?
					Color::FG_RED : (Function::collidePoint({xPos, yPos, 2, 2}, mouseX, mouseY) ?
						Color::FG_YELLOW : Color::FG_DARK_GRAY)));
			Drawer::DrawBox({xPos, yPos, 2, 2}, Pixel::PIXEL_SOLID, active);
		}
	}

	for (short i = 0; i < 3; i++)
	{
		float y = 12 * i + 1;
		ToolAvailable tools = static_cast<ToolAvailable>(i);
		Drawer::DrawBoxHollow({104, y, 10, 10}, 1, Pixel::PIXEL_SOLID,
			(this->toolUsed == tools ?
				Color::FG_RED : (Function::collidePoint({105, y+1, 8, 8}, mouseX, mouseY) ?
					Color::FG_YELLOW : Color::FG_WHITE)));
		Drawer::DrawCString({105, y+1}, this->toolDesign[i], true);
	}

	for (short i = 3; i < 7; i++)
	{
		float y = 12 * i + 1;
		Drawer::DrawBoxHollow({104, y, 10, 10}, 1, Pixel::PIXEL_SOLID,
			(Function::collidePoint({105, y+1, 8, 8}, mouseX, mouseY) ? Color::FG_CYAN : Color::FG_WHITE));
		Drawer::DrawCString({105, y+1}, this->toolDesign[i], true);
	}

	// DrawOpen
	Drawer::DrawBox({this->openLabel->GetX()-1, this->openLabel->GetY()-1,
		this->openLabel->GetWidth()+2, this->openLabel->GetHeight()+2},
		Pixel::PIXEL_SOLID, (this->openLabel->CollidePoint(mouseX, mouseY) ?
			Color::FG_BLACK : Color::FG_DARK_GRAY), 2);
	this->openLabel->Render(Color::FG_WHITE);

	// DrawSave
	Drawer::DrawBox({this->saveLabel->GetX()-1, this->saveLabel->GetY()-1,
		this->saveLabel->GetWidth()+2, this->saveLabel->GetHeight()+2},
		Pixel::PIXEL_SOLID, (this->saveLabel->CollidePoint(mouseX, mouseY) ?
			Color::FG_BLACK : Color::FG_DARK_GRAY), 2);
	this->saveLabel->Render(Color::FG_WHITE);

	this->handleKeys();

	return true;
}
