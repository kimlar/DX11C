@echo off

IF EXIST "Temp" (
    rmdir "Temp" /s /q
)

mkdir Temp

ResourceCompiler.exe -c Temp/Resource.pack
ResourceCompiler.exe -a ../Textures/Debug/DebugBox.png Temp/Resource.pack
ResourceCompiler.exe -a ../Textures/Debug/AABB_debug_box.png Temp/Resource.pack
ResourceCompiler.exe -a ../Textures/General/tile03.png Temp/Resource.pack
ResourceCompiler.exe -a ../Textures/General/tile15.png Temp/Resource.pack
ResourceCompiler.exe -a ../Textures/General/transparent_red_x.png Temp/Resource.pack
ResourceCompiler.exe -a ../Textures/General-01/player-simple-frame.png Temp/Resource.pack
ResourceCompiler.exe -a ../Textures/Grass-00/grass09.png Temp/Resource.pack
ResourceCompiler.exe -a ../Textures/Skybox/skybox02.png Temp/Resource.pack

IF EXIST "Temp/Resource.pack" (
	xcopy Temp\Resource.pack ..\..\Data /y
)

IF EXIST "Temp" (
    rmdir "Temp" /s /q
)
