#include "shell.h"

/**
 * MY_read_hist - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *MY_read_hist(MY_info *info)
{
	char *buf, *dir;

	dir = MY_getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (MY__strlength(dir) + MY__strlength(HIST_FILE_NAME) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	MY_strcpy(buf, dir);
	MY_strcat(buf, "/");
	MY_strcat(buf, HIST_FILE_NAME);
	return (buf);
}

/**
 * MY_create_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int MY_create_history(MY_info *info)
{
	ssize_t fd;
	char *filename = MY_read_hist(info);
	list_s *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		MY_write_chars(node->str, fd);
		MY_Print_char('\n', fd);
	}
	MY_Print_char(NEG_ONE, fd);
	close(fd);
	return (1);
}

/**
 * MY_read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: hist_lines on success, 0 otherwise
 */
int MY_read_history(MY_info *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = MY_read_hist(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			MY_update_history(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		MY_update_history(info, buf + last, linecount++);
	free(buf);
	info->hist_lines = linecount;
	while (info->hist_lines-- >= HIST_SIZE_MAX)
		MY_delete_node_num(&(info->history), 0);
	MY_renumber_history(info);
	return (info->hist_lines);
}

/**
 * MY_update_history - adds entry to a history linked list
 * @info: contains simulated arguments for a function pointer,
 * @buf: buffer
 * @linecount: the history linecount, hist_lines
 *
 * Return: Always 0
 */
int MY_update_history(MY_info *info, char *buf, int linecount)
{
	list_s *node = NULL;

	if (info->history)
		node = info->history;
	MY_add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * MY_renumber_history - renumbers the history linked list after changes
 * @info: contains simulated arguments for a function pointer,
 *
 * Return: the new hist_lines
 */
int MY_renumber_history(MY_info *info)
{
	list_s *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->hist_lines = i);
}
