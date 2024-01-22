#include "monty.h"

/**
 *
 *
 */
char *parseOpcode(char *content, stack_t **head, bus_t *bus)
{
	char *opcode = strtok(content, " \t\n");
	if (opcode == NULL || opcode[0] == '#')
	{
		cleaning(head, bus);
		return (NULL);
	}
	return (opcode);
}

/**
 *
 *
 *
 */
void cleaning(stack_t **head, bus_t *bus)
{
	fclose(bus->file);
	free(bus->content);
	free_stack(*head);
	exit(EXIT_FAILURE);
}

/**
 *
 *
 *
 */
int execute(char *content, stack_t **head, unsigned int counter, bus_t *bus)
{
	char *opcode;
	char *arg_str;
	instruction_t foundOpcode;

	opcode = parseOpcode(content, head, bus);
	if (opcode == NULL)
		return 0;
	arg_str = strtok(NULL, " \t\n");
	foundOpcode = findOpcode(opcode);
	if(foundOpcode.f == NULL)
	{
		fprintf(stderr, "L%u: unknown instruction %s\n", counter, opcode);
		cleaning(head, bus);
	}
	executeFoundOpcode(foundOpcode, arg_str, head, counter, bus);
	return 0;
}

/**
 *
 *
 *
 *
 */
instruction_t findOpcode(char *opcode)
{
	int i;

	instruction_t opcodes[] = {
		{"push", f_push},
		{"pall", f_pall},
		{NULL, NULL}
	};
	for (i = 0;  opcodes[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, opcodes[i].opcode) == 0)
		{
			return (opcodes[i]);
		}
	}
	return (instruction_t){NULL, NULL};
}

/**
 *
 *
 *
 */
void executeFoundOpcode(instruction_t opcode, char *arg_str, stack_t **head, unsigned int counter, bus_t *bus)
{
	int arg_value;

	if (strcmp(opcode.opcode, "push") == 0)
	{
		if (arg_str == NULL)
		{
			fprintf(stderr, "L%u: push requires an argument\n", counter);
			cleaning(head, bus);
		}
		arg_value = atoi(arg_str);
		opcode.f(head, arg_value);
	}
	else
	{
		opcode.f(head, counter);
	}
}
