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
		"Base/src"
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
		"Vendor/glew-2.1.0/include/"
	}
	
	libdirs
	{
		"Vendor/glew-2.1.0/lib/x64/"
	}
	
	links
	{
		"Base",
		"glew32"
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