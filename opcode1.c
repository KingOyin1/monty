#include "monty.h"

/**
 *
 *
 *
 */
void f_push(stack_t **head, unsigned int number)
{
	stack_t *new_node;

	new_node = malloc(sizeof(stack_t));
	if (!new_node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		fclose(bus.file);
		free(bus.content);
		free_stack(*head);
		exit(EXIT_FAILURE);
	}
	new_node->n = number;
	new_node->next = NULL;
	if (*head == NULL)
	{
		new_node->prev = NULL;
		*head = new_node;
	}
	else
	{
		stack_t *last = *head;
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = new_node;
		new_node->prev = last;
	}
}

/**
 *
 *
 *
 */
void f_pall(stack_t **head, unsigned int counter)
{
	stack_t *h;
	
	(void)counter;
	h = *head;
	while (h != NULL && h->next != NULL)
	{
		h = h->next;
	}
	while (h != NULL)
	{
		printf("%d\n", h->n);
		h = h->prev;
	}
}
