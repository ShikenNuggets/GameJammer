#ifndef JAMMER_INPUT_INPUT_H
#define JAMMER_INPUT_INPUT_H

//Hide warnings from external code that we can't/won't modify - WNF
#pragma warning(disable : 26819) //Unnanotated fallthrough in switch statement
#include <SDL.h>
#pragma warning(default : 26819)

#include "Input/InputEnums.h"

namespace Jammer{
	class Input{
	public:
		Input();

		bool GetButtonDown(ButtonID button_);
		bool GetButtonUp(ButtonID button_);
		bool GetButtonHeld(ButtonID button_);

		float GetAxis(AxisID axis_);

	private:

	};
}

#endif //!JAMMER_INPUT_INPUT_H