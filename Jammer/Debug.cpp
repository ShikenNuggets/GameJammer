#include "Debug.h"

#include <iostream>

#include <ShlObj_core.h>

//Hide warnings from external code that we can't/won't modify - WNF
#pragma warning(disable : 26819) //Unnanotated fallthrough in switch statement
#include <SDL_messagebox.h>
#pragma warning(default : 26819)

using namespace Jammer;

constexpr const char* logFileName = "log.txt";
bool gHasWrittenToFile = false;
const HANDLE gConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Debug::Log(const String& message_, const String& fileName_, int lineNumber_){
	std::cout << message_;

	if(!fileName_.IsEmpty()){
		std::cout << " [" << fileName_;

		if(lineNumber_ > 0){
			std::cout << ":" << lineNumber_;
		}

		std::cout << "]";
	}

	std::cout << "\n";
}

void Debug::LogWarning(const String& message_, const String& fileName_, int lineNumber_){
	if(gConsole){ SetConsoleTextAttribute(gConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY); }

	Debug::Log("WARNING: " + message_, fileName_, lineNumber_);

	if(gConsole){ SetConsoleTextAttribute(gConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); }
}

void Debug::LogError(const String& message_, const String& fileName_, int lineNumber_){
	if(gConsole){ SetConsoleTextAttribute(gConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); }

	Debug::Log("ERROR: " + message_, fileName_, lineNumber_);

	if(gConsole){ SetConsoleTextAttribute(gConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); }
}

int Debug::PopupAssertErrorMessage(const String& message_){
	Debug::LogError(message_);

	const SDL_MessageBoxButtonData buttons[2] = {
		{ 0, 0, "Ignore" },
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Break" }
	};

	const String messageWithPadding = message_ + "            \n            ";

	SDL_MessageBoxData data{};
	data.flags = SDL_MESSAGEBOX_WARNING;
	data.window = nullptr;
	data.title = "Assert Failed";
	data.message = messageWithPadding.CStr();
	data.numbuttons = std::size(buttons);
	data.buttons = buttons;
	data.colorScheme = nullptr;

	int buttonId;
	SDL_ShowMessageBox(&data, &buttonId);
	return buttonId;
}

void Debug::ThrowFatalError(const String& message_, ErrorCode error_, const String& fileName_, int lineNumber_){
	String messageWithErr = message_ + "\nError Code: " + GetErrorCodeString(error_);
	LogError(messageWithErr, fileName_, lineNumber_);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal Error", messageWithErr.CStr(), nullptr);
	throw std::runtime_error(messageWithErr.CStr());
}