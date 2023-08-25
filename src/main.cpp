#include "commonheader.h"

int Info::currentUid = 0;
bool Info::DebugMode = false;
Account *UserInterface::currentUser = nullptr;

int main()
{
	UserInterface ui;
	while (ui.run())
		;
	return 0;
}
