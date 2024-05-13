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
bool binary_file_write_i8(void* data, binary_file file);
bool binary_file_write_i16(void* data, binary_file file);
bool binary_file_write_i32(void* data, binary_file file);
bool binary_file_write_i64(void* data, binary_file file);
bool binary_file_write_u8(void* data, binary_file file);
bool binary_file_write_u16(void* data, binary_file file);
bool binary_file_write_u32(void* data, binary_file file);
bool binary_file_write_u64(void* data, binary_file file);
bool binary_file_write_byte(void* data, u64 size, binary_file file);
bool binary_file_write_str(str text, binary_file file);
bool binary_file_write_elements(void* data, u64 size, u64 count, binary_file file);
bool binary_file_read_i8(void* data, binary_file file);
bool binary_file_read_i16(void* data, binary_file file);
bool binary_file_read_i32(void* data, binary_file file);
bool binary_file_read_i64(void* data, binary_file file);
bool binary_file_read_u8(void* data, binary_file file);
bool binary_file_read_u16(void* data, binary_file file);
bool binary_file_read_u32(void* data, binary_file file);
bool binary_file_read_u64(void* data, binary_file file);
bool binary_file_read_byte(void* data, u64 size, binary_file file);
bool binary_file_read_str(str text, u64 size, binary_file file);
bool binary_file_read_elements(void* data, u64 size, u64 count, binary_file file);
bool binary_file_seek_begin(binary_file file);
bool binary_file_seek_position(file_size position, binary_file file);
bool binary_file_seek_end(binary_file file);
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
bool binary_file_write_i8(void* data, binary_file file)
{
	u32 number_of_elements = (u32)fwrite(data, sizeof(i8), 1, file);
	if (number_of_elements != 1)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'i16' data to a binary file
bool binary_file_write_i16(void* data, binary_file file)
{
	u32 number_of_elements = (u32)fwrite(data, sizeof(i16), 1, file);
	if (number_of_elements != 1)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'i32' data to a binary file
bool binary_file_write_i32(void* data, binary_file file)
{
	u32 number_of_elements = (u32)fwrite(data, sizeof(i32), 1, file);
	if (number_of_elements != 1)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'i64' data to a binary file
bool binary_file_write_i64(void* data, binary_file file)
{
	u32 number_of_elements = (u32)fwrite(data, sizeof(i64), 1, file);
	if (number_of_elements != 1)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'u8' data to a binary file
bool binary_file_write_u8(void* data, binary_file file)
{
	u32 number_of_elements = (u32)fwrite(data, sizeof(u8), 1, file);
	if (number_of_elements != 1)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'u16' data to a binary file
bool binary_file_write_u16(void* data, binary_file file)
{
	u32 number_of_elements = (u32)fwrite(data, sizeof(u16), 1, file);
	if (number_of_elements != 1)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'u32' data to a binary file
bool binary_file_write_u32(void* data, binary_file file)
{
	u32 number_of_elements = (u32)fwrite(data, sizeof(u32), 1, file);
	if (number_of_elements != 1)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'u64' data to a binary file
bool binary_file_write_u64(void* data, binary_file file)
{
	u32 number_of_elements = (u32)fwrite(data, sizeof(u64), 1, file);
	if (number_of_elements != 1)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'byte'(s) data to a binary file
bool binary_file_write_byte(void* data, u64 size, binary_file file)
{
	u32 number_of_elements = (u32)fwrite(data, sizeof(byte), size, file);
	if (number_of_elements != size)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'str' data to a binary file
bool binary_file_write_str(str text, binary_file file)
{
	u32 number_of_elements = (u32)fwrite(text, strlen(text), 1, file);
	if (number_of_elements != 1)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'elements'(s) data to a binary file (as typical fwrite())
bool binary_file_write_elements(void* data, u64 size, u64 count, binary_file file)
{
	u32 number_of_elements = (u32)fwrite(data, size, count, file);
	if (number_of_elements != count)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Read 'i8' data from a binary file
bool binary_file_read_i8(void* data, binary_file file)
{
	u32 number_of_elements = (u32)fread(data, sizeof(i8), 1, file); // Note: While technically fread returns size_t, we cap it to u32 (unlikely scenario)
	if (number_of_elements != 1)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'i16' data from a binary file
bool binary_file_read_i16(void* data, binary_file file)
{
	u32 number_of_elements = (u32)fread(data, sizeof(i16), 1, file); // Note: While technically fread returns size_t, we cap it to u32 (unlikely scenario)
	if (number_of_elements != 1)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'i32' data from a binary file
bool binary_file_read_i32(void* data, binary_file file)
{
	u32 number_of_elements = (u32)fread(data, sizeof(i32), 1, file); // Note: While technically fread returns size_t, we cap it to u32 (unlikely scenario)
	if (number_of_elements != 1)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'i64' data from a binary file
bool binary_file_read_i64(void* data, binary_file file)
{
	u32 number_of_elements = (u32)fread(data, sizeof(i64), 1, file); // Note: While technically fread returns size_t, we cap it to u32 (unlikely scenario)
	if (number_of_elements != 1)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'u8' data from a binary file
bool binary_file_read_u8(void* data, binary_file file)
{
	u32 number_of_elements = (u32)fread(data, sizeof(u8), 1, file); // Note: While technically fread returns size_t, we cap it to u32 (unlikely scenario)
	if (number_of_elements != 1)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'u16' data from a binary file
bool binary_file_read_u16(void* data, binary_file file)
{
	u32 number_of_elements = (u32)fread(data, sizeof(u16), 1, file); // Note: While technically fread returns size_t, we cap it to u32 (unlikely scenario)
	if (number_of_elements != 1)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'u32' data from a binary file
bool binary_file_read_u32(void* data, binary_file file)
{
	u32 number_of_elements = (u32)fread(data, sizeof(u32), 1, file); // Note: While technically fread returns size_t, we cap it to u32 (unlikely scenario)
	if (number_of_elements != 1)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'u64' data from a binary file
bool binary_file_read_u64(void* data, binary_file file)
{
	u32 number_of_elements = (u32)fread(data, sizeof(u64), 1, file); // Note: While technically fread returns size_t, we cap it to u32 (unlikely scenario)
	if (number_of_elements != 1)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'byte'(s) data from a binary file
bool binary_file_read_byte(void* data, u64 size, binary_file file)
{
	u32 number_of_elements = (u32)fread(data, sizeof(byte), size, file); // Note: While technically fread returns size_t, we cap it to u32 (unlikely scenario)
	if (number_of_elements != size)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'str' data from a binary file
bool binary_file_read_str(str text, u64 size, binary_file file)
{
	u32 number_of_elements = (u32)fread(text, size, 1, file);
	text[size] = '\0';
	if(number_of_elements != 1)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'elements'(s) data from a binary file
bool binary_file_read_elements(void* data, u64 size, u64 count, binary_file file)
{
	u64 number_of_elements = (u64)fread(data, size, count, file); // Note: While technically fread returns size_t, we cap it to u64 (unlikely scenario)
	if (number_of_elements != count)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Seek to the beginning of a binary file
bool binary_file_seek_begin(binary_file file)
{
	return (_fseeki64(file, 0, SEEK_SET) == 0); // Returns true if the seek returns 0 meaning that the seek was successful
}
// Seek to a specific position in a binary file
bool binary_file_seek_position(file_size position, binary_file file)
{
	return (_fseeki64(file, position, SEEK_CUR) == 0); // Returns true if the seek returns 0 meaning that the seek was successful
}
// Seek to the end of a binary file
bool binary_file_seek_end(binary_file file)
{
	return (_fseeki64(file, 0, SEEK_END) == 0); // Note: the regular fseek() supports only file sizes up to 2GB. This _fseeki64() supports up to 8 Exabytes.
}
// Close a binary file
void binary_file_close(binary_file file)
{
	fclose(file);
}
