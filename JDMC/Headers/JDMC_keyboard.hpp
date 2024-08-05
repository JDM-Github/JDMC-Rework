#pragma once
#include "JDMC_enum.hpp"
#include "JDMC_struct.hpp"
#include <unordered_set>

namespace JDMC
{
	class Window;
	class Keyboard
	{
	public:
		Keyboard();
		JDMC::KeyState getState(JDMC::Keys index);

	private:
		constexpr bool isKeyHeld    (bool OldState, bool NewState) { return ( OldState &&  NewState); }
		constexpr bool isKeyPressed (bool OldState, bool NewState) { return (!OldState &&  NewState); }
		constexpr bool isKeyReleased(bool OldState, bool NewState) { return ( OldState && !NewState); }
		void resetUpdateCycle();

	private:
		std::unordered_set<JDMC::Keys> allUpdated;

		JDMC::KeyState Keys[0x100];
		bool KeyOldState[0x100];
		bool KeyNewState[0x100];

		friend class Window;
	};
}
