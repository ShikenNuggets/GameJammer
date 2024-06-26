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
	}
end

function JammerExternalLibDirs()
	libdirs
	{
	}
end

function JammerExternalLibs(options)
	dependson
	{
	}

	options = options or {}
	if options.linkLibs then
		links
		{
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
	
	filter "system:windows"
		postbuildcommands
		{
		}
		
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
			"echo D|xcopy \"$(SolutionDir)Resources\\\" \"$(TargetDir)Resources\\\" /y /E /d",
		}
		
	filter "configurations:Debug or Develop"
		kind "ConsoleApp"
		IgnoreDefaultLibrariesForDebug()
		
	filter "configurations:Release"
		kind "WindowedApp"
		IgnoreDefaultLibrariesForRelease()