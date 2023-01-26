workspace "TopDownShooter"

outputdir = "%{cfg.system}-%{cfg.buildcfg}-%{cfg.architecture}"

	configurations { "Debug", "Release" }
	platforms { "x64", "x86"}
	startproject "Game"

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"	
		
	filter { "platforms:x64" }
		architecture "x86_64"
		
	filter { "platforms:x86" }
		architecture "x86"

	newaction {
		trigger = "clean",
		description = "Remove all binaries, intermediates and build files",
		execute=function()
			print("Removing binaries")
			os.rmdir("./bin")
			print("Removing intermediates")
			os.rmdir("./bin-int")
			print("Removing build files")
			os.rmdir("./.vs")
			os.remove("**.sln")
			os.remove("**.vcxproj.**")
			os.remove("**Makefile**")
			os.remove("**.workspace")
			os.remove("**.project")
			print("Done")
		end
	}



project "raylib"
	location "%{wks.location}/vendor/raylib"
	language "C"
	cdialect "C17"
	cppdialect "C++20"
	targetdir ("%{wks.location}/bin/" .. outputdir)
	objdir ("%{wks.location}/bin-int/" .. outputdir)
	staticruntime "On"
	kind "StaticLib"
	systemversion "latest"
		
	filter "action:vs*"
		defines{ "_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS" }
		characterset ("MBCS")
	
	filter "system:windows"
		defines{ "_WIN32", "_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS" }
		links { "winmm", "kernel32", "opengl32", "gdi32" }
				
	filter "system:linux"
		links {"pthread", "GL", "m", "dl", "rt", "X11"}

	filter{}
	
	defines{ "PLATFORM_DESKTOP" }
	defines{ "GRAPHICS_API_OPENGL_43" }

	includedirs { 
		"%{prj.location}/src", 
		"%{prj.location}/src/external/glfw/include"
	 }
	vpaths 
	{
		["Header Files"] = { "raylib/src/**.h"},
		["Source Files/*"] = {"raylib/src/**.c"},
	}
	files { 
		"%{prj.location}/src/*.h", 
		"%{prj.location}/src/*.c"
	}
		
project "Game"
	location "%{wks.location}/Game"
	language "C++"
	targetdir ("%{wks.location}/bin/" .. outputdir)
	objdir ("%{wks.location}/bin-int/" .. outputdir)
	cppdialect "C++20"
	cdialect "C17"
	staticruntime "On"
	targetname "Square-Shooter"
	systemversion "latest"
	
	vpaths 
	{
		["Header Files"] = { "**.h", "**.hpp"},
		["Source Files"] = {"**.c", "**.cpp"},
	}
	files { 
		"%{prj.location}/src/**.c", 
		"%{prj.location}/src/**.cpp", 
		"%{prj.location}/src/**.h", 
		"%{prj.location}/src/**.hpp",
		"%{prj.location}/src/**.lua",
		"%{wks.location}/*.lua",
	}

	links {"raylib"}

	pchheader("pch.hpp")
	pchsource("%{prj.location}/src/pch.cpp")
	
	includedirs { 
		"%{wks.location}/vendor/raylib/src"
	 }
	
	defines{ "PLATFORM_DESKTOP" }
	defines{ "GRAPHICS_API_OPENGL_43" }	
			
	filter { "system:windows", "action:vs*" }
		defines{ 
			"STRICT",
			"NOMINMAX",
			"WINDOWS_LEAN_AND_MEAN",
			"_WINSOCK_DEPRECATED_NO_WARNINGS", 
			"_CRT_SECURE_NO_WARNINGS",
		}
		dependson { "raylib" }
		links { "raylib.lib" }
        characterset ("MBCS")

	filter { "configurations:Debug" }
		kind "ConsoleApp"

	filter { "configurations:Release" }
		kind "WindowedApp"
		entrypoint "mainCRTStartup"

	filter { "action:gmake*", "configurations:Release" }
		buildoptions { "-Of"}

	filter { "action:gmake*", "system:not windows", "configurations:Release" }
		buildoptions { "-Of" }
		
	filter "system:windows"
		defines{ "_WIN32", "_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS" }
		links { "winmm", "kernel32", "opengl32", "gdi32", "shell32" }
		libdirs { "bin/" ..outputdir }
		
	filter "system:linux"
		links { "pthread", "GL", "m", "dl", "rt", "X11" }
