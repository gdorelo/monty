#include "monty.h"

int num = 0;
int data_format = 0;
int exit_check = 0;

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
		dprintf(2, "USAGE: monty file\n"), exit(EXIT_FAILURE);
	file = argv[1];
	fp = fopen(file, "r");
	if (fp == NULL)
		dprintf(2, "Error: Can't open file %s\n", argv[1]), exit(EXIT_FAILURE);
	while (getline(&buf, &bufsize, fp) != -1)
	{
		token = strtok(buf, " \t\n");
		array[0] = token;
		if (!iscomment(array[0]))
		{
			line_number++;
			continue;
		}
		if (strcmp("push", array[0]) == 0)
		{
			token = strtok(NULL, " \t\n");
			array[1] = token;
			num = isnumber(array[1], line_number);
			exit_failure_check(buf, fp, head);
		}
		ptr = get_opcode_func(array[0]);
		if (ptr != NULL)
			(*ptr)(&head, line_number);
		else
			dprintf(2, "L%i: unknown instruction %s\n", (int)line_number, array[0]);
		exit_failure_check(buf, fp, head);
		line_number++;
	}
	free(buf), fclose(fp), free_stackt(head);
	return (0);
}
