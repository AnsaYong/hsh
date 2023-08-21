#ifndef SHELL_H
#define SHELL_H

/*---LIBRARIES---*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/*---MACROS---*/
#define MAX_CHARS 1024

/*---VARIABLES---*/
extern char **environ;

/*---STRUCTS---*/

/* 2_parser.c */
/**
 * struct command_info - store information about a single command
 * @cmd_name: A string (char pointer) representing the command name
 * @numb_args: An integer representing the number of arguments for the command
 * @args: A pointer to an array of strings (char pointers) to store the
 * arguments for the command.
 *
 * Description: store information about a single command, after tokenizing
 * the user input and breaking up commands at separators
 */
typedef struct command_info
{
	char *cmd_name;
	int numb_args;
	char **args;
} cmd_info;

/**
 * struct command_structure - represents information from the user input
 * @numb_cmds: an int representing the number of commands provided by the user
 * @cmds: A pointer to an array of pointers to cmd_info structs. This allows
 * you to store information about each individual command.
 */
typedef struct command_structure
{
	int numb_cmds;
	cmd_info **cmds;
} cmd_data;

typedef cmd_info *(*builtin_function)(cmd_info *);

/**
 * struct builtin_func - returns pointer to the matched builtin function
 * @cmd_name: command to compare against predefined builtin functions
 * @func_ptr: the associated function
 */

typedef struct builtin_func
{
	char *cmd_name;
	builtin_function func_ptr;
} builtin_cmd;


/*---PROTOTYPES---*/

/* 0_shell.c */
void interactive_mode(char *prog);
void non_interactive_mode(char *prog);
int process_commands(cmd_data *commands, char *prog);
/* 1_read_commands.c */
char *read_cmd_line(void);
ssize_t _getline(char **lineptr, size_t *n, int fd);
/* 2_parser.c */
void init_info(cmd_data *parsed_commands);
void parse_cmd(char *user_input, cmd_info *cmd);
void handle_separator(char *cmd_line, cmd_data *input, const char *separator);
cmd_data *parse_input(char *cmd_line);
void print_cmd_info(cmd_data *parsed_cmds);
void free_cmd_info(cmd_data *parsed_cmds);
/* 3_executor.c */
int execute_command(cmd_info *command, int *c_status);
int is_fullpath(char *cmd);
char *get_full_path(cmd_info *cmd);
/* aux_functions.c */
char *_strtok(char *str, const char *sep, char **end);
void strip_white_spaces(char **args_arr, int numb_args);
int is_all_spaces(const char *line);
builtin_function is_builtin_command(cmd_info *command);
/* 4_builtin_functions.c */
cmd_info *execute_exit(cmd_info *command);
cmd_info *execute_env(cmd_info *command);
cmd_info *execute_cd(cmd_info *command);
cmd_info *execute_setenv(cmd_info *command);
cmd_info *execute_unsetenv(cmd_info *command);
/* error_messages.c */
void command_not_found(char *prog, char *command);
void invalid_exit_arg(char *arg);
/* string_functions.c */
char *_strdup(char *str);
int _strlen(char *str);
void _strcat(char *s1, char *s2);
char *_strchr(const char *s, const char c);
int _atoi(const char *str);
/* more_string_functions.c */
char *_strcpy(char *destination, const char *source);
int _strcmp(char *str1, char *str2);
int compare(const char *main_str, const char *search_str);
const char *_strstr(const char *main_str, const char *search_str);

#endif /* SHELL_H */
