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
	location "BlueFir"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "files/"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"Base/src",
		"Graphics/src",
		"Core/src",
		"Renderer/src",
		"Input/src",
		"Scene/src",
		"Time/src",
		"Editor/src",
		"Resources/src"
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
	location "Base"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "files/"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"Vendor/SDL2-2.0.8/include/"
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
	location "Graphics"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "files/"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"Base/src",
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
-- ################################# GROUP MODULES ###################################
-- ===================================================================================

group "Modules"
-- ===================================================================================
-- ================================== PROJECT CORE ===================================
-- ===================================================================================
project "Core"
	location "Core"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "files/"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		
		"%{prj.name}/Vendor/**/**.h",
		"%{prj.name}/Vendor/**/**.cpp"
	}
	
	includedirs
	{
		"Base/src"
	}
	
	libdirs
	{
	
	}
	
	links
	{
		"Base"
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
	location "Renderer"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "files/"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		
		"%{prj.name}/Vendor/**/**.h",
		"%{prj.name}/Vendor/**/**.cpp"
	}
	
	includedirs
	{
		"Base/src",
		"Core/src",
		"Graphics/src"
	}
	
	libdirs
	{
	
	}
	
	links
	{
		"Base",
		"Core",
		"Graphics"
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
	location "Scene"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "files/"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		
		"%{prj.name}/Vendor/**/**.h",
		"%{prj.name}/Vendor/**/**.cpp"
	}
	
	includedirs
	{
		"Base/src",
		"Core/src",
		"Renderer/src"
	}
	
	libdirs
	{
	
	}
	
	links
	{
		"Base",
		"Core",
		"Renderer"
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
	location "Input"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "files/"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		
		"%{prj.name}/Vendor/**/**.h",
		"%{prj.name}/Vendor/**/**.cpp"
	}
	
	includedirs
	{
		"Base/src",
		"Core/src",
		"Renderer/src",
		"Editor/src",
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
	location "Time"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "files/"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		
		"%{prj.name}/Vendor/**/**.h",
		"%{prj.name}/Vendor/**/**.cpp"
	}
	
	includedirs
	{
		"Base/src",
		"Core/src"
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
	location "Editor"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "files/"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		
		"%{prj.name}/Vendor/**/**.h",
		"%{prj.name}/Vendor/**/**.cpp"
	}
	
	includedirs
	{
		"Base/src",
		"Core/src",
		"Graphics/src",
		"Renderer/src",
		"Time/src",
		"Scene/src",
		"Resources/src",
		
		"Vendor/glew-2.1.0/include/",
		"Vendor/SDL2-2.0.8/include/"
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
	location "Resources"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "files/"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		
		"%{prj.name}/Vendor/**/**.h",
		"%{prj.name}/Vendor/**/**.cpp"
	}
	
	includedirs
	{
		"Base/src",
		"Core/src",
		"Graphics/src",
		"Vendor/Assimp/include"
	}
	
	libdirs
	{
		"Vendor/Assimp/lib/x64"
	
	}
	
	links
	{
		"Base",
		"Core",
		"Renderer",
		"Graphics"
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