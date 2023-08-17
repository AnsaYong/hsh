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
		printf("Non-interactive mode\n");
		non_interactive_mode(prog);
	}

	else
	{
		printf("Interactive mode\n");
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
	int status = -1, i, cmd_status;
	cmd_data *commands;
	/*builtin_function builtin_ptr = NULL;*/

	(void)prog;

	/* print prompt */
	while (status == -1)
	{
		builtin_function builtin_ptr = NULL;
		write(STDOUT_FILENO, "$ ", 2);
		fflush(stdout);

		/* read and store user commands from stdin */
		cmd_line = read_cmd_line();
		printf("You entered the following command: %s\n", cmd_line);

		/* break up commands and arguments into separate words */
		commands = parse_input(cmd_line);
		free(cmd_line);

		/* execute commands stored in cmd_info **cmds from cmd_data */
		for (i = 0; i < commands->numb_cmds; i++)
		{
			if((builtin_ptr = is_builtin_command(commands->cmds[i])) != NULL)
				builtin_ptr(commands->cmds[i]);
			else
			{
				printf("The function is not a builtin function\n");
				if (!(is_fullpath(commands->cmds[i]->cmd_name)))
				{
					printf("The command does not have a fullpath\n");
					get_full_path(commands->cmds[i]);
					printf("The updated command is %s\n", commands->cmds[i]->cmd_name);
					print_cmd_info(commands);
					status = execute_command(commands->cmds[i], &cmd_status);
				}
				else
				{
					status = execute_command(commands->cmds[i], &cmd_status);
				}
			}
		}
		free_cmd_info(commands);
		free(cmd_line);
	}

	/* free memory */
	/*free_cmd_info(commands);*/
	/*free(cmd_line);*/

	/* exit with status */
	if (status >= 0)
	{
		exit(status);
	}
}

/**
 * non-interactive_mode - executes commands in non interactive mode
 * @prog: a string representing the program name
 */
void non_interactive_mode(char *prog)
{
	char *cmd_line, *fullpath = NULL;
	int status = -1, i, cmd_status = 0;
	cmd_data *commands;
	builtin_function builtin_ptr = NULL;

	while (status == -1)
	{
		cmd_line = read_cmd_line();	/* get user command from stdin */
		if (cmd_line != NULL && is_all_spaces(cmd_line))
		{
			free(cmd_line);
			continue;
		}

		printf("You entered the following command: %s\n", cmd_line);
		commands = parse_input(cmd_line); /* breakup cmd_line into cmds+args */
		print_cmd_info(commands);

		/* execute all commands stored in cmd_info **cmds from cmd_data */
		for (i = 0; i < commands->numb_cmds; i++)
		{
			printf("The current command is %s\n", commands->cmds[i]->cmd_name);
			if((builtin_ptr = is_builtin_command(commands->cmds[i])) != NULL)
			{
				printf("Executing builtin command\n");
				builtin_ptr(commands->cmds[i]);	/* use (*builtin_ptr)(...) */
			}
			else
			{
				printf("Not a builtin command\n");
				printf("Checking the command for fullpath\n");
				if (!(is_fullpath(commands->cmds[i]->cmd_name)))
				{
					printf("Command is %s and does not have full path\n", commands->cmds[i]->cmd_name);
					fullpath = get_full_path(commands->cmds[i]);
					if (fullpath == NULL)
					{
						command_not_found(prog, commands->cmds[i]->cmd_name);
						free_cmd_info(commands);
						free(cmd_line);
						exit(127);
					}

					/* free, then update old cmd_name ptr with new full path */
					free(commands->cmds[i]->cmd_name);
					commands->cmds[i]->cmd_name = fullpath;

					/* free, then update first argument in args array */
					free(commands->cmds[i]->args[0]);
					commands->cmds[i]->args[0] = strdup(fullpath);

					printf("The updated command is:\n");
					print_cmd_info(commands);
					status = execute_command(commands->cmds[i], &cmd_status);
				}
				else
				{
					printf("Command is %s and full path is given\n", commands->cmds[i]->cmd_name);
					status = execute_command(commands->cmds[i], &cmd_status);
					printf("The command status is %d\n", cmd_status);
					if (cmd_status)
						exit(cmd_status);
				}
			}
		}
		free_cmd_info(commands);
		free(cmd_line);
	}

	if (status >= 0)
		exit(status);
}
