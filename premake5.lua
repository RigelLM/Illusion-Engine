workspace "Project"
	architecture "x64"
	startproject "Game"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Illusion/Lib/GLFW/include"
IncludeDir["Glad"] = "Illusion/Lib/Glad/include"
IncludeDir["ImGui"] = "Illusion/Lib/imgui"
IncludeDir["glm"] = "Illusion/Lib/glm"
IncludeDir["stb_image"] = "Illusion/Lib/stb_image"
IncludeDir["IrrKlang"] = "Illusion/Lib/IrrKlang/include"


include "Illusion/Lib/GLFW"
include "Illusion/Lib/Glad"
include "Illusion/Lib/imgui"

project "Illusion"
	location "Illusion"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Illusion/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/Lib/stb_image/**.h",
		"%{prj.name}/Lib/stb_image/**.cpp",
		"%{prj.name}/Lib/glm/glm/**.hpp",
		"%{prj.name}/Lib/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/Lib/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.IrrKlang}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"Illusion/Lib/IrrKlang/Lib/irrKlang.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ILLUSION_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "ILLUSION_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ILLUSION_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ILLUSION_DIST"
		runtime "Release"
		optimize "on"

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Illusion/Lib/spdlog/include",
		"Illusion/src",
		"Illusion/Lib",
		"%{IncludeDir.glm}",
		"%{IncludeDir.IrrKlang}",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"Illusion",
		"Illusion/Lib/IrrKlang/Lib/irrKlang.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ILLUSION_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ILLUSION_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ILLUSION_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ILLUSION_DIST"
		runtime "Release"
		optimize "on"
