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
		// Image properties
		u32 image_width = 0;
		u32 image_height = 0;
		u32 image_numChannels = 0;

		// Get the image data, width and height
		byte* image_data = image_png_load_file(item_filename, &image_width, &image_height, &image_numChannels);
		if (image_data == NULL)
		{
			printf("Error: Failed to load image file: %s\n", item_filename);
			return 1;
		}

		// Get the data type
		data_type = Unknown_ImageResourceType;
		if (image_numChannels == 4)
		{
			data_type = RGBA_U8_ImageResourceType;
		}

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
	// Open the resource file
	binary_file resource_file = binary_file_read(resource_filename);
	if (resource_file == NULL)
	{
		printf("Error: Failed to open resource file: %s\n", resource_filename);
		return 1; // Failed!
	}

	// Get the size of the resource file
	file_size resource_file_size = binary_file_get_size(resource_filename);
	if (resource_file_size == 0)
		return 0;

	// Loop through all resource items in the resource file
	file_size i_begin = 0;
	file_size i_end = 0;
	for (file_size i = 0; i < resource_file_size;)
	{
		// Keep the beginning position index of the current resource item in the resource file
		i_begin = i;

		// Get header size
		u32 header_size = 0;
		if (!binary_file_read_u32(&header_size, resource_file))
		{
			printf("Error: Failed to read header size in resource file: %s\n", resource_filename);
			return 1; // Failed!
		}
		i += sizeof(header_size);

		// Get data size
		file_size data_size = 0;
		if (!binary_file_read_u64(&data_size, resource_file))
		{
			printf("Error: Failed to read data size in resource file: %s\n", resource_filename);
			return 1; // Failed!
		}
		i += sizeof(data_size);

		// Get data type
		u32 data_type = 0;
		if (!binary_file_read_u32(&data_type, resource_file))
		{
			printf("Error: Failed to read data type in resource file: %s\n", resource_filename);
			return 1; // Failed!
		}
		i += sizeof(data_type);

		// Get data name
		u32 data_name_length = header_size - sizeof(header_size) - sizeof(data_size) - sizeof(data_type);
		if (data_name_length == 0)
		{
			printf("Error: Failed to read data name length in resource file: %s\n", resource_filename);
			return 1; // Failed!
		}
		str data_name = malloc(data_name_length);
		if (!binary_file_read_str(data_name, data_name_length, resource_file))
		{
			printf("Error: Failed to read data name in resource file: %s\n", resource_filename);
			return 1; // Failed!
		}
		i += data_name_length;

		// Did we find the item?
		if (strcmp(data_name, get_file_basename(item_filename)) == 0)
		{
			if (data_type == get_resource_type(get_file_extension(item_filename)))
			{
				printf("Removing item: %s.%s\n", data_name, get_resource_type_name(data_type));

				// Keep the end position index of the current resource item in the resource file
				i_end = i + data_size;

				file_size bin_data_size = resource_file_size - (i_end - i_begin);
				byte* bin_data = malloc(bin_data_size);
				if (bin_data == NULL)
				{
					printf("Error: Failed to allocate memory for writing data to the resource file: %s\n", resource_filename);
					return 1; // Failed!
				}

				binary_file_set_position_begin(resource_file);

				// part1 bin_data[0-32838]
				// part2 bin_data[295012-14467349]
				// delta_size = 295012 - 32838 = 262174 (size of tile03 RGBA_U8 image + header size + ...)
				// new_bin_data_size = 14467349 - (295012 - 32838) = 14205175
				//13943000
				printf("resource_file_size: %llu\n", resource_file_size);
				printf("i_begin: %llu\n", i_begin);
				printf("i_end: %llu\n", i_end);
				printf("i_end - i_begin: %llu\n", i_end - i_begin);
				printf("bin_data_size: %llu\n", bin_data_size);

				for (file_size j = 0; j < i_begin; j++)
				{
					if (!binary_file_read_byte(&bin_data[j], 1, resource_file))
					{
						printf("Error: Failed to read data in resource file: %s\n", resource_filename);
						return 1; // Failed!
					}
				}

				binary_file_set_position(i_end, resource_file);

				for (file_size j = i_end; j < bin_data_size; j++)
				{
					if (!binary_file_read_byte(&bin_data[j - (i_end - i_begin)], 1, resource_file))
					{
						printf("Error: Failed to read data in resource file: %s\n", resource_filename);
						return 1; // Failed!
					}
				}



				//binary_file_set_position((i_end-i_begin), resource_file);

				/*
				for (file_size j = i_end; j < bin_data_size; j++)
				{
					if (!binary_file_read_byte(&bin_data[j], 1, resource_file))
					{
						printf("Error: Failed to read data in resource file: %s\n", resource_filename);
						return 1; // Failed!
					}
				}
				*/

				// Close the resource file
				binary_file_close(resource_file);

				//binary_file new_resource_file = binary_file_write_new(resource_filename);
				binary_file new_resource_file = binary_file_write_new("temp.bin");
				if (new_resource_file == NULL)
				{
					printf("Error: Failed to create new resource file: %s\n", resource_filename);
					return 1; // Failed!
				}

				//for (file_size j = 0; j < i_begin; j++)
				for (file_size j = 0; j < bin_data_size; j++)
				{
					if (!binary_file_write_byte(&bin_data[j], 1, new_resource_file))
					{
						printf("Error: Failed to write data in resource file: %s\n", resource_filename);
						return 1; // Failed!
					}
				}


				// Close the new resource file
				binary_file_close(new_resource_file);


				printf("Done\n");

				return 0; // Finish with the job
			}
		}

		// Clean up
		free(data_name);

		// Jump to next item in the resource file
		if (!binary_file_set_position_relative(data_size, resource_file))
		{
			printf("Error: Failed to jump to next item in resource file: %s\n", resource_filename);
			return 1; // Failed!
		}
		i += data_size;
	}

	// Close the resource file
	binary_file_close(resource_file);

	return 0;
}

