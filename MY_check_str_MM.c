#include "shell.h"
/**
 * MY_is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter else 0
 */
bool MY_is_chain(MY_info *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->sep_buff_kind = OR_FLAG;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->sep_buff_kind = AND_FLAG;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->sep_buff_kind = CHAIN_FLAG;
	}
	else
		return (false);
	*p = j;
	return (true);
}

/**
 * MY_check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void MY_check_chain(MY_info *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->sep_buff_kind == AND_FLAG)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->sep_buff_kind == OR_FLAG)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*p = j;
}

/**
 * MY_change_v - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int MY_change_v(MY_info *info)
{
	int i = 0;
	list_s *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!MY_strcmp(info->argv[i], "$?"))
		{
			MY_change_string(&(info->argv[i]),

						   MY_strdup(MY_change_base(info->status, 10, 0)));

			continue;
		}
		if (!MY_strcmp(info->argv[i], "$$"))
		{
			MY_change_string(&(info->argv[i]),

						   MY_strdup(MY_change_base(getpid(), 10, 0)));

			continue;
		}
		node = MY_node_str_start(info->env, &info->argv[i][1], '=');
		if (node)
		{
			MY_change_string(&(info->argv[i]),

						   MY_strdup(MY_strchr(node->str, '=') + 1));

			continue;
		}
		MY_change_string(&info->argv[i], MY_strdup(""));
	}
	return (0);
}
/**
 * MY_change_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int MY_change_string(char **old, char *new)
{
	free(*old);
	*old = new;

	return (1);
}
