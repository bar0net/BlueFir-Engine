-- ===================================================================================
-- =============================== PROJECT MathGeoLib ================================
-- ===================================================================================
project "MathGeoLib"
	location "MathGeoLib"
	kind "StaticLib"
	language "C++"
	
	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "../files/"
	
	files
	{
		"%{prj.name}/**/**.h",
		"%{prj.name}/**/**.cpp"
	}
	
	includedirs
	{
	}
	
	libdirs
	{
	}
	
	links
	{
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
-- ================================== PROJECT ImGui ==================================
-- ===================================================================================
project "ImGui"
	location "imgui-docking"
	kind "StaticLib"
	language "C++"
	
	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "../files/"
	
	files
	{
		"imgui-docking/**.h",
		"imgui-docking/**.cpp"
	}
	
	includedirs
	{
		"glew-2.1.0/include/",
		"SDL2-2.0.8/include/"
	}
	
	libdirs
	{
		"glew-2.1.0/lib/x64/",
		"SDL2-2.0.8/lib/x64/",
	}
	
	links
	{
		"glew32",
		"OpenGL32",
		"SDL2",
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