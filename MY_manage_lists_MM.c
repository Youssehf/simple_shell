#include "shell.h"

/**
 * MY_add_node_start - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_s *MY_add_node_start(list_s **head, const char *str, int num)
{
	list_s *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_s));
	if (!new_head)
		return (NULL);
	MY_memset((void *)new_head, 0, sizeof(list_s));
	new_head->num = num;
	if (str)
	{
		new_head->str = MY_strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * MY_add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_s *MY_add_node_end(list_s **head, const char *str, int num)
{
	list_s *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_s));
	if (!new_node)
		return (NULL);
	MY_memset((void *)new_node, 0, sizeof(list_s));
	new_node->num = num;
	if (str)
	{
		new_node->str = MY_strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * MY_print_list_str - prints only the str element of a list_s linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t MY_print_list_str(const list_s *h)
{
	size_t i = 0;

	while (h)
	{
		_MY_puts(h->str ? h->str : "(nil)");
		_MY_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * MY_delete_node_num - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int MY_delete_node_num(list_s **head, unsigned int index)
{
	list_s *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * MY_free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void MY_free_list(list_s **head_ptr)
{
	list_s *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
