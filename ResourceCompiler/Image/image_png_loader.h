#pragma once

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "Image/stb_image.h"

// Image resource types
enum ImageResourceType // Can't use 24 bits as GPU only supports 16/32 bits
{
	Unknown_ImageResourceType = 0,
	RGBA_U8_ImageResourceType,
	Grayscale_U16_ImageResourceType, /* NOT IMPLEMENTED */
	Grayscale_F32_ImageResourceType  /* NOT IMPLEMENTED */
	// For further formats look at dxgiformat.h
};

// Load PNG Image
byte* image_png_load_file(const char* filename, int* width, int* height, int* numChannels)
{
	//int forceNumChannels = 4;
	int forceNumChannels = 0;
	byte* textureData = stbi_load(filename, width, height, numChannels, forceNumChannels);
	//assert(textureData);

	return textureData;
}
