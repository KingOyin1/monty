#ifndef MONTY
#define MONTY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

/**
 * struct stack_s - holds nodes of a linked list
 * @n: number of node
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 *
 *
 *
 *
 */
typedef struct bus_s
{
	char *arg;
	FILE *file;
	char *content;
	int lifi;
} bus_t;

extern bus_t bus;

/**
 * struct instruction_s - for holding monty instruction information/data
 * @opcode: The code e.g push
 *
 *
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;


void start_init(FILE *fd);
void cleanup(FILE *file, stack_t *stack);void processFile(FILE *file, stack_t **stack, bus_t *bus);
void parseArguments(int argc, char *argv[], FILE **file, bus_t *bus);
int execute(char *content, stack_t **head, unsigned int counter, bus_t *bus);
void free_stack(stack_t *head);

void cleaning(stack_t **head, bus_t *bus);
void executeFoundOpcode(instruction_t opcode, char *arg_str, stack_t **head, unsigned int counter, bus_t *bus);
char *parseOpcode(char *content);
instruction_t findOpcode(char *opcode);
/*void processFile(FILE file, stack_t **stack, bus_t bus);
void parseArguments(int argc, char *argv[], FILE *file, bus_t *bus);*/
void clean(stack_t **head, bus_t *bus);


void f_push(stack_t **head, unsigned int number);
void f_pall(stack_t **head, unsigned int number);

#endif /*MONTY*/
