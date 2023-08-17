#include "shell.h"

/**
 * execute_exit - executes exit command
 * @command: command struct
 *
 * Return: Nothing on success, NULL on failure
 */
cmd_info *execute_exit(cmd_info *command)
{
	int status;

	if (command->numb_args == 1)
	{
		/*free_cmd_info(command);*/
		exit(EXIT_SUCCESS);
	}
	else if (command->numb_args == 2)
	{
		status = atoi(command->args[1]);
		if (status < 0)
		{
			invalid_exit_arg(command->args[1]);
			exit(2);
		}
		/*free_cmd_info(command);*/
		exit(status);
	}
	else
	{
		write(STDOUT_FILENO, "exit: too many arguments", 25);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (NULL);
}

/**
 * execute_env - executes env command
 * @command: command struct
 *
 * Return: Nothing on success, NULL on failure
 */
cmd_info *execute_env(cmd_info *command)
{
	/* print the environment variable */
	char **env = environ;

	(void)command;

	while (*env)
	{
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
	return (NULL);
}

/**
 * execute_cd - executes cd command
 * @command: command struct
 *
 * Return: Nothing on success, NULL on failure
 */
cmd_info *execute_cd(cmd_info *command)
{
	if (command->numb_args == 2)
	{
		printf("The argument (folder name) is %s\n", command->args[1]);
		if (chdir(command->args[1]) == -1)
		{
			perror("cd");
		}
	}
	else
	{
		write(STDOUT_FILENO, "cd: invalid arguments", 21);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (NULL);
}

/**
 * execute_setenv - executes setenv
 * @command: command struct
 *
 * Return: Nothing on success, NULL on failure
 */
cmd_info *execute_setenv(cmd_info *command)
{
	if (command->numb_args == 2)
	{
		if (setenv(command->args[0], command->args[1], 1) == -1)
		{
			perror("setenv");
		}
	}
	else
	{
		printf("setenv: invalid arguments\n");
	}
	return (NULL);
}

/**
 * execute_unsetenv - executes unsetenv
 * @command: command struct
 *
 * Return: Nothing on success, NULL on failure
 */
cmd_info *execute_unsetenv(cmd_info *command)
{
	if (command->numb_args == 1)
	{
		if (unsetenv(command->args[0]) == -1)
		{
			perror("unsetenv");
		}
	}
	else
	{
		printf("unsetenv: invalid arguments\n");
	}
	return (NULL);
}
