#include "shell.h"
/**
 * MY_clear_info - initializes MY_info struct
 * @info: struct address
 */
void MY_clear_info(MY_info *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
 * MY_set_info - initializes MY_info struct
 * @info: struct address
 * @av: argument vector
 */
void MY_set_info(MY_info *info, char **av)
{
	int i = 0;

	info->prog_name = av[0];
	if (info->arg)
	{
		info->argv = MY_strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = MY_strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
		MY_change_alias(info);
		MY_change_v(info);
	}
}
/**
 * MY_free_info - frees MY_info struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void MY_free_info(MY_info *info, int all)
{
	MY_free_vector(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->sep_buff)
			free(info->arg);
		if (info->env)
			MY_free_list(&(info->env));
		if (info->history)
			MY_free_list(&(info->history));
		if (info->alias)
			MY_free_list(&(info->alias));
		MY_free_vector(info->environ);
		info->environ = NULL;
		MY_bfree((void **)info->sep_buff);
		if (info->fd_read > 2)
			close(info->fd_read);
		_putchar(NEG_ONE);
	}
}