// List all resource items in an existing resource file
u32 resource_compiler_list(str resource_filename)
{
	// Open the resource file
	binary_file resource_file = binary_file_read(resource_filename);
	if (resource_file == NULL)
	{
		printf("Error: Failed to open resource file: %s\n", resource_filename);
		return 1; // Failed!
	}

	// Get the size of the resource file
	file_size resource_file_size = binary_file_get_size(resource_filename);
	if (resource_file_size == 0)
		return 0;

	// Loop through all resource items in the resource file
	for (file_size i = 0; i < resource_file_size;)
	{
		// Get header size
		u32 header_size = 0;
		if (!binary_file_read_u32(&header_size, resource_file))
		{
			printf("Error: Failed to read header size in resource file: %s\n", resource_filename);
			return 1; // Failed!
		}
		i += sizeof(header_size);

		// Get data size
		file_size data_size = 0;
		if (!binary_file_read_u64(&data_size, resource_file))
		{
			printf("Error: Failed to read data size in resource file: %s\n", resource_filename);
			return 1; // Failed!
		}
		i += sizeof(data_size);

		// Get data type
		u32 data_type = 0;
		if (!binary_file_read_u32(&data_type, resource_file))
		{
			printf("Error: Failed to read data type in resource file: %s\n", resource_filename);
			return 1; // Failed!
		}
		i += sizeof(data_type);

		// Get data name
		u32 data_name_length = header_size - sizeof(header_size) - sizeof(data_size) - sizeof(data_type);
		if (data_name_length == 0)
		{
			printf("Error: Failed to read data name length in resource file: %s\n", resource_filename);
			return 1; // Failed!
		}
		str data_name = malloc(data_name_length);
		if (!binary_file_read_str(data_name, data_name_length, resource_file))
		{
			printf("Error: Failed to read data name in resource file: %s\n", resource_filename);
			return 1; // Failed!
		}
		i += data_name_length;

		// List current item
		printf("%s.%s\n", data_name, get_resource_type_name(data_type));
		
		// Clean up
		free(data_name);

		// Jump to next item in the resource file
		if (!binary_file_set_position_relative(data_size, resource_file))
		{
			printf("Error: Failed to jump to next item in resource file: %s\n", resource_filename);
			return 1; // Failed!
		}
		i += data_size;
	}

	binary_file_close(resource_file);

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
