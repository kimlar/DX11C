#include "LoadPNG.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

// Load PNG Image
unsigned char* image_load_png(const char* filename, int* width, int* height, int* numChannels)
{
	//int forceNumChannels = 4;
	int forceNumChannels = 0;
	unsigned char* textureData = stbi_load(filename, width, height, numChannels, forceNumChannels);
	//assert(textureData);

	return textureData;
}
