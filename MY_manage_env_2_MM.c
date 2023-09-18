#include "shell.h"

/**
 * MY_getenv - gets the value of an environ variable
 * @info: contains simulated arguments for a function pointer,
 * @name: env var name
 *
 * Return: the value
 */

char *MY_getenv(MY_info *info, const char *name)
{
	char *p;
	list_s *node = info->env;

	while (node)
	{
		p = MY_starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * MY_check_set_env - Checks if an environment variable has been set.
 * @info: contains simulated arguments for a function pointer,
 * allowing for a consistent function prototype
 *
 * Return: 0 if set, else 1.
 */

int MY_check_set_env(MY_info *info)
{
	if (info->argc != 3)
	{
		MY_Print_err("Incorrect number of arguements\n");
		return (1);
	}

	if (MY_set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * MY_check_unset_env - Remove an environment variable
 * @info: contains simulated arguments for a function pointer,
 * allowing for a consistent function prototype
 * Return: Always 0
 */
int MY_check_unset_env(MY_info *info)
{
	int i;

	if (info->argc == 1)
	{
		MY_Print_err("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		MY_unset_env(info, info->argv[i]);

	return (0);
}

/**
 * MY_gather_env - populates env linked list
 * @info: contains simulated arguments for a function pointer,
 * allowing for a consistent function prototype
 * Return: Always 0
 */
int MY_gather_env(MY_info *info)
{
	list_s *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		MY_add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

/**
 * MY_printenv - prints the current environment
 * @info: contains simulated arguments for a function pointer,
 * allowing for a consistent function prototype
 * Return: Always 0
 */
int MY_printenv(MY_info *info)
{
	MY_print_list_str(info->env);
	return (0);
}
