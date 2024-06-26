#ifndef JAMMER_DEBUG_H
#define JAMMER_DEBUG_H

#include "JammerEnums.h"
#include "Data/String.h"

namespace Jammer{
	namespace Debug{
		void Log(const String& message_, const String& fileName_ = "", int lineNumber_ = 0);
		void LogWarning(const String& message_, const String& fileName_ = "", int lineNumber_ = 0);
		void LogError(const String& message_, const String& fileName_ = "", int lineNumber_ = 0);

		int PopupAssertErrorMessage(const String& message_);

		//This WILL crash the game! Only use this for completely unrecoverable error cases
		void ThrowFatalError(const String& message_, ErrorCode error_, const String& fileName_, int lineNumber_);
	};
}

#ifndef JLOG
	#define JLOG(message) Jammer::Debug::Log(message, __FILE__, __LINE__)
#endif //!JLOG

#ifndef JLOG_WARNING
	#define JLOG_WARNING(message) Jammer::Debug::Log(message, __FILE__, __LINE__)
#endif //!JLOG_WARNING

#ifndef JLOG_ERROR
	#define JLOG_ERROR(message) Jammer::Debug::Log(message, __FILE__, __LINE__)
#endif //!JLOG_ERROR

#if defined JAMMER_DEBUG && defined JAMMER_PLATFORM_WIN32 && !defined J_ASSERT
	#define J_ASSERT(expr, msg) { if(!(expr)){ int result = Jammer::Debug::PopupAssertErrorMessage(msg); if(result > 0){ __debugbreak(); } } }
#endif //JAMMER_DEBUG && JAMMER_PLATFORM_WIN32

#if defined JAMMER_RELEASE && !defined J_ASSERT
	//We still want the poup messages not the debug break
	#define J_ASSERT(expr, msg)
#endif //GADGET_RELEASE || !GADGET_PLATFORM_WIN32

#define J_BASIC_ASSERT(expr) J_ASSERT(expr, "Condition Failed: " ## #expr)
#define J_ASSERT_NOT_IMPLEMENTED J_ASSERT(false, "Case not implemented - Ask a dev!")

#endif //!JAMMER_DEBUG_H