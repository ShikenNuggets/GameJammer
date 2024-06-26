-- //-----------------------------------------------------------//
-- //---------------- Functions --------------------------------//
-- //-----------------------------------------------------------//

-- Defaults for new C++ projects
function CppProjectDefaults()
	location "%{prj.name}"
	language "C++"
	cppdialect "C++20"
	warnings "Extra"
	
	targetdir ("Build/%{prj.name}/%{cfg.buildcfg}/") 
	objdir ("Build/Intermediate/%{prj.name}/%{cfg.buildcfg}/")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp",
	}

	flags
	{
		"MultiProcessorCompile",
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		defines
		{
			"JAMMER_PLATFORM_WIN32",
		}

		fatalwarnings
		{
			"4715", -- Not all control paths return a value
			"4834", -- Discarding return value of function with [[nodiscard]] attribute
		}

	filter "configurations:Debug"
		defines "JAMMER_DEBUG"
		symbols "On"
		runtime "Debug"
	
	filter "configurations:Develop"
		defines
		{
			"JAMMER_DEBUG",
			"JAMMER_DEVELOP",
		}
		
		symbols "On"
		optimize "Speed"
		runtime "Debug"
	
		flags
		{
			"LinkTimeOptimization"
		}
	
	filter "configurations:Release"
		defines "JAMMER_RELEASE"
		optimize "Speed"
		runtime "Release"
	
		flags
		{
			"LinkTimeOptimization"
		}
	
	filter {} -- Deactivate filters
end

function JammerExternalIncludes()
	includedirs
	{
		"%{prj.name}/",
		"SDK/Glad/include",
		"SDK/SDL2/include",
		"SDK/SDL2_image/include",
	}
end

function JammerExternalLibDirs()
	libdirs
	{
		"SDK/Glad/lib/%{cfg.buildcfg}/",
		"SDK/SDL2/lib/x64/",
		"SDK/SDL2_image/lib/x64/",
	}
end

function JammerExternalLibs(options)
	options = options or {}
	if options.linkLibs then
		links
		{
			"Glad.lib",
			"SDL2.lib",
			"SDL2main.lib",
			"SDL2_image.lib",
		}
	end

	filter {} --Deactivate filters
end

function DependsOnJammer()
	includedirs { "Jammer/" }
	libdirs { "Build/Jammer/%{cfg.buildcfg}/" }
	links { "Jammer.lib" }
	dependson { "Jammer" }
	forceincludes { "Jammer.h" }
end

function IgnoreDefaultLibrariesForDebug()
	ignoredefaultlibraries
	{
		"libcmt",
		"msvcrt", 
		"msvcrtd"
	}
end

function IgnoreDefaultLibrariesForRelease()
	ignoredefaultlibraries
	{
		"libcmtd",
		"msvcrt",
		"msvcrtd"
	}
end

-- //-----------------------------------------------------------//
-- //---------------------- Workspace --------------------------//
-- //-----------------------------------------------------------//

workspace "GameJammer"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Develop",
		"Release"
	}
	
	startproject "Game"
	
-- //-----------------------------------------------------------//
-- //----------------------- Jammer ----------------------------//
-- //-----------------------------------------------------------//

project "Jammer"
	location "Jammer"
	kind "StaticLib"

	CppProjectDefaults()
	JammerExternalIncludes()
	JammerExternalLibDirs()
	JammerExternalLibs()
		
	filter "configurations:Release"
		symbols "Off"

-- //-----------------------------------------------------------//
-- //----------------------- Game ------------------------------//
-- //-----------------------------------------------------------//

project "Game"
	CppProjectDefaults()
	JammerExternalIncludes()
	JammerExternalLibDirs()
	JammerExternalLibs { linkLibs="true" }
	DependsOnJammer()

	dpiawareness "HighPerMonitor"
	debugdir ("%{cfg.targetdir}")
	
	filter "system:windows"
		postbuildcommands
		{
			"echo D|xcopy \"$(SolutionDir)SDK\\SDL2\\lib\\x64\\*.dll\" \"$(TargetDir)\" /y /E /d",
			"echo D|xcopy \"$(SolutionDir)SDK\\SDL2_image\\lib\\x64\\*.dll\" \"$(TargetDir)\" /y /E /d",
			"echo D|xcopy \"$(SolutionDir)SDK\\SDL2_image\\lib\\x64\\optional\\*.dll\" \"$(TargetDir)\" /y /E /d",
			"echo D|xcopy \"$(SolutionDir)Resources\\\" \"$(TargetDir)Resources\\\" /y /E /d",
		}
		
	filter "configurations:Debug or Develop"
		kind "ConsoleApp"
		IgnoreDefaultLibrariesForDebug()
		
	filter "configurations:Release"
		kind "WindowedApp"
		IgnoreDefaultLibrariesForRelease()