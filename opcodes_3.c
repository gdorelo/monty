#include "monty.h"


/**
 * mod_ - function that computes the rest of the division of
 * the second top element of the stack by the top element of the stack
 * @head: double pointer, pointer to a pointer to the head node
 * @line_number: index of the bytecode line where function is called
 * Return: void
 */

void mod_(stack_t **head, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (!(*head) || !((*head)->next))
	{
		dprintf(2, "L%i: can't mod, stack too short\n", line_number);
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
	temp->n %= (*head)->n;
	pop_(head, line_number);
}

/**
 * pchar_ - function that prints the char at the top of the stack
 * @head: double pointer, pointer to a pointer to the head node
 * @line_number: index of the bytecode line where function is called
 * Return: void
 */

void pchar_(stack_t **head, unsigned int line_number)
{
	if (!(*head))
	{
		dprintf(2, "L%i: can't pchar, stack empty\n", line_number);
		exit_check = 1;
		return;
	}
	if ((*head)->n > 127 || (*head)->n < 0)
	{
		dprintf(2, "L%i: can't pchar, value out of range\n", line_number);
		exit_check = 1;
		return;
	}
	printf("%c\n", (char)((*head)->n));
}

/**
 * pstr_ - function that prints the string starting at the top of the stack
 * @head: double pointer, pointer to a pointer to the head node
 * @line_number: index of the bytecode line where function is called
 * Return: void
 */

void pstr_(stack_t **head, unsigned int line_number)
{
	stack_t *temp = NULL;

	(void)line_number;
	if (*head)
	{
		temp = *head;
		while (temp != NULL && temp->n != 0 && temp->n <= 127 && temp->n >= 33)
		{
			printf("%c", (char)(temp->n));
			temp = temp->next;
		}
		printf("\n");
	}
	else
		printf("\n");
}

/**
 * rotl_ - function that rotates the stack to the top
 * @head: double pointer, pointer to a pointer to the head node
 * @line_number: index of the bytecode line where function is called
 * Return: void
 */

void rotl_(stack_t **head, unsigned int line_number)
{
	stack_t *temp = NULL;

	(void)line_number;
	if (!(*head) || !((*head)->next))
		return;
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = *head;
	(*head)->prev = temp;
	*head = (*head)->next;
	(*head)->prev->next = NULL;
	(*head)->prev = NULL;
}

/**
 * rotr_ - function that rotates the stack to the top
 * @head: double pointer, pointer to a pointer to the head node
 * @line_number: index of the bytecode line where function is called
 * Return: void
 */

void rotr_(stack_t **head, unsigned int line_number)
{
	stack_t *temp = NULL;

	(void)line_number;
	if (!(*head) || !((*head)->next))
		return;
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = *head;
	(*head)->prev = temp;
	temp->prev->next = NULL;
	temp->prev = NULL;
	*head = temp;
}
