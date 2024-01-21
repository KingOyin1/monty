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
	size_t read_line = 1;
	unsigned int counter = 0;

	while (read_line > 0)
	{
		content = NULL;
		read_line = getline(&content, &size, file);
		bus->content = content;
		counter++;
		if (read_line > 0)
		{
			execute(content, stack, counter, bus);
		}
		free(content);
	}
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
