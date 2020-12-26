#include "monty.h"


/**
 * push_ - function that pushes a node to the head of the stack
 * @head: double pointer, pointer to a pointer to the head node
 * @line_number: index of the bytecode line where function is called
 * Return: void
 */

void push_(stack_t **head, unsigned int line_number)
{
	stack_t *new_node = NULL;
	stack_t *temp = NULL;

	(void)line_number;
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		dprintf(2, "Error: malloc failed\n");
		exit_check = 1;
		return;
	}
	new_node->n = num;
	new_node->prev = NULL;
	new_node->next = NULL;

	if (*head == NULL)
		*head = new_node;
	else
	{
		if (data_format == 0)
		{
			new_node->next = *head;
			(*head)->prev = new_node;
			*head = new_node;
		}
		else if (data_format == 1)
		{
			temp = *head;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = new_node;
			new_node->prev = temp;
		}
	}
}

/**
 * pall_ - function that prints all the values on the stack,
 * starting from the top of the stack
 * @head: double pointer, pointer to a pointer to the head node
 * @line_number: index of the bytecode line where function is called
 * Return: void
 */

void pall_(stack_t **head, unsigned int line_number)
{
	stack_t *temp = NULL;

	(void)line_number;
	if (*head)
	{
		temp = *head;
		while (temp != NULL)
		{
			printf("%i\n", temp->n);
			temp = temp->next;
		}
	}
}

/**
 * pint_ - function that prints the value at the top of the stack
 * @head: double pointer, pointer to a pointer to the head node
 * @line_number: index of the bytecode line where function is called
 * Return: void
 */

void pint_(stack_t **head, unsigned int line_number)
{
	if (!*head)
	{
		dprintf(2, "L%i: can't pint, stack empty\n", line_number);
		exit_check = 1;
		return;
	}
	printf("%i\n", (*head)->n);
}

/**
 * pop_ - function that removes the top element of the stack
 * @head: double pointer, pointer to a pointer to the head node
 * @line_number: index of the bytecode line where function is called
 * Return: void
 */

void pop_(stack_t **head, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (!*head)
	{
		dprintf(2, "L%i: can't pop an empty stack\n", line_number);
		exit_check = 1;
		return;
	}
	temp = *head;
	*head = (*head)->next;
	if (*head != NULL)
	{
		(*head)->prev = NULL;
		temp->next = NULL;
	}
	free(temp);
}

/**
 * swap_ - function that swaps the top two elements of the stack
 * @head: double pointer, pointer to a pointer to the head node
 * @line_number: index of the bytecode line where function is called
 * Return: void
 */

void swap_(stack_t **head, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (!(*head) || !((*head)->next))
	{
		dprintf(2, "L%i: can't swap, stack too short\n", line_number);
		exit_check = 1;
		return;
	}
	temp = (*head)->next;
	(*head)->next = temp->next;
	(*head)->prev = temp;
	temp->next = *head;
	temp->prev = NULL;
	*head = temp;
}
