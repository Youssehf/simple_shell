#include "shell.h"
/**
 * MY_Print_err - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void MY_Print_err(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		MY_putchar_err(str[i]);
		i++;
	}
}
/**
 * MY_putchar_err - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On failure, -1 is returned
 */
int MY_putchar_err(char c)
{
	static int i;
	static char buf[BUFFER_SIZE_WRITE];

	if (c == NEG_ONE || i >= BUFFER_SIZE_WRITE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != NEG_ONE)
		buf[i++] = c;
	return (1);
}
/**
 * MY_Print_char - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On failure, -1 is returned
 */
int MY_Print_char(char c, int fd)
{
	static int i;
	static char buf[BUFFER_SIZE_WRITE];

	if (c == NEG_ONE || i >= BUFFER_SIZE_WRITE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != NEG_ONE)
		buf[i++] = c;
	return (1);
}
/**
 * MY_write_chars - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int MY_write_chars(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += MY_Print_char(*str++, fd);
	}
	return (i);
}
