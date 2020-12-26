#include "monty.h"


/**
 * free_stackt - function that frees a dlistint_t list
 * @head: pointer to head node passed from main
 * Return: void
 */

void free_stackt(stack_t *head)
{
	stack_t *temp = NULL;
	stack_t *prev = NULL;

	if (!head)
		return;

	temp = head;
	while (temp != NULL)
	{
		prev = temp;
		temp = temp->next;
		free(prev);
	}
}

/**
 * get_opcode_func - function that checks for opcodes and points to
 * the proper function pointer
 * @s: string passed from main (argv[0])
 * Return: NULL or pointer to the correct opcode function
 */

void (*get_opcode_func(char *s))(stack_t **stack, unsigned int line_number)
{
	instruction_t opc[] = {
		{"push", push_},
		{"pall", pall_},
		{"pint", pint_},
		{"pop", pop_},
		{"swap", swap_},
		{"add", add_},
		{"nop", nop_},
		{"sub", sub_},
		{"div", div_},
		{"mul", mul_},
		{"mod", mod_},
		{"pchar", pchar_},
		{"pstr", pstr_},
		{"rotl", rotl_},
		{"rotr", rotr_},
		{"stack", stack_},
		{"queue", queue_},
		{NULL, NULL}
	};
	int i = 0, res = 0;

	while (i < 17)
	{
		res = strcmp(s, opc[i].opcode);
		if (res == 0)
			return (opc[i].f);
		i++;
	}
	exit_check = 1;
	return (NULL);
}

/**
 * isnumber - function that checks strings of digits
 * and converts the string to an integer if all characters are digits
 * @str: string passed from main (string pointed to by array[1])
 * @line_number: index of the bytecode line where function is called
 * Return: n, integer to be stored as global variable, -1 if not integer
 */

int isnumber(char *str, unsigned int line_number)
{
	int i = 0, n = 0;

	if (!str)
	{
		dprintf(2, "L%i: usage: push integer\n", line_number);
		exit_check = 1;
		return (-1);
	}
	if (str[0] == '-')
		i = 1;
	for (; str[i] != '\0'; i++)
		if (!isdigit(str[i]))
		{
			dprintf(2, "L%i: usage: push integer\n", line_number);
			exit_check = 1;
			return (-1);
		}
	n = atoi(str);
	return (n);
}

/**
 * iscomment - function that treat a line as a comment
 * when the first non-space character of a line is #
 * @str: string passed from main (string pointed to by array[0])
 * Return: 0 when comment is found, 1 otherwise
 */

int iscomment(char *str)
{
	if (!str)
		return (0);
	if (*str == '#')
		return (0);
	return (1);
}

/**
 * exit_failure_check - function that frees and close(fp) before exiting
 * @buf: buffer created by getline for each line being read from file
 * @fp: pointer returned by fopen function
 * @head: pointer to head node passed from main
 * Return: void
 */

void exit_failure_check(char *buf, FILE *fp, stack_t *head)
{
	if (exit_check == 1)
	{
		free(buf);
		fclose(fp);
		free_stackt(head);
		exit(EXIT_FAILURE);
	}
}
