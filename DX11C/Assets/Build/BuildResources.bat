@echo off

IF EXIST "Temp" (
    rmdir "Temp" /s /q
)

mkdir Temp

ImageConverter.exe ../Textures/General/tile03.png Temp
ImageConverter.exe ../Textures/General/tile15.png Temp
ImageConverter.exe ../Textures/General/transparent_red_x.png Temp

ResourceCompiler.exe Temp/Resource.pack Temp/tile03.image_header Temp/tile15.image_header Temp/transparent_red_x.image_header

IF EXIST "Temp/Resource.pack" (
	xcopy Temp\Resource.pack ..\..\Data /y
)

IF EXIST "Temp" (
    rmdir "Temp" /s /q
)
