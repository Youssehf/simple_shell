#include "shell.h"
/**
 * main - Entry point to shell program
 * @argc: Number of arguments passed into the shell executable.
 * @argv: Vector containing arguments passed.
 *
 * Return: 0 on success or 1 on failure.
 */
int main(int argc, char **argv)
{
	MY_info info[] = {SET_INFO};
	int fd = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(fd)
		: "r"(fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);

			if (errno == ENOENT)
			{
				MY_Print_err(argv[0]);
				MY_Print_err(": 0: Can't open ");
				MY_Print_err(argv[1]);
				MY_putchar_err('\n');
				MY_putchar_err(NEG_ONE);
				exit(127);
			}

			return (EXIT_FAILURE);
		}

		info->fd_read = fd;
	}

	MY_gather_env(info);
	MY_read_history(info);
	MY_shell(info, argv);

	return (EXIT_SUCCESS);
}
