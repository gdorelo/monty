#include "monty.h"

int num = 0;
int data_format = 0;

/**
 * main - interpreter for Monty ByteCodes files
 * @argc: arguments count
 * @argv: arguments passed in the command line
 * Return: TBD
 */

int main(int argc, char **argv)
{
	char *buf = NULL, *file = NULL, *token = NULL, *array[2];
	size_t bufsize = 0, line_number = 1;
	FILE *fp = NULL;
	void (*ptr)();
	stack_t *head = NULL;

	if (argc != 2)
	{
		dprintf(2, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = argv[1];
	fp = fopen(file, "r");
	if (fp == NULL)
	{
		dprintf(2, "Error: Can't open file %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	while (getline(&buf, &bufsize, fp) != -1)
	{
		token = strtok(buf, " \t\n");
		array[0] = token;
		if (!iscomment(array[0]))
			break;
		token = strtok(NULL, " \t\n");
		array[1] = token;
		if (strcmp("push", array[0]) == 0)
			num = isnumber(array[1], line_number);
		ptr = get_opcode_func(array[0]);
		if (ptr != NULL)
			(*ptr)(&head, line_number);
		line_number++;
	}
	free(buf);
	fclose(fp);
	free_stackt(head);
/*	printf("return (0)"\n);*/
	return (0);
}

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
	return (NULL);
}

/**
 * isnumber - function that checks strings of digits
 * and converts the string to an integer if all characters are digits
 * @str: string passed from main (string pointed to by array[1])
 * @line_number: index of the bytecode line where function is called
 * Return: n, integer to be stored as global variable
 */

int isnumber(char *str, unsigned int line_number)
{
	int i = 0, n = 0;

	if (!str)
	{
		dprintf(2, "L%i: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	for (; str[i] != '\0'; i++)
		if (!isdigit(str[i]))
		{
			dprintf(2, "L%i: usage: push integer\n", line_number);
			exit(EXIT_FAILURE);
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
	if (*str == '#')
		return (0);
	return (1);
}

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
		exit(EXIT_FAILURE);
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
		exit(EXIT_FAILURE);
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
		exit(EXIT_FAILURE);
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

	if (!((*head)->next))
	{
		dprintf(2, "L%i: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp = (*head)->next;
	(*head)->next = temp->next;
	(*head)->prev = temp;
	temp->next = *head;
	temp->prev = NULL;
	*head = temp;
}

/**
 * add_ - function that adds the top two elements of the stack
 * @head: double pointer, pointer to a pointer to the head node
 * @line_number: index of the bytecode line where function is called
 * Return: void
 */

void add_(stack_t **head, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (!((*head)->next))
	{
		dprintf(2, "L%i: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
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

	if (!((*head)->next))
	{
		dprintf(2, "L%i: can't sub, stack too short\n", line_number);
		exit(EXIT_FAILURE);
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

	if (!((*head)->next))
	{
		dprintf(2, "L%i: can't div, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	if ((*head)->n == 0)
	{
		dprintf(2, "L%i: division by zero\n", line_number);
		exit(EXIT_FAILURE);
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

	if (!((*head)->next))
	{
		dprintf(2, "L%i: can't mul, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp = (*head)->next;
	temp->n *= (*head)->n;
	pop_(head, line_number);
}

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

	if (!((*head)->next))
	{
		dprintf(2, "L%i: can't mod, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	if ((*head)->n == 0)
	{
		dprintf(2, "L%i: division by zero\n", line_number);
		exit(EXIT_FAILURE);
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
	if (!*head || (*head)->n > 127 || (*head)->n < 0)
	{
		dprintf(2, "L%i: can't pchar, stack empty\n", line_number);
		exit(EXIT_FAILURE);
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
		while (temp != NULL && temp->n != 0 && temp->n <= 127 && temp->n >= 0)
		{
			printf("%c", (char)(temp->n));
			temp = temp->next;
		}
		printf("\n");
	}
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
	if (!((*head)->next))
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
	if (!((*head)->next))
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

/**
 * stack_ - function that sets the format of the data to a stack (LIFO)
 * @head: double pointer, pointer to a pointer to the head node
 * @line_number: index of the bytecode line where function is called
 * Return: void
 */

void stack_(stack_t **head, unsigned int line_number)
{
	(void)head;
	(void)line_number;
	data_format = 0;
}

/**
 * queue_ - function that sets the format of the data to a queue (FIFO)
 * @head: double pointer, pointer to a pointer to the head node
 * @line_number: index of the bytecode line where function is called
 * Return: void
 */

void queue_(stack_t **head, unsigned int line_number)
{
	(void)head;
	(void)line_number;
	data_format = 1;
}
