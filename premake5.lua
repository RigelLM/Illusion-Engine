workspace "Project"
	architecture "x64"
	startproject "Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["glfw"] = "Illusion/Lib/glfw/include"
IncludeDir["Glad"] = "Illusion/Lib/Glad/include"
IncludeDir["ImGui"] = "Illusion/Lib/imgui"
IncludeDir["glm"] = "Illusion/Lib/glm"
IncludeDir["stb_image"] = "Illusion/Lib/stb_image"
IncludeDir["EnTT"] = "Illusion/Lib/EnTT/include"
IncludeDir["Json"] = "Illusion/Lib/nlohmann/include"

group "Dependencies"
	include "Illusion/Lib/glfw"
	include "Illusion/Lib/Glad"
	include "Illusion/Lib/imgui"
group ""

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
		"%{IncludeDir.glfw}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.EnTT}",
		"%{IncludeDir.Json}"
	}

	links 
	{ 
		"glfw",
		"Glad",
		"ImGui",
		"opengl32.lib"
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
		"%{IncludeDir.glfw}",
		"%{IncludeDir.EnTT}"
	}

	links
	{
		"Illusion"
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

project "Editor"
	location "Editor"
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
		"%{IncludeDir.glfw}",
		"%{IncludeDir.EnTT}"
	}

	links
	{
		"Illusion"
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
