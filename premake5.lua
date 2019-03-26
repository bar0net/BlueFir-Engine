workspace "BlueFir Engine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Development",
		"Release"
	}
	
	startproject "BlueFir"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"	


-- ===================================================================================
-- ================================= PROJECT BLUEFIR =================================
-- ===================================================================================
project "BlueFir"
	location "Source/BlueFir"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "files/"
	
	files
	{
		"Source/%{prj.name}/src/**.h",
		"Source/%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"Source/Base/src",
		"Source/Graphics/src",
		"Source/Core/src",
		"Source/Renderer/src",
		"Source/Input/src",
		"Source/Scene/src",
		"Source/Time/src",
		"Source/Editor/src",
		"Source/Resources/src"
	}
	
	links
	{
		"Base",
		"Graphics",
		"Core",
		"Renderer",
		"Input",
		"Scene",
		"Time",
		"Editor",
		"Resources"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"BF_PLATFORM_WINDOWS"
		}
		
		
	filter "configurations:Debug"
		defines "BF_DEBUG"
		symbols "On"
		
	filter "configurations:Development"
		defines "BF_Development"
		optimize "On"
		
	filter "configurations:Release"
		defines "BF_RELEASE"
		optimize "On"
		

-- ===================================================================================
-- ================================== PROJECT BASE ===================================
-- ===================================================================================
project "Base"
	location "Source/Base"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "files/"
	
	files
	{
		"Source/%{prj.name}/src/**.h",
		"Source/%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"Vendor/SDL2-2.0.8/include/",
		"Vendor/rapidjson/include/"
	}
	
	libdirs
	{
		"Vendor/SDL2-2.0.8/lib/x64/"
	}
	
	links
	{
		"SDL2"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"BF_PLATFORM_WINDOWS"
		}
		
		
	filter "configurations:Debug"
		defines "BF_DEBUG"
		symbols "On"
		
	filter "configurations:Development"
		defines "BF_Development"
		optimize "On"
		
	filter "configurations:Release"
		defines "BF_RELEASE"
		optimize "On"

-- ===================================================================================
-- ================================ PROJECT GRAPHICS =================================
-- ===================================================================================
project "Graphics"
	location "Source/Graphics"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "files/"
	
	files
	{
		"Source/%{prj.name}/src/**.h",
		"Source/%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"Source/Base/src",
		"Vendor/glew-2.1.0/include/",
		"Vendor/SDL2-2.0.8/include/",
		"Vendor/DevIL/include"
	}
	
	libdirs
	{
		"Vendor/glew-2.1.0/lib/x64/",
		"Vendor/SDL2-2.0.8/lib/x64/",
		"Vendor/DevIL/lib/x64/Release"
	}
	
	links
	{
		"Base",
		"glew32",
		"OpenGL32",
		"SDL2",
		"DevIL",
		"ILU",
		"ILUT"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"BF_PLATFORM_WINDOWS"
		}
		
		
	filter "configurations:Debug"
		defines "BF_DEBUG"
		symbols "On"
		
	filter "configurations:Development"
		defines "BF_Development"
		optimize "On"
		
	filter "configurations:Release"
		defines "BF_RELEASE"
		optimize "On"

-- ===================================================================================
-- ################################## GROUP VENDOR ###################################
-- ===================================================================================
		
group "Vendor"
dofile("Vendor/premake5.lua")
		
-- ===================================================================================
-- ################################# GROUP MODULES ###################################
-- ===================================================================================

group "Modules"
-- ===================================================================================
-- ================================== PROJECT CORE ===================================
-- ===================================================================================
project "Core"
	location "Source/Core"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "files/"
	
	files
	{
		"Source/%{prj.name}/src/**.h",
		"Source/%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"Source/Base/src",
		
		"Vendor/MathGeoLib/"
	}
	
	libdirs
	{
	
	}
	
	links
	{
		"Base",
		"MathGeoLib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"BF_PLATFORM_WINDOWS"
		}
		
		
	filter "configurations:Debug"
		defines "BF_DEBUG"
		symbols "On"
		
	filter "configurations:Development"
		defines "BF_Development"
		optimize "On"
		
	filter "configurations:Release"
		defines "BF_RELEASE"
		optimize "On"
		
-- ===================================================================================
-- ================================ PROJECT RENDERER =================================
-- ===================================================================================
project "Renderer"
	location "Source/Renderer"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "files/"
	
	files
	{
		"Source/%{prj.name}/src/**.h",
		"Source/%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"Source/Base/src",
		"Source/Core/src",
		"Source/Graphics/src",
		"Vendor/MathGeoLib/"
	}
	
	libdirs
	{
	
	}
	
	links
	{
		"Base",
		"Core",
		"Graphics",
		"MathGeoLib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"BF_PLATFORM_WINDOWS"
		}
		
		
	filter "configurations:Debug"
		defines "BF_DEBUG"
		symbols "On"
		
	filter "configurations:Development"
		defines "BF_Development"
		optimize "On"
		
	filter "configurations:Release"
		defines "BF_RELEASE"
		optimize "On"
		
