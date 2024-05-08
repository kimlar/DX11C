#pragma once

#include "Common.h"

// Prototypes
u32 resource_compiler_create(str resource_filename);
u32 resource_compiler_add(str item_filename, str resource_name);
u32 resource_compiler_remove(str item_filename, str resource_name);
u32 resource_compiler_list(str resource_filename);
u32 resource_compiler_help();
u32 resource_compiler_incorrect_usage();

// ---------------------------------------------------------------------------------------------------------------

// Create a new resource file (blank file)
u32 resource_compiler_create(str resource_filename)
{
	str file_path = get_file_path(resource_filename);
	str file_path_with_last_slash = get_file_path_with_last_slash(resource_filename);
	str file_fullname = get_file_fullname(resource_filename);
	str file_basename = get_file_basename(resource_filename);
	str file_extension = get_file_extension(resource_filename);
	str file_extension_with_dot = get_file_extension_with_dot(resource_filename);

	//...
	
	free(file_path);
	free(file_path_with_last_slash);
	free(file_fullname);
	free(file_basename);
	free(file_extension);
	free(file_extension_with_dot);
	return 0;
}

// Add a resource item to an existing resource file
u32 resource_compiler_add(str item_filename, str resource_name)
{
	return 0;
}

// Remove a resource item from an existing resource file
u32 resource_compiler_remove(str item_filename, str resource_name)
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
	printf("  -c Create a new blank resource file.\n");
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
