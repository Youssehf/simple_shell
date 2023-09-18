#include "shell.h"

/**
 * MY_from_terminal - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if MY_from_terminal mode else 0
 */

int MY_from_terminal(MY_info *info)
{
	return (isatty(STDIN_FILENO) && info->fd_read <= 2);
}

/**
 * MY_isalpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic else 0 if not
 */

int MY_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * MY__atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string else converted integer
 */

int MY__atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}

/**
 * MY_is_delimiter - checks if a character is a delimiter
 * @c: Character to be checked.
 * @delimiters: String of charaters to be compated.
 *
 * This function compares a character to one or more of delimiters
 * to see if the character matches any of the delimiters.
 *
 * Return: True if it is a delimiter, else false.
 */

bool MY_is_delimiter(char c, char *delimiters)
{
	int s;

	for (s = 0; delimiters[s]; s++)
		if (c == delimiters[s])
			return (true);
	return (false);
}
