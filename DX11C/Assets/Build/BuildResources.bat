@echo off

IF EXIST "Temp" (
    rmdir "Temp" /s /q
)

mkdir Temp

ImageConverter.exe ../Textures/Debug/DebugBox.png Temp
ImageConverter.exe ../Textures/Debug/AABB_debug_box.png Temp
ImageConverter.exe ../Textures/General/tile03.png Temp
ImageConverter.exe ../Textures/General/tile15.png Temp
ImageConverter.exe ../Textures/General/transparent_red_x.png Temp
ImageConverter.exe ../Textures/General-01/player-simple-frame.png Temp
ImageConverter.exe ../Textures/Grass-00/grass09.png Temp
ImageConverter.exe ../Textures/Skybox/skybox02.png Temp

REM ResourceCompiler.exe Temp/Resource.pack Temp/DebugBox.image_header Temp/AABB_debug_box.image_header Temp/tile03.image_header Temp/tile15.image_header Temp/transparent_red_x.image_header Temp/player-simple-frame.image_header Temp/grass09.image_header Temp/skybox02.image_header

ResourceCompiler.exe ^
Temp/Resource.pack ^
Temp/DebugBox.image_header ^
Temp/AABB_debug_box.image_header ^
Temp/tile03.image_header ^
Temp/tile15.image_header ^
Temp/transparent_red_x.image_header ^
Temp/player-simple-frame.image_header ^
Temp/grass09.image_header ^
Temp/skybox02.image_header

IF EXIST "Temp/Resource.pack" (
	xcopy Temp\Resource.pack ..\..\Data /y
)

IF EXIST "Temp" (
    rmdir "Temp" /s /q
)
