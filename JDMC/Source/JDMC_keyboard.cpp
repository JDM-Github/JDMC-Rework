#include <Windows.h>
#include "JDMC_keyboard.hpp"

JDMC::Keyboard::Keyboard()
	: KeyOldState{false}, KeyNewState{false}
{
}

JDMC::KeyState JDMC::Keyboard::getState(JDMC::Keys key)
{
	short index = static_cast<short>(key);
	if (this->allUpdated.find(key) != this->allUpdated.end())
		return this->Keys[index];

	this->allUpdated.insert(key);

	this->KeyNewState[index]     = GetKeyState(index) & 0x8000;
	this->Keys[index].isHeld     = this->isKeyHeld    (this->KeyOldState[index], this->KeyNewState[index]);
	this->Keys[index].isPressed  = this->isKeyPressed (this->KeyOldState[index], this->KeyNewState[index]);
	this->Keys[index].isReleased = this->isKeyReleased(this->KeyOldState[index], this->KeyNewState[index]);
	this->KeyOldState[index]     = this->KeyNewState[index];
	return this->Keys[index];
}

void JDMC::Keyboard::resetUpdateCycle()
{
	this->allUpdated.clear();
}
