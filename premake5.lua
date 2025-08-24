project "engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	defines {
		"GLFW_INCLUDE_NONE"
	}

	files
	{
		"src/**.h",
		"src/**.cpp",
		"%{IncludeDir.stb_image}/**.h",
		"%{IncludeDir.stb_image}/**.cpp",
	}

	includedirs
	{
		"src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.SDL3}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.json}",
		"%{IncludeDir.zipFile}",
	}

	links 
	{
		"SDL3",
		"GLFW",
		"glad",
		"ImGui"
	}

	libdirs
	{
		"%{IncludeDir.SDL3}/../lib/x64/"
	}

	flags {
		"MultiProcessorCompile"
	}

	filter "system:windows"
		systemversion "latest"
		buildoptions { "/utf-8" }

	filter "system:linux"
		systemversion "latest"

	filter "system:macosx"
		systemversion "latest"
        xcodebuildsettings { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }

	filter "configurations:Debug*"
		defines "EG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release*"
		defines "EG_RELEASE"
		runtime "Release"
		symbols "on"
		optimize "on"

	filter "configurations:Dist*"
		defines "EG_DIST"
		runtime "Release"
		symbols "off"
		optimize "on"
