#ifndef JAMMER_JAMMER_ENUMS_H
#define JAMMER_JAMMER_ENUMS_H

#include <cstdint>
#include <xutility>

namespace Jammer{
	constexpr enum class ErrorCode : uint32_t{
		OK = 0,
		Unknown = 1,

		Invalid_State,
		Invalid_Args,
		FileIO,
		Constructor_Failed,

		Win32_Error,

		SDL_Error,

		OpenGL_Error,
		OpenGL_ShaderCompileFailed,

		ErrorCode_MAX
	};

	constexpr const char* ErrorCodeStr[10] = {
		"OK",
		"Unknown",

		"Invalid State",
		"Invalid Args",
		"File IO",
		"Constructor Failed",

		"Win32 Error",

		"SDL Error",

		"OpenGL Error"
		"OpenGL Shader Compile Failed",

		//ErrorCode_MAX
	};

	static_assert(std::size(ErrorCodeStr) == static_cast<uint32_t>(ErrorCode::ErrorCode_MAX));

	constexpr inline const char* GetErrorCodeString(ErrorCode err_){
		if(err_ >= ErrorCode::ErrorCode_MAX){
			return "Unknown Error Code";
		}

		return ErrorCodeStr[static_cast<uint32_t>(err_)];
	}
}

#endif //!JAMMER_JAMMER_ENUMS_H