/*
*	Image Converter - Converts .png to .header + .data files
* 
*	Purpose: To remove unneccessary .png dependencies in the main game project
* 
* 	Structure:
*	resource_name_length: u8
*	resource_name: char[resource_name_length]
*	resource_type: u8 <---- Gives us the resource_type: RGBA_U8, Grayscale_U16, Grayscale_F32
*	resource_texture_width: u32
*	resource_texture_height: u32
*	resource_data: rgba (32 bits per pixel) or grayscale (U16/F32 bits per pixel)
* 
*/

// Disable warnings
#define _CRT_SECURE_NO_WARNINGS

// Includes - C standard headers
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Includes - Project headers
#include "ImageFormat/LoadPNG.h"

#define byte unsigned char

enum ImageResourceType // Can't use 24 bits as GPU only supports 16/32 bits
{
	RGBA_U8 = 0,
	Grayscale_U16 = 1, /* NOT IMPLEMENTED */
	Grayscale_F32 = 2  /* NOT IMPLEMENTED */
	// For further formats look at dxgiformat.h
};

// Prototypes
const char* get_filename_basename(const char* filename, const char* fileext);
const char* get_filename_ext(const char* filename);
const char* basename_add_extension(const char* basename, const char* fileext);

// Get the file name without the file extension (i.e. "Wizard.png" -> "Wizard")
const char* get_filename_basename(const char* filename, const char* fileext)
{
	if (strcmp(get_filename_ext(filename), fileext) != 0)
	{
		printf("Error: Input file must have the same file extension\n");
		exit(1);
	}

	size_t basename_length = strlen(filename) - strlen(fileext) - 1;
	char* basename = (char*)malloc(basename_length);
	for (int i = 0; i < basename_length; i++)
	{
		basename[i] = filename[i];
	}
	basename[basename_length] = '\0';

	return basename;
}

const char* get_filename_ext(const char* filename)
{
	const char* dot = strrchr(filename, '.');
	if (!dot || dot == filename)
		return "";
	return dot + 1;
}

const char* basename_append_extension(const char* basename, const char* fileext)
{
	char* newFilename = (char*)malloc(strlen(basename) + strlen(fileext) + 1);
	for (int i = 0; i < strlen(basename); i++)
	{
		newFilename[i] = basename[i];
	}
	for (int i = 0; i < strlen(fileext); i++)
	{
		newFilename[strlen(basename) + i] = fileext[i];
	}
	newFilename[strlen(basename) + strlen(fileext)] = '\0';

	return newFilename;
}

int main(int argc, char** argv)
{
	// Check for number of arguments
	if (argc == 1)
	{
		printf("Usage: ImageConverter.exe <png_filename>\n");
		exit(1);
	}

	// Check if the file has a .png file extension
	if (strcmp(get_filename_ext(argv[1]), "png") != 0)
	{
		printf("Error: Input file must be a .png file\n");
		exit(1);
	}


	//Wizard.png
	//Wizard_ImageHeader.header
	//Wizard_ImageData.data

	// Get the filename with path and file extension
	const char* filename = argv[1];

	// Get the file name without the .png extension
	const char* basename = get_filename_basename(argv[1], "png");

	// Get the filename for the image header file
	const char* imageHeaderFilename = basename_append_extension(basename, "_ImageHeader.data");
	//printf("#%s#", headerFilename);

	// Get the filename for the image data file
	const char* imageDataFilename = basename_append_extension(basename, "_ImageData.data");
	//printf("#%s#", dataFilename);


	// Load PNG Image and get image properties
	int width;
	int height;
	int numChannels;
	unsigned char* textureData = image_load_png(filename, &width, &height, &numChannels);
	if (!textureData)
	{
		printf("Error: Failed to load png image\n");
		exit(1);
	}

	// Write Image Header file
	FILE* imageHeaderFile = fopen(imageHeaderFilename, "wb");
	if (!imageHeaderFile)
	{
		printf("Error: Failed to write image header file\n");
		exit(1);
	}

	

	// Set image resource type
	byte resourceType = RGBA_U8;

	// Write image header data
	fprintf(imageHeaderFile, "%c", (byte)strlen(basename));
	fprintf(imageHeaderFile, "%s", basename);
	fprintf(imageHeaderFile, "%c", resourceType);
	fwrite((const void*)&width, sizeof(int), 1, imageHeaderFile);
	fwrite((const void*)&height, sizeof(int), 1, imageHeaderFile);

	fclose(imageHeaderFile);
	printf("Image resource header: %s\n", imageHeaderFilename);

	// Write image data (raw image data)
	FILE* imageDataFile = fopen(imageDataFilename, "wb");
	if (!imageDataFile)
	{
		printf("Error: Failed to write image data file\n");
		exit(1);
	}

	fwrite(&textureData[0], width * height * numChannels, 1, imageDataFile);

	fclose(imageDataFile);
	printf("Image resource data: %s\n", imageDataFilename);

	return 0; // Success
}