#include "shell.h"

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(MY_info *info, char *str)
{
	char *p, c;
	int ret;

	p = MY_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = MY_delete_node_num(&(info->alias),
							   MY_get_node_index(info->alias, MY_node_str_start(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(MY_info *info, char *str)
{
	char *p;

	p = MY_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (MY_add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_s *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = MY_strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_MY_puts(p + 1);
		_MY_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * MY_alias_handler - mimics the alias builtin (man alias)
 * @info: contains simulated arguments for a function pointer,
 * allowing for a consistent function prototype
 *	Return: Always 0
 */
int MY_alias_handler(MY_info *info)
{
	int i = 0;
	char *p = NULL;
	list_s *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = MY_strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(MY_node_str_start(info->alias, info->argv[i], '='));
	}
	return (0);
}

/**
 * MY_change_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int MY_change_alias(MY_info *info)
{
	int i;
	list_s *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = MY_node_str_start(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = MY_strchr(node->str, '=');
		if (!p)
			return (0);
		p = MY_strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}

	return (1);
}
