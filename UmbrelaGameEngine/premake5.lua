project "UmbrelaGameEngine"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	--staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"vendor/**.cpp",
		"vendor/**.h",
		"vendor/**.c",
		"vendor/imgui/**.h",
		"vendor/imgui/**.cpp",
		"src/**.cpp",
		"src/**.h",
		"misc/**.cpp",
		"misc/**.h",
		"entity/**.cpp",
		"entity/**.h",
		"gfx/**.cpp",
		"gfx/**.h",
		"gfx/shader/**.cpp",
		"gfx/shader/**.h",
		"sandbox/**.cpp",
		"sandbox/**.h",
	}
	
	includedirs 
	{
		"%{wks.location}/Dependencies/GLFW/include"
	}
	
	libdirs 
	{
		"%{wks.location}/Dependencies/GLFW/lib-vc2019"
	}
	
	links
	{
		"glfw3.lib",
		"opengl32.lib",
		--"user32.lib",
		--"kernel32.lib",
		--"shell32.lib",
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"