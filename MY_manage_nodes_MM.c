#include "shell.h"
/**
 * MY_listlen - gets the length of linked list
 * @h: Pointer to first node.
 *
 * Return: Size of list.
 */
size_t MY_listlen(const list_s *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * MY_list_to_vector - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: Array of strings.
 */

char **MY_list_to_vector(list_s *head)
{
	list_s *node = head;
	size_t i = MY_listlen(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));

	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(MY__strlength(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		str = MY_strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * MY_print_list - prints all elements of a list_s linked list
 * @h: pointer to first node
 *
 * Return: Size of list
 */

size_t MY_print_list(const list_s *h)
{
	size_t i = 0;

	while (h)
	{
		_MY_puts(MY_change_base(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_MY_puts(h->str ? h->str : "(nil)");
		_MY_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * MY_node_str_start - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to check
 * @c: the next character after prefix to check
 *
 * Return: match node or null
 */

list_s *MY_node_str_start(list_s *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = MY_starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * MY_get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: -1 or index of node
 */

ssize_t MY_get_node_index(list_s *head, list_s *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
