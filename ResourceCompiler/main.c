/*
*	ResourceCompiler - Turns .header + .data files into .pack file
*
*
* 	Structure(in: image header + image data):
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

// Defines
#define byte unsigned char

/*
		printf("Header files types:\n");
		printf("For images:\timage_header\n");
		printf("For models:\tmodel_header\n");
		printf("For shaders:\tshader_header\n");
		printf("For levels:\tlevel_header\n");
		printf("For scripts:\tscript_header\n");
		printf("For sound:\tsound_header\n");
		printf("For music:\tmusic_header\n");
		printf("For fonts:\tfont_header\n");
*/

// Resource types
enum ResourceType
{
	Image_Resource = 0,
	Model_Resource,
	Shader_Resource,
	Level_Resource,
	Script_Resource,
	Sound_Resource,
	Music_Resource,
	Font_Resource
};

// Image resource types
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
const char* get_file_only_path(const char* filename);
enum ResourceType get_resource_type(const char* fileext);

// Get the file name without the file extension (i.e. "Wizard.png" -> "Wizard")
const char* get_filename_basename(const char* filename, const char* fileext)
{
	//printf("#%s#\n", filename);
	//printf("#%s#\n", fileext);
	//printf("#%s#\n", get_filename_ext(filename));

	if (strcmp(get_filename_ext(filename), fileext) != 0)
	{
		printf("Error: Input file must have the same file extension\n");
		exit(1);
	}

	size_t temp_basename_length = strlen(filename) - strlen(fileext) - 1;
	char* temp_basename = (char*)malloc(temp_basename_length);
	for (int i = 0; i < temp_basename_length; i++)
	{
		temp_basename[i] = filename[i];
	}
	temp_basename[temp_basename_length] = '\0';

	// Remove all file path and which gives only the basename
	int fileNameIndex = 0;
	size_t basename_length = strlen(temp_basename);
	char* basename = (char*)malloc(basename_length);
	for (int i = 0; i < temp_basename_length; i++)
	{
		if (temp_basename[i] == '/' || temp_basename[i] == '\\')
		{
			fileNameIndex = i;
		}
	}
	for (int i = 0; i < basename_length; i++)
	{
		basename[i] = temp_basename[fileNameIndex + i + 1];
	}
	basename[basename_length] = '\0';

	//printf("Basename: %s\n", basename);

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

const char* get_file_only_path(const char* filename)
{
	//printf("#%s#\n", filename);
	int last_slash = 0;
	for (int i = 0; i < strlen(filename); i++)
	{
		if (filename[i] == '/' || filename[i] == '\\')
		{
			last_slash = i;
		}
	}

	char* newFilename = (char*)malloc(last_slash + 1);
	for (int i = 0; i < last_slash; i++)
	{
		newFilename[i] = filename[i];
	}
	newFilename[last_slash] = '\0';

	return newFilename;
}

const char* get_file_filepath(const char* filename)
{
	for (int i = (int)strlen(filename) - 1; i >= 0; i--)
	{
		if (filename[i] == '.')
		{
			char* filepath = (char*)malloc(i + 1);
			for (int j = 0; j < i; j++)
			{
				filepath[j] = filename[j];
			}
			filepath[i] = '\0';
			return filepath;
		}
	}

	return filename; // Did not find any '.' in filename.
}

//---------------------------------------------------------------------------------------------------------------------

enum ResourceType get_resource_type(const char* fileext)
{
	if (strcmp(fileext, "image_header") == 0)
		return Image_Resource;
	if (strcmp(fileext, "model_header") == 0)
		return Model_Resource;
	if (strcmp(fileext, "shader_header") == 0)
		return Shader_Resource;
	if (strcmp(fileext, "level_header") == 0)
		return Level_Resource;
	if (strcmp(fileext, "script_header") == 0)
		return Script_Resource;
	if (strcmp(fileext, "sound_header") == 0)
		return Sound_Resource;
	if (strcmp(fileext, "music_header") == 0)
		return Music_Resource;
	if (strcmp(fileext, "font_header") == 0)
		return Font_Resource;

	return -1;
}

//---------------------------------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{
	// Display help info?
	if (argc < 3)
	{
		printf("Packing files:\tUsage: ResourceCompiler.exe Resource.pack file1.image_header file2.image_header ...\n");
		printf("Listing files:\tUsage: ResourceCompiler.exe -l Resource.pack\n");
		printf("\n");
		printf("Header files types:\n");
		printf("For images:\timage_header\n");
		printf("For models:\tmodel_header\n");
		printf("For shaders:\tshader_header\n");
		printf("For levels:\tlevel_header\n");
		printf("For scripts:\tscript_header\n");
		printf("For sound:\tsound_header\n");
		printf("For music:\tmusic_header\n");
		printf("For fonts:\tfont_header\n");
		return 1;
	}

	//ResourceCompiler.exe Temp/Resource.pack Temp/tile03.image_header Temp/tile15.image_header Temp/transparent_red_x.image_header


	const char* file_pack_basename = get_filename_basename(argv[1], "pack");
	
	unsigned int resource_id = 0;

	FILE* resourceFile = fopen(argv[1], "wb");
	if (!resourceFile)
	{
		printf("Error: Failed to write resource file: %s\n", argv[1]);
		exit(1);
	}


	for (int i = 2; i < argc; i++)
	{
		//printf("\n");
		//printf("Full path: %s\n", argv[i]);
		//printf("Only path: %s\n", get_file_only_path(argv[i]));
		//printf("Basename: %s\n", get_filename_basename(argv[i], get_filename_ext(argv[i])));
		//printf("Fileext: %s\n", get_filename_ext(argv[i]));
		//printf("Resource type: %d\n", get_resource_type(get_filename_ext(argv[i])));

		FILE* headerFile = fopen(argv[i], "rb");
		if (!headerFile)
		{
			printf("Error: Failed to load header file\n");
			exit(1);
		}

		// Get file size
		fseek(headerFile, 0, SEEK_END);
		long headerFileLength = ftell(headerFile);
		fseek(headerFile, 0, SEEK_SET);

		// Allocate memory
		char* headerData = (char*)malloc(headerFileLength + 1);

		// Read data
		fread(headerData, headerFileLength, 1, headerFile);
		headerData[headerFileLength] = '\0';

		/* Work on data */
		//------------------------------------

		switch (get_resource_type(get_filename_ext(argv[i])))
		{
			case Image_Resource:
			{
			
				// Write resource id
				fwrite(&resource_id, sizeof(unsigned int), 1, resourceFile);

				// Write resource basename length
				unsigned char resource_name_length = headerData[0];
				fwrite(&resource_name_length, sizeof(unsigned char), 1, resourceFile);

				// Write resource basename
				fwrite(&headerData[1], sizeof(unsigned char), resource_name_length, resourceFile);

				// Write image type (RGBA_U8, Grayscale_U16, Grayscale_F32)
				fwrite(&headerData[1 + resource_name_length], sizeof(unsigned char), 1, resourceFile);

				// Write image width
				fwrite(&headerData[1 + resource_name_length + 1], sizeof(int), 1, resourceFile);

				// Write image height
				fwrite(&headerData[1 + resource_name_length + 1 + 4], sizeof(int), 1, resourceFile);

				// Write image data size
				char* dataFilepath = (char*)get_file_filepath(argv[i]);
				strcat(dataFilepath, ".image_data");
				FILE* dataFile = fopen(dataFilepath, "rb");
				if (!dataFile)
				{
					printf("Error: Failed to load data file\n");
					exit(1);
				}

				// Get file size
				fseek(dataFile, 0, SEEK_END);
				long dataFileLength = ftell(dataFile);
				fseek(dataFile, 0, SEEK_SET);
				
				// Write image data size to resource file
				fwrite(&dataFileLength, sizeof(int), 1, resourceFile);

				// Allocate memory
				unsigned char* dataImageData = (unsigned char*)malloc(dataFileLength + 1);

				// Read data
				fread(dataImageData, dataFileLength, 1, dataFile);
				dataImageData[dataFileLength] = '\0';

				// Write image data to resource file
				fwrite(dataImageData, sizeof(unsigned char), dataFileLength, resourceFile);

				// Close file
				fclose(dataFile);

				// Increment resource id
				resource_id++;

				break;
			}
			case Model_Resource:
			{
				break;
			}
			case Shader_Resource:
			{
				break;
			}
			case Level_Resource:
			{
				break;
			}
			case Script_Resource:
			{
				break;
			}
			case Sound_Resource:
			{
				break;
			}
			case Music_Resource:
			{
				break;
			}
			case Font_Resource:
			{
				break;
			}
			default:
			{
				printf("Error: Unknown resource type\n");
				exit(1);
				break;
			}
		}

		//------------------------------------

		// Deallocate memory
		free(headerData);
				
		// Close file
		fclose(headerFile);
		
		//
		printf("Resource item compiled: %s\n", argv[i]);
	}

	// Close file
	fclose(resourceFile);

	// Resource file created
	printf("Resource file compiled: %s\n", argv[1]);

	return 0; // Success
}
