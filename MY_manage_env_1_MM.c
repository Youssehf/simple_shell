#include "shell.h"

/**
 * MY_get_environ - Returns a copy of the environment variables as an array of strings.
 * @info: Structure containing the environment variables.
 *		  Used to maintain constant function prototype.
 * Return: The environment variables as an array of strings.
 */

char **MY_get_environ(MY_info *info)
{
	/* If the environment variables have not been set or have been changed, update them. */
	if (!info->environ || info->env_changed)
	{
		info->environ = MY_list_to_vector(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * MY_set_env - Adds or updates an environment variable.
 * @info: Structure containing the environment variables.
 *		  Used to maintain constant function prototype.
 * @var: The name of the environment variable to add or update.
 * @value: The value of the environment variable to add or update.
 * Return: 0 if the environment variable was successfully added or updated, else 1.
 */

int MY_set_env(MY_info *info, char *var, char *value)
{
	char *buf = NULL;
	list_s *node;
	char *p;

	/* Return 1 if either the variable name or value is not defined. */
	if (!var || !value)
		return (1);

	/* Allocate memory for the new environment variable. */
	buf = malloc(MY__strlength(var) + MY__strlength(value) + 2);
	if (!buf)
		return (1);

	/* Combine the variable name and value into a single string. */
	MY_strcpy(buf, var);
	MY_strcat(buf, "=");
	MY_strcat(buf, value);

	/* Loop through each environment variable. */
	node = info->env;
	while (node)
	{
		/* Check if the current variable matches the name to be added or updated. */
		p = MY_starts_with(node->str, var);
		if (p && *p == '=')
		{
			/* Replace the current variable with the new one. */
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}

		/* Move to the next variable in the list. */
		node = node->next;
	}

	/* Add the new variable to the end of the */
	MY_add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

/**
 * MY_unset_env - Removes an environment variable.
 * @info: Structure containing the environment variables.
 *		  Used to maintain constant function prototype.
 * @var: The name of the environment variable to remove.
 * Return: 1 if the environment variable was successfully removed, else 0.
 */
int MY_unset_env(MY_info *info, char *var)
{
	list_s *node = info->env;
	size_t index = 0;
	char *p;

	/* Return 0 if the environment variables or variable name are not defined. */
	if (!node || !var)
		return (0);

	/* Loop through each environment variable. */
	while (node)
	{
		/* Check if the current variable matches the name to be removed. */
		p = MY_starts_with(node->str, var);
		if (p && *p == '=')
		{
			/* Remove the current variable from the list. */
			info->env_changed = MY_delete_node_num(&(info->env), index);

			/* Reset the index and continue to the next variable. */
			index = 0;
			node = info->env;
			continue;
		}

		/* Move to the next variable in the list. */
		node = node->next;
		index++;
	}

	return (info->env_changed);
}
