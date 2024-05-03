#pragma once

#include <stdio.h>
#include <stdlib.h>

unsigned char* file_system_read_binary(const char* file_name, unsigned int memory_size)
{
	unsigned char* memory_data;
	FILE* fp = fopen(file_name, "rb");
	if (fp == NULL)
	{
		printf("ERROR: Could not open file.\n");
		exit(1);
		// TODO(kim): implement logging
	}

	fseek(fp, 0, SEEK_END);
	memory_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	memory_data = (unsigned char*)malloc(memory_size);
	if (memory_size != fread(memory_data, sizeof(char), memory_size, fp))
	{
		free(memory_data);
		exit(1);
		// TODO(kim): implement logging
	}
	fclose(fp);

	return memory_data;
}