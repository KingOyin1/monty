#include "monty.h"
#include <string.h>

bus_t bus;
/**
 *
 *
 */
void start_init(FILE *fd)
{
	bus.lifi = 1;
	bus.arg = NULL;
	bus.file = fd;
	bus.content = NULL;
}

/**
 *
 *
 *
 */
void parseArguments(int argc, char *argv[], FILE **file, bus_t *bus)
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	*file = fopen(argv[1], "r");
	if (!*file)
	{
		fprintf(stderr, "Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	start_init(*file);
	bus->file = *file;
}

/**
 *
 *
 *
 */
void processFile(FILE *file, stack_t **stack, bus_t *bus)
{
	char *content = NULL;
	size_t size = 0;
	unsigned int counter = 0;
	size_t initial_size = 128;
	size_t length;

	content = (char*)malloc(initial_size * sizeof(char));
	if (content ==NULL)
	{
		fprintf(stderr, "Memory allocation error");
		exit(EXIT_FAILURE);
	}
	while (fgets(content, size, file) != NULL)
	{
		bus->content = content;
		counter++;
		length = strlen(content);
		if (length > 0 && content[length -1] == '\n')
			content[length-1] = '\0';
		execute(content, stack, counter, bus);
	}
	free(content);
}

/**
 *
 *
 *
 */
void cleanup(FILE *file, stack_t *stack)
{
	free_stack(stack);
	fclose(file);
}

/**
 *
 *
 *
 *
 */
int main(int argc, char *argv[])
{
	FILE *file;
	stack_t *stack;
	bus_t bus;

	stack = NULL;
	parseArguments(argc, argv, &file, &bus);
	processFile(file, &stack, &bus);
	cleanup(file, stack);
	return 0;
}
