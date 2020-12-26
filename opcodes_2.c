#include "monty.h"


/**
 * add_ - function that adds the top two elements of the stack
 * @head: double pointer, pointer to a pointer to the head node
 * @line_number: index of the bytecode line where function is called
 * Return: void
 */

void add_(stack_t **head, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (!(*head) || !((*head)->next))
	{
		dprintf(2, "L%i: can't add, stack too short\n", line_number);
		exit_check = 1;
		return;
	}
	temp = (*head)->next;
	temp->n += (*head)->n;
	pop_(head, line_number);
}

/**
 * nop_ - function that "doesn’t do anything"
 * @head: double pointer, pointer to a pointer to the head node
 * @line_number: index of the bytecode line where function is called
 * Return: void
 */

void nop_(stack_t **head, unsigned int line_number)
{
	(void)head;
	(void)line_number;
}

/**
 * sub_ - function that subtracts the top element of the stack
 * from the second top element
 * @head: double pointer, pointer to a pointer to the head node
 * @line_number: index of the bytecode line where function is called
 * Return: void
 */

void sub_(stack_t **head, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (!(*head) || !((*head)->next))
	{
		dprintf(2, "L%i: can't sub, stack too short\n", line_number);
		exit_check = 1;
		return;
	}
	temp = (*head)->next;
	temp->n -= (*head)->n;
	pop_(head, line_number);
}

/**
 * div_ - function that divides the second top element of the stack
 * by the top element of the stack
 * @head: double pointer, pointer to a pointer to the head node
 * @line_number: index of the bytecode line where function is called
 * Return: void
 */

void div_(stack_t **head, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (!(*head) || !((*head)->next))
	{
		dprintf(2, "L%i: can't div, stack too short\n", line_number);
		exit_check = 1;
		return;
	}
	if ((*head)->n == 0)
	{
		dprintf(2, "L%i: division by zero\n", line_number);
		exit_check = 1;
		return;
	}
	temp = (*head)->next;
	temp->n /= (*head)->n;
	pop_(head, line_number);
}

/**
 * mul_ - function that multiplies the second top element of the stack
 * with the top element of the stack
 * @head: double pointer, pointer to a pointer to the head node
 * @line_number: index of the bytecode line where function is called
 * Return: void
 */

void mul_(stack_t **head, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (!(*head) || !((*head)->next))
	{
		dprintf(2, "L%i: can't mul, stack too short\n", line_number);
		exit_check = 1;
		return;
	}
	temp = (*head)->next;
	temp->n *= (*head)->n;
	pop_(head, line_number);
}
