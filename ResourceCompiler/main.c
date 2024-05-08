#include "Common.h"
#include "ResourceCompiler.h"

int main(int argc, char** argv)
{
	// Create?
	if (argc == 3 && argv[1][0] == '-' && argv[1][1] == 'c')
		return resource_compiler_create(argv[2]);

	// Add?
	if (argc == 4 && argv[1][0] == '-' && argv[1][1] == 'a')
		return resource_compiler_add(argv[2], argv[3]);

	// Remove?
	if (argc == 4 && argv[1][0] == '-' && argv[1][1] == 'r')
		return resource_compiler_remove(argv[2], argv[3]);

	// List?
	if (argc == 3 && argv[1][0] == '-' && argv[1][1] == 'l')
		return resource_compiler_list(argv[2]);

	// Help?
	if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'h')
		return resource_compiler_help();

	// Incorrect usage
	return resource_compiler_incorrect_usage();
}
