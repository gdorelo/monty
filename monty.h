#ifndef MONTY_H
#define MONTY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern int num;
extern int data_format;
extern int exit_check;

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

void free_stackt(stack_t *head);
void (*get_opcode_func(char *s))(stack_t **stack, unsigned int line_number);
int isnumber(char *str, unsigned int line_number);
int iscomment(char *str);
void exit_failure_check(char *buf, FILE *fp, stack_t *head);
void push_(stack_t **head, unsigned int line_number);
void pall_(stack_t **head, unsigned int line_number);
void pint_(stack_t **head, unsigned int line_number);
void pop_(stack_t **head, unsigned int line_number);
void swap_(stack_t **head, unsigned int line_number);
void add_(stack_t **head, unsigned int line_number);
void sub_(stack_t **head, unsigned int line_number);
void nop_(stack_t **head, unsigned int line_number);
void sub_(stack_t **head, unsigned int line_number);
void div_(stack_t **head, unsigned int line_number);
void mul_(stack_t **head, unsigned int line_number);
void mod_(stack_t **head, unsigned int line_number);
void pchar_(stack_t **head, unsigned int line_number);
void pstr_(stack_t **head, unsigned int line_number);
void rotl_(stack_t **head, unsigned int line_number);
void rotr_(stack_t **head, unsigned int line_number);
void stack_(stack_t **head, unsigned int line_number);
void queue_(stack_t **head, unsigned int line_number);

#endif
