#pragma once

#include "Common.h"
#include "ResourceType.h"
#include "Image/image_png_loader.h"

// Prototypes
u32 resource_compiler_create(str resource_filename);
u32 resource_compiler_add(str item_filename, str resource_filename);
u32 resource_compiler_remove(str item_filename, str resource_filename);
u32 resource_compiler_list(str resource_filename);
u32 resource_compiler_help();
u32 resource_compiler_incorrect_usage();

// ---------------------------------------------------------------------------------------------------------------

// Create a new resource file (blank file)
u32 resource_compiler_create(str resource_filename)
{
	// Create a new resource file. Truncate the file if it already exists.
	binary_file resource_file = binary_file_write_new(resource_filename);
	if (resource_file == NULL)
	{
		printf("Error: Failed to create resource file: %s\n", resource_filename);
		return 1; // Failed
	}

	// Close the file
	binary_file_close(resource_file);

	return 0;
}

// Add a resource item to an existing resource file
u32 resource_compiler_add(str item_filename, str resource_filename)
{
	// Readying the header
	u32 header_size = 0;
	file_size data_size = binary_file_get_size(item_filename);
	u32 data_type = get_resource_type(get_file_extension(item_filename));
	str data_name = get_file_basename(item_filename);

	// Calculate the header size
	header_size = sizeof(header_size) + sizeof(data_size) + sizeof(data_type) + (u32)strlen(data_name);

	// Inform user about current item file to be added into the resource file
	printf("Adding: %s\n", get_file_fullname(item_filename));
	
	// Add the item to the resource file
	if (data_type == Image_RGBA_U8_ResourceType)
	{
		int width;
		int height;
		int numChannels;
		byte* image_data = image_png_load_file(item_filename, &width, &height, &numChannels);
		if (image_data == NULL)
		{
			printf("Error: Failed to load image file: %s\n", item_filename);
			exit(1);
		}

		// Get the data type
		data_type = (u8)Unknown_ImageResourceType;
		if (numChannels == 4)
		{
			data_type = (u8)RGBA_U8_ImageResourceType;
		}

		// Get image width and height
		u32 image_width = width;
		u32 image_height = height;

		// Calculate the data size (image_width + image_height + image_data_size)
		data_size = sizeof(image_width) + sizeof(image_height) + (image_width * image_height * 4);

		// Add a resource item to an existing resource file
		binary_file resource_file = binary_file_write_append(resource_filename);
		if (resource_file == NULL)
		{
			printf("Error: Failed to open resource file: %s\n", resource_filename);
			return 1;
		}

		// Write the header
		binary_file_write_u32(&header_size, resource_file);
		binary_file_write_u64(&data_size, resource_file);
		binary_file_write_u32(&data_type, resource_file);
		binary_file_write_str(data_name, resource_file);

		// Write the data
		binary_file_write_u32(&image_width, resource_file);
		binary_file_write_u32(&image_height, resource_file);
		binary_file_write_byte(image_data, sizeof(byte) * image_width * image_height * 4, resource_file);

		// Close the file
		binary_file_close(resource_file);

		// Free the image data
		free(image_data);

		return 0; // Finish with the job
	}
	if (data_type == Shader_Pixel_ResourceType)
	{
		return 0;
	}
	if (data_type == Shader_Vertex_ResourceType)
	{
		return 0;
	}

	return 0;
}

// Remove a resource item from an existing resource file
u32 resource_compiler_remove(str item_filename, str resource_filename)
{
	return 0;
}

// List all resource items in an existing resource file
u32 resource_compiler_list(str resource_filename)
{
	return 0;
}

// Help
u32 resource_compiler_help()
{
	printf("Flags:\n");
	printf("  -c Create a new blank resource file. Truncate the file if it already exists.\n");
	printf("  -a Add a resource item to an existing resource file.\n");
	printf("  -r Remove a resource item from an existing resource file.\n");
	printf("  -l List all resource items in an existing resource file.\n");
	printf("  -h Display this help\n");
	printf("\n");
	printf("Usage:\n");
	printf("ResourceCompiler.exe -c <resource_file.pack>\n");
	printf("ResourceCompiler.exe -a <item_file.dat> <resource_file.pack>\n");
	printf("ResourceCompiler.exe -r <item_file.dat> <resource_file.pack>\n");
	printf("ResourceCompiler.exe -l <resource_file.pack>\n");
	printf("ResourceCompiler.exe -h\n");

	return 0;
}

// Incorrect usage
u32 resource_compiler_incorrect_usage()
{
	printf("Incorrect usage.\nFor more help: ResourceCompiler.exe -h\n");

	return 0;
}