-- ===================================================================================
-- ================================== PROJECT SCENE ===================================
-- ===================================================================================
project "Scene"
	location "Source/Scene"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "files/"
	
	files
	{
		"Source/%{prj.name}/src/**.h",
		"Source/%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"Source/Base/src",
		"Source/Core/src",
		"Source/Renderer/src",
		"Source/Resources/src"
	}
	
	libdirs
	{
	
	}
	
	links
	{
		"Base",
		"Core",
		"Renderer",
		"Resources"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"BF_PLATFORM_WINDOWS"
		}
		
		
	filter "configurations:Debug"
		defines "BF_DEBUG"
		symbols "On"
		
	filter "configurations:Development"
		defines "BF_Development"
		optimize "On"
		
	filter "configurations:Release"
		defines "BF_RELEASE"
		optimize "On"
		
-- ===================================================================================
-- ================================== PROJECT INPUT ==================================
-- ===================================================================================
project "Input"
	location "Source/Input"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "files/"
	
	files
	{
		"Source/%{prj.name}/src/**.h",
		"Source/%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"Source/Base/src",
		"Source/Core/src",
		"Source/Renderer/src",
		"Source/Editor/src",
		"Vendor/SDL2-2.0.8/include/"
	}
	
	libdirs
	{
		"Vendor/SDL2-2.0.8/lib/x64/"	
	}
	
	links
	{
		"Base",
		"Core",
		"Renderer",
		"Editor",
		"SDL2"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"BF_PLATFORM_WINDOWS"
		}
		
		
	filter "configurations:Debug"
		defines "BF_DEBUG"
		symbols "On"
		
	filter "configurations:Development"
		defines "BF_Development"
		optimize "On"
		
	filter "configurations:Release"
		defines "BF_RELEASE"
		optimize "On"		
		
-- ===================================================================================
-- ================================= PROJECT TIME ==================================
-- ===================================================================================
project "Time"
	location "Source/Time"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "files/"
	
	files
	{
		"Source/%{prj.name}/src/**.h",
		"Source/%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"Source/Base/src",
		"Source/Core/src"
	}
	
	libdirs
	{
	
	}
	
	links
	{
		"Base",
		"Core"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"BF_PLATFORM_WINDOWS"
		}
		
		
	filter "configurations:Debug"
		defines "BF_DEBUG"
		symbols "On"
		
	filter "configurations:Development"
		defines "BF_Development"
		optimize "On"
		
	filter "configurations:Release"
		defines "BF_RELEASE"
		optimize "On"
		
-- ===================================================================================
-- ================================= PROJECT EDITOR ==================================
-- ===================================================================================
project "Editor"
	location "Source/Editor"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "files/"
	
	files
	{
		"Source/%{prj.name}/src/**.h",
		"Source/%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"Source/Base/src",
		"Source/Core/src",
		"Source/Graphics/src",
		"Source/Renderer/src",
		"Source/Time/src",
		"Source/Scene/src",
		"Source/Resources/src",
		
		"Vendor/glew-2.1.0/include/",
		"Vendor/SDL2-2.0.8/include/",
		"Vendor/imgui-docking/"
	}
	
	libdirs
	{
		"Vendor/glew-2.1.0/lib/x64/",
		"Vendor/SDL2-2.0.8/lib/x64/"	
	}
	
	links
	{
		"Base",
		"Core",
		"Graphics",
		"Renderer",
		"Time",
		"Scene",
		"Resources",
		
		"ImGui",
		"glew32",
		"OpenGL32",
		"SDL2"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"BF_PLATFORM_WINDOWS"
		}
		
		
	filter "configurations:Debug"
		defines "BF_DEBUG"
		symbols "On"
		
	filter "configurations:Development"
		defines "BF_Development"
		optimize "On"
		
	filter "configurations:Release"
		defines "BF_RELEASE"
		optimize "On"		

-- ===================================================================================
-- ================================ PROJECT RESOURCES ==================================
-- ===================================================================================
project "Resources"
	location "Source/Resources"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "files/"
	
	files
	{
		"Source/%{prj.name}/src/**.h",
		"Source/%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"Source/Base/src",
		"Source/Core/src",
		"Source/Graphics/src",
		"Source/Renderer/src",
		
		"Vendor/assimp/include"
	}
	
	libdirs
	{
		"Vendor/assimp/lib/x64"
	}
	
	links
	{
		"Base",
		"Core",
		"Renderer",
		"Graphics",
		"assimp-vc140-mt"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"BF_PLATFORM_WINDOWS"
		}
		
		
	filter "configurations:Debug"
		defines "BF_DEBUG"
		symbols "On"
		
	filter "configurations:Development"
		defines "BF_Development"
		optimize "On"
		
	filter "configurations:Release"
		defines "BF_RELEASE"
		optimize "On"				
group ""