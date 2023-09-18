#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <math.h>
#include <dirent.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>

#define BUFFER_SIZE_READ 1024
#define BUFFER_SIZE_WRITE 1024
#define MAX_WORD_COUNT 100
#define NEG_ONE -1
#define REG_FLAG 0
#define OR_FLAG 1
#define AND_FLAG 2
#define CHAIN_FLAG 3
#define BAS_CHANGE_LOWER 1
#define BAS_CHANGE_UNSIG 2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE_NAME ".ss_history"
#define HIST_SIZE_MAX 4096
#define SET_INFO							\
	{										\
		NULL, NULL, NULL, 0, 0, 0, 0,		\
		NULL, NULL, NULL, NULL, NULL,		\
		0, 0, NULL, 0, 0, 0					\
	}

extern char **environ;

/**
 * struct ListNode - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct ListNode
{
	int num;
	char *str;
	struct ListNode *next;
} list_s;

/**
 * struct InfoNode - contains simulated arguments for a function pointer,
 *					 allowing for a consistent function prototype
 * @arg: a string generated from getline that holds arguments
 * @argv: an array of strings generated from @arg
 * @path: the path string for the current command
 * @argc: the number of arguments
 * @lines: the number of errors encountered
 * @error_code: the exit() error code
 * @lc_flag: a flag indicating whether this line of input should be counted
 * @prog_name: the name of the program's file
 * @env: a linked list representing a local copy of the environment variables
 * @environ: a custom-modified copy of the environ from the linked list env
 * @history: the node for the command history
 * @alias: the node for the command alias
 * @env_changed: a flag that indicates whether environ has been changed
 * @status: the return status of the most recent executed command
 * @sep_buff: the address of the pointer to sep_buff, used for chaining
 * @sep_buff_kind: the type of command buffer (CMD_type ||, &&, ;)
 * @fd_read: the file descriptor used for reading line input
 * @hist_lines: the number of lines in the history
 */

typedef struct InfoNode
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	size_t lines;
	int error_code;
	int lc_flag;
	char *prog_name;
	list_s *env;
	list_s *history;
	list_s *alias;
	char **environ;
	int env_changed;
	int status;

	char **sep_buff;
	int sep_buff_kind;
	int fd_read;
	int hist_lines;
} MY_info;

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(MY_info *);
} builtin_commands;

int MY_shell(MY_info *info, char **av);
int MY_Print_char(char c, int fd);
int MY_write_chars(char *str, int fd);
int MY__strlength(char *s);
int MY_strcmp(char *s1, char *s2);
int MY_putchar_err(char);
int _putchar(char);
int MY_isalpha(int);
int MY__atoi(char *);
int err_num(char *);
int MY_exit_handler(MY_info *);
int MY_cd_handler(MY_info *);
int MY_help_handler(MY_info *);
int MY_history_handler(MY_info *);
int MY_alias_handler(MY_info *);
int MY_new_getline(MY_info *, char **, size_t *);
int MY_printenv(MY_info *);
int MY_check_set_env(MY_info *);
int MY_check_unset_env(MY_info *);
int MY_unset_env(MY_info *, char *);
int MY_set_env(MY_info *, char *, char *);
void MY_Print_err(char *);
void _MY_puts(char *);
char *MY_strcat(char *, char *);
char *MY_strcpy(char *, char *);
char *MY_strdup(const char *);
char *MY_strncpy(char *, char *, int);
char *MY_strncat(char *, char *, int);
char *MY_strchr(char *, char);
char *MY_memset(char *, char, unsigned int);
void *MY_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *MY_getenv(MY_info *, const char *);
char *MY_starts_with(const char *, const char *);
char *MY_dup_chars(char *, int, int);
char *MY_check_file_in_path(MY_info *info, char *pathstr, char *cmd);
char *MY_change_base(long int, int, int);
char *MY_read_hist(MY_info *info);
char **MY_get_environ(MY_info *);
char **MY_strtow(char *, char *);
char **MY_list_to_vector(list_s *);
void MY_check_command(MY_info *);
void MY_create_process(MY_info *);
void MY_handle_sigint(int);
void MY_clear_info(MY_info *);
void MY_set_info(MY_info *, char **);
void MY_free_info(MY_info *, int);
void MY_free_vector(char **);
void MY_print_error(MY_info *, char *);
void MY_commants_handler(char *);
void MY_free_list(list_s **);
void MY_check_chain(MY_info *info, char *buf, size_t *p, size_t i, size_t len);
int MY_handle_builtin(MY_info *);
bool MY_is_executable(MY_info *, char *);
int MY_bfree(void **);
int MY_from_terminal(MY_info *);
int MY_print_dec(int, int);
int MY_gather_env(MY_info *);
int MY_create_history(MY_info *info);
int MY_read_history(MY_info *info);
int MY_update_history(MY_info *info, char *buf, int linecount);
int MY_renumber_history(MY_info *info);
int MY_loophsh(char **);
int MY_delete_node_num(list_s **, unsigned int);
bool MY_is_chain(MY_info *, char *, size_t *);
int MY_change_alias(MY_info *);
int MY_change_v(MY_info *);
int MY_change_string(char **, char *);
list_s *MY_add_node_start(list_s **head, const char *str, int num);
list_s *MY_add_node_end(list_s **head, const char *str, int num);
list_s *MY_node_str_start(list_s *, char *, char);
size_t MY_print_list_str(const list_s *);
size_t MY_listlen(const list_s *);
size_t MY_print_list(const list_s *);
ssize_t MY_get_input(MY_info *);
ssize_t MY_get_node_index(list_s *, list_s *);
char **MY_split_string(char *str, char *separators, size_t *word_count);
int MY_words_count(char *str, char *separators, unsigned int *arr);
void MY_set_zeros(unsigned int *arr, size_t size);
void MY_set_nulls(char *arr, size_t size);
bool MY_is_delimiter(char c, char *delimiters);

#endif /* SHELL_H */
