#include "JDMC.hpp"
#include "Sprites/JDMC_EntitySprite.hpp"
#include "Sprites/JDMC_LabelSprite.hpp"

class ConsoleApplication : public JDMC::Window
{
private:
	JDMC::EntitySprite *sprite;
	JDMC::LabelSprite *label;

public:
	ConsoleApplication();
	bool onUserCreate();
	bool onUserUpdate();
};
