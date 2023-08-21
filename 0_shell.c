#include "shell.h"


/**
 * main - entry point of the shell program. Checks if the shell
 * is interactive or not
 * @argc: number of arguments provided
 * @argv: array of string arguments
 * @envp: the passed environment variable
 *
 * Return: 0
 */
int main(int argc, char *argv[], char *envp[])
{
	char *prog;

	(void)argc, (void)envp;
	prog = argv[0];

	if (!isatty(STDIN_FILENO))
	{
		/* source of input is anything other than the keyboard */
		non_interactive_mode(prog);
	}

	else
	{
		interactive_mode(prog);
	}

	return (0);
}

/**
 * interactive_mode - executes commands in interactive mode
 * @prog: a string representing the program name
 */
void interactive_mode(char *prog)
{
	char *cmd_line;
	int status = -1;
	cmd_data *commands;

	while (status == -1)
	{
		/* print prompt */
		write(STDOUT_FILENO, "$ ", 2);
		fflush(stdout);

		/* read and store user commands from stdin */
		cmd_line = read_cmd_line();
		if (cmd_line != NULL && is_all_spaces(cmd_line))
		{
			free(cmd_line);
			continue;
		}

		/* break up commands and arguments into separate words */
		commands = parse_input(cmd_line);

		/* process tokenized commands */
		status = process_commands(commands, prog);

		/* free memory */
		free_cmd_info(commands);
		free(cmd_line);
	}

	/* exit with status */
	if (status >= 0)
	{
		exit(status);
	}
}

/**
 * non_interactive_mode - executes commands in non interactive mode
 * @prog: a string representing the program name
 */
void non_interactive_mode(char *prog)
{
	char *cmd_line;
	int status = -1;
	cmd_data *commands;

	while (status == -1)
	{
		/* get user command from stdin */
		cmd_line = read_cmd_line();
		if (cmd_line != NULL && is_all_spaces(cmd_line))
		{
			free(cmd_line);
			continue;
		}

		/* breakup cmd_line into command + arguments */
		commands = parse_input(cmd_line);

		/* process tokenized commands */
		status = process_commands(commands, prog);

		/* free memory used for both user command and for tokenizing */
		free_cmd_info(commands);
		free(cmd_line);
	}

	if (status >= 0)
		exit(status);
}

/**
 * process_commands - processes each command in the cmd_data struct
 * @commands: cmd_data struct containing all the commands
 * @prog: program name
 *
 * Return: status of execution
 */
int process_commands(cmd_data *commands, char *prog)
{
	int i, status, cmd_status;
	char *fullpath;
	builtin_function builtin_ptr = NULL;

	for (i = 0; i < commands->numb_cmds; i++) /* execute all commandds */
	{
		builtin_ptr = is_builtin_command(commands->cmds[i]);
		if (builtin_ptr != NULL)
		{
			builtin_ptr(commands->cmds[i]); /* use (*builtin_ptr)(...) */
			return (-1);
		}
		else	/* not builtin command */
		{
			if (!(is_fullpath(commands->cmds[i]->cmd_name)))	/* fullpath not given */
			{
				fullpath = get_full_path(commands->cmds[i]);
				if (fullpath == NULL)
				{
					command_not_found(prog, commands->cmds[i]->cmd_name);
					return (127);
				}
				free(commands->cmds[i]->cmd_name);	/* clear old cmd_name */
				commands->cmds[i]->cmd_name = fullpath;	/* replace */
				free(commands->cmds[i]->args[0]);	/* clear old cmd_name */
				commands->cmds[i]->args[0] = strdup(fullpath); /* replace */

				status = execute_command(commands->cmds[i], &cmd_status);
			}
			else
				status = execute_command(commands->cmds[i], &cmd_status);
		}
	}
	return (status);
}
