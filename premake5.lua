workspace "UmbrelaGameEngine3D"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "App"

    DEPS = "%{wks.location}/dependencies/GLFW"

project "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    location "program/engine"
    targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
    objdir    "%{wks.location}/bin/obj/%{cfg.buildcfg}"

    files {
        "program/engine/gfx/**.h",    "program/engine/gfx/**.cpp",
        "program/engine/misc/**.h",   "program/engine/misc/**.cpp",
        "program/engine/scene/**.h",  "program/engine/scene/**.cpp",
        "program/engine/shader/**.h", "program/engine/shader/**.cpp",
        "program/engine/src/**.h",    "program/engine/src/**.cpp",
        "program/engine/entity/**.h", "program/engine/entity/**.cpp",
        "program/engine/vendor/**.h", "program/engine/vendor/**.cpp",
        "program/engine/vendor/**.c",
    }

    includedirs {
        "program/engine/",
        "program/engine/vendor/",
        "%{DEPS}/include/",
    }

    libdirs {
        "%{DEPS}/lib/",
    }

    links {
        "glfw3",
        "assimp",
        "opengl32",
    }

project "App"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    location "program/app"
    targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
    objdir    "%{wks.location}/bin/obj/%{cfg.buildcfg}"
    debugdir  "%{wks.location}"

    files {
        "program/app/**.h",
        "program/app/**.cpp",
    }

    includedirs {
        "program/engine/",
        "program/engine/vendor/",
        "%{DEPS}/include/",
    }

    libdirs {
        "%{DEPS}/lib/",
    }

    links {
        "Engine",
        "glfw3",
        "assimp",
        "opengl32",
    }

    postbuildcommands {
        "{COPYFILE} %{DEPS}/bin/assimp-vc143-mt.dll %{wks.location}/bin/%{cfg.buildcfg}/"
    }