#pragma once

/*
* File name and path functions utilities
* 
* Example:
*
* str filename = "Temp/Resource.pack";
* 
*/

// Prototypes
str get_file_path(str filename);					// Returns: Temp
str get_file_path_with_last_slash(str filename);	// Returns: Temp/
str get_file_fullname(str filename);				// Returns: Resource.pack
str get_file_basename(str filename);				// Returns: Resource
str get_file_extension(str filename);				// Returns: pack
str get_file_extension_with_dot(str filename);		// Returns: .pack

// ---------------------------------------------------------------------------------------------------------------

// Returns: Temp
str get_file_path(str filename)
{
	// If filename is empty, return an empty string
	assert(filename != NULL);
	assert(filename != "");
	if (filename == NULL || filename == "")
		return ""; // Incorrect filename, returning an empty string.

	// Find the last slash in the filename
	size_t last_slash = 0;
	for (size_t i = 0; i < strlen(filename); i++)
	{
		if (filename[i] == '/' || filename[i] == '\\')
			last_slash = i;
	}

	// Create a string for the path to be returned
	str path = (str)malloc(last_slash);
	for (size_t i = 0; i < last_slash; i++)
	{
		path[i] = filename[i];
	}
	path[last_slash] = '\0';

	return path;
}

// Returns: Temp/
str get_file_path_with_last_slash(str filename)
{
	// If filename is empty, return an empty string
	assert(filename != NULL);
	assert(filename != "");
	if (filename == NULL || filename == "")
		return ""; // Incorrect filename, returning an empty string.

	// Find the last slash in the filename
	size_t last_slash = 0;
	for (size_t i = 0; i < strlen(filename); i++)
	{
		if (filename[i] == '/' || filename[i] == '\\')
			last_slash = i + 1;
	}

	// Create a string for the path to be returned
	str path = (str)malloc(last_slash);
	for (size_t i = 0; i < last_slash; i++)
	{
		path[i] = filename[i];
	}
	path[last_slash] = '\0';

	return path;
}

// Returns: Resource.pack
str get_file_fullname(str filename)
{
	// If filename is empty or null, return an empty string
	assert(filename != NULL);
	assert(filename != "");
	if (filename == NULL || filename == "")
		return ""; // Incorrect filename, returning an empty string.

	// Find the last slash in the filename
	size_t last_slash = 0;
	for (size_t i = 0; i < strlen(filename); i++)
	{
		if (filename[i] == '/' || filename[i] == '\\')
			last_slash = i + 1;
	}

	// Create a string for the full file name to be returned
	size_t fullname_length = strlen(filename) - last_slash;
	str fullname = (str)malloc(fullname_length);
	for (size_t i = 0; i < fullname_length; i++)
	{
		fullname[i] = filename[last_slash + i];
	}
	fullname[fullname_length] = '\0';

	return fullname;
}

// Returns: Resource
str get_file_basename(str filename)
{
	// If filename is empty or null, return an empty string
	assert(filename != NULL);
	assert(filename != "");
	if (filename == NULL || filename == "")
		return ""; // Incorrect filename, returning an empty string.

	// Find the last slash in the filename
	size_t last_slash = 0;
	for (size_t i = 0; i < strlen(filename); i++)
	{
		if (filename[i] == '/' || filename[i] == '\\')
			last_slash = i + 1;
	}

	// Search for the last dot in the filename
	size_t last_dot = 0;
	for (size_t i = 0; i < strlen(filename); i++)
	{
		if (filename[i] == '.')
			last_dot = i + 1;
	}

	// Create a string for the base file name to be returned
	size_t basename_length = last_dot - last_slash - 1;
	str basename = (str)malloc(basename_length);
	for (size_t i = 0; i < basename_length; i++)
	{
		basename[i] = filename[last_slash + i];
	}
	basename[basename_length] = '\0';

	return basename;
}

// Returns: pack
str get_file_extension(str filename)
{
	// If filename is empty or null, return an empty string
	assert(filename != NULL);
	assert(filename != "");
	if (filename == NULL || filename == "")
		return ""; // Incorrect filename, returning an empty string.

	// Search for the last dot in the filename
	size_t last_dot = 0;
	for (size_t i = 0; i < strlen(filename); i++)
	{
		if (filename[i] == '.')
			last_dot = i + 1;
	}

	// Create a string for the file extension to be returned
	size_t extension_length = strlen(filename) - last_dot;
	str extension = (str)malloc(extension_length);
	for (size_t i = 0; i < extension_length; i++)
	{
		extension[i] = filename[last_dot + i];
	}
	extension[extension_length] = '\0';

	return extension;
}

// Returns: .pack
str get_file_extension_with_dot(str filename)
{
	// If filename is empty or null, return an empty string
	assert(filename != NULL);
	assert(filename != "");
	if (filename == NULL || filename == "")
		return ""; // Incorrect filename, returning an empty string.

	// Search for the last dot in the filename
	size_t last_dot = 0;
	for (size_t i = 0; i < strlen(filename); i++)
	{
		if (filename[i] == '.')
			last_dot = i;
	}

	// Create a string for the file extension to be returned
	size_t extension_length = strlen(filename) - last_dot;
	str extension = (str)malloc(extension_length);
	for (size_t i = 0; i < extension_length; i++)
	{
		extension[i] = filename[last_dot + i];
	}
	extension[extension_length] = '\0';

	return extension;
}
