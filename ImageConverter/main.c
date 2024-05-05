/*
*	Image Converter - Converts .png to .header + .data files
* 
*	Purpose: To remove unneccessary .png dependencies in the main game project
* 
*/

// Disable warnings
#define _CRT_SECURE_NO_WARNINGS

// Includes - C standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Includes - Project headers
#include "ImageFormat/LoadPNG.h"

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
	//Wizard_Header.header
	//Wizard_Data.data

	// Get the filename with path and file extension
	const char* filename = argv[1];

	// Get the file name without the .png extension
	const char* basename = get_filename_basename(argv[1], "png");

	// Get the filename for the image header file
	const char* headerFilename = basename_append_extension(basename, "_Header.data");
	printf("#%s#", headerFilename);
	
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

	// Write Header file
	FILE* headerFile = fopen(headerFilename, "wb");
	if (!headerFile)
	{
		printf("Error: Failed to write header file\n");
		exit(1);
	}

	/*
	* resource_id: u32
	* resource_type: u8
	* resource_name_length: u8
	* resource_name: char[resource_name_length]
	* ...
	* resource_texture_width: u16
	* resource_texture_height: u16
	* ...
	* #resource_data_size infered by: char[resource_texture_width * resource_texture_height * numChannels]
	* resource_data: rgb/rgba (24/32 bits per pixel)
	*/


	return 0; // Success
}