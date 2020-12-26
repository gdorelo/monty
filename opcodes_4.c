#include "monty.h"


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
