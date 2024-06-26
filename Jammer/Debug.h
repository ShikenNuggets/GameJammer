#ifndef JAMMER_DEBUG_H
#define JAMMER_DEBUG_H

#include "Data/String.h"

namespace Jammer{
	namespace Debug{
		void Log(const String& message_, const String& fileName_ = "", int lineNumber_ = 0);
		void LogWarning(const String& message_, const String& fileName_ = "", int lineNumber_ = 0);
		void LogError(const String& message_, const String& fileName_ = "", int lineNumber_ = 0);
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

#endif //!JAMMER_DEBUG_H