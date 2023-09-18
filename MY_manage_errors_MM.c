#include "shell.h"
/**
 * err_num - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string,
 * converted integer else -1
 *
 */
int err_num(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}
/**
 * MY_print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string,
 * converted integer else -1
 */
void MY_print_error(MY_info *info, char *estr)
{
	MY_Print_err(info->prog_name);
	MY_Print_err(": ");
	MY_print_dec(info->lines, STDERR_FILENO);
	MY_Print_err(": ");
	MY_Print_err(info->argv[0]);
	MY_Print_err(": ");
	MY_Print_err(estr);
}
/**
 * MY_print_dec - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int MY_print_dec(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = MY_putchar_err;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{

		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;
	return (count);
}
/**
 * MY_change_base - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *MY_change_base(long int num, int base, int flags)
{
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	static char *array;
	static char buffer[50];

	if (!(flags & BAS_CHANGE_UNSIG) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & BAS_CHANGE_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * MY_commants_handler - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: 0;
 */

void MY_commants_handler(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
