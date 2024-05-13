#pragma once

/*
* File data functions utilities for binary and text files (read and write data)
* 
* TODO: Implement text file
* 
*/

// Types
typedef FILE* binary_file;
typedef FILE* text_file;
typedef u64 file_size;

// Prototypes: Binary file
binary_file binary_file_write_new(str filename);
binary_file binary_file_write_append(str filename);
binary_file binary_file_read(str filename);
file_size binary_file_get_size(str filename);
void binary_file_write_i8(void* data, binary_file file);
void binary_file_write_i16(void* data, binary_file file);
void binary_file_write_i32(void* data, binary_file file);
void binary_file_write_i64(void* data, binary_file file);
void binary_file_write_u8(void* data, binary_file file);
void binary_file_write_u16(void* data, binary_file file);
void binary_file_write_u32(void* data, binary_file file);
void binary_file_write_u64(void* data, binary_file file);
void binary_file_write_byte(void* data, u64 size, binary_file file);
void binary_file_write_str(str text, binary_file file);
void binary_file_write_elements(void* data, u64 size, u64 count, binary_file file);
void binary_file_close(binary_file file);

// Prototypes: Text file
/*
text_file text_file_write_new(str filename);
text_file text_file_write_append(str filename);
text_file text_file_read(str filename);
file_size text_file_get_size(str filename);
void text_file_close(binary_file file);
*/

// Open a binary file for writing in truncate mode.
binary_file binary_file_write_new(str filename)
{
	// Create a binary file. Truncate the file if it already exists.
	binary_file file = fopen(filename, "wb");

	return file;
}
// Open a binary file for writing in append mode.
binary_file binary_file_write_append(str filename)
{
	// Open a binary file in append mode.
	binary_file file = fopen(filename, "ab");

	return file;
}
// Open a binary file for reading in binary mode.
binary_file binary_file_read(str filename)
{
	// Read a binary file in binary mode.
	binary_file file = fopen(filename, "rb");

	return file;
}
// Get the size of a binary file
file_size binary_file_get_size(str filename)
{
	binary_file file = binary_file_read(filename);
	if (file == NULL)
	{
		printf("Error: Failed to open item file: %s\n", filename);
		return 0; // Return 0 if the binary file is not found
	}

	fseek(file, 0, SEEK_END);
	file_size data_size = ftell(file);

	binary_file_close(file);

	return data_size; // Return the data size of the binary file
}
// Write 'i8' data to a binary file
void binary_file_write_i8(void* data, binary_file file)
{
	fwrite(data, sizeof(i8), 1, file);
}
// Write 'i16' data to a binary file
void binary_file_write_i16(void* data, binary_file file)
{
	fwrite(data, sizeof(i16), 1, file);
}
// Write 'i32' data to a binary file
void binary_file_write_i32(void* data, binary_file file)
{
	fwrite(data, sizeof(i32), 1, file);
}
// Write 'i64' data to a binary file
void binary_file_write_i64(void* data, binary_file file)
{
	fwrite(data, sizeof(i64), 1, file);
}
// Write 'u8' data to a binary file
void binary_file_write_u8(void* data, binary_file file)
{
	fwrite(data, sizeof(u8), 1, file);
}
// Write 'u16' data to a binary file
void binary_file_write_u16(void* data, binary_file file)
{
	fwrite(data, sizeof(u16), 1, file);
}
// Write 'u32' data to a binary file
void binary_file_write_u32(void* data, binary_file file)
{
	fwrite(data, sizeof(u32), 1, file);
}
// Write 'u64' data to a binary file
void binary_file_write_u64(void* data, binary_file file)
{
	fwrite(data, sizeof(u64), 1, file);
}
// Write 'byte'(s) data to a binary file
void binary_file_write_byte(void* data, u64 size, binary_file file)
{
	fwrite(data, sizeof(byte), size, file);
}
// Write 'str' data to a binary file
void binary_file_write_str(str text, binary_file file)
{
	fwrite(text, sizeof(str), 1, file);
}
// Write 'elements'(s) data to a binary file (as typical fwrite())
void binary_file_write_elements(void* data, u64 size, u64 count, binary_file file)
{
	fwrite(data, size, count, file);
}
// Close a binary file
void binary_file_close(binary_file file)
{
	fclose(file);
}
