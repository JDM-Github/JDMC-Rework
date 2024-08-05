#include "ConsoleApplication.hpp"

ConsoleApplication::ConsoleApplication()
	: JDMC::Window("ConsoleApplication", 250, 250, 2, 2)
{
	this->label = new JDMC::LabelSprite("1234567890");
	this->sprite = new JDMC::EntitySprite({5, 20}, "Sprite/test.json");

	// this->label.SetFontSize(2);
}

bool ConsoleApplication::onUserCreate()
{
	return true;
}

bool ConsoleApplication::onUserUpdate()
{
	Clear();
	this->sprite->Render();
	this->label->Render();
	return true;
}

