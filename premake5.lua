workspace"MusicPlayer"
  architecture "x64"

  configurations
  {
  	  "Debug",
	  "Release"
  }

 outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
 IncludeDir = {}
 IncludeDir["GLFW"] = "MusicPlayer/vendor/glfw/include"
 IncludeDir["ImGui"] = "MusicPlayer/vendor/imgui"

 include "MusicPlayer/vendor/glfw"
 include "MusicPlayer/vendor/imgui"

project "MusicPlayer"
  location "MusicPlayer"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  staticruntime "on"
  systemversion "latest"

  targetdir ("bin/" ..outputdir.. "/%{prj.name}")
  objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

  files
  {
  	  "%{prj.name}/Src/**.h",
	  "%{prj.name}/Src/**.cpp"
  }

  includedirs
  {
      "%{prj.name}/src",
	  "%{IncludeDir.GLFW}",
      "%{IncludeDir.ImGui}"
  }

  links
  {
  	  "GLFW",
      "ImGui",
	  "opengl32.lib"
  }

  filter "configurations:Debug"
	symbols "on"
   
  filter "configurations:Release"
	optimize  "on"