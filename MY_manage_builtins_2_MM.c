#include "shell.h"

/**
 * MY_exit_handler - exits the shell
 * @info: contains simulated arguments for a function pointer,
 * allowing for a consistent function prototype
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */

int MY_exit_handler(MY_info *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = err_num(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			MY_print_error(info, "Illegal number: ");
			MY_Print_err(info->argv[1]);
			MY_putchar_err('\n');
			return (1);
		}
		info->error_code = err_num(info->argv[1]);
		return (-2);
	}
	info->error_code = -1;
	return (-2);
}
/**
 * MY_cd_handler - changes the current directory of the process
 * @info: contains simulated arguments for a function pointer,
 *		  allowing for a consistent function prototype
 *
 * Return: 0
 */

int MY_cd_handler(MY_info *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_MY_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = MY_getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = MY_getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (MY_strcmp(info->argv[1], "-") == 0)
	{
		if (!MY_getenv(info, "OLDPWD="))
		{
			_MY_puts(s);
			_putchar('\n');
			return (1);
		}
		_MY_puts(MY_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = MY_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);

	if (chdir_ret == -1)
	{
		MY_print_error(info, "can't cd to ");
		MY_Print_err(info->argv[1]), MY_putchar_err('\n');
	}
	else
	{
		MY_set_env(info, "OLDPWD", MY_getenv(info, "PWD="));
		MY_set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * MY_help_handler - prints a message for aa function not implemented
 * @info:	contains simulated arguments for a function pointer,
 *			constant function prototype.
 * Return: 0
 */

int MY_help_handler(MY_info *info)
{
	char **arg_array;

	arg_array = info->argv;
	_MY_puts("help call works. Function not yet implemented \n");
	if (0)
		_MY_puts(*arg_array);

	return (0);
}

/**
 * MY_history_handler - displays the history list, one command by line, preceded
 *					with line numbers, starting at 0.
 * @info: contains simulated arguments for a function pointer,
 *		  constant function prototype.
 *	Return: Always 0
 */

int MY_history_handler(MY_info *info)
{
	MY_print_list(info->history);

	return (0);
}
