#include "shell.h"

/**
 * execute_command - executes a single not-built-in command using execve
 * @command: command struct
 *
 * Return: -1 on success, 0 otherwise
 */
int execute_command(cmd_info *command)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("./hsh");
	}
	else if	(child_pid == 0)
	{
		/* remember to add the environment parameter */
		if (execve(command->cmd_name, command->args, NULL) < 0)
		{
			perror("./hsh");
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		/* wait for the child to terminate */
		wait(&status);
	}
	return (-1);
}

/**
 * is_fullpath - checks if the command is a full path
 * @command: the provided user command
 *
 * Return: 1 if full path is given, and 0 otherwise
 */
int is_fullpath(char *cmd)
{
	/* check of the first word starts with a '/' */
	if (cmd[0] == '/')
	{
		return (1);
	}
	return (0);
}

/**
 * get_full_path - appends full path to the command name if it is not given
 * @cmd: command to be executed
 */
void get_full_path(cmd_info *cmd)
{
	char *path_env, *path, *new_cmd_name;
	size_t cmd_len, path_len;
	struct stat file_info;

	path_env = getenv("PATH");
	if (path_env == NULL)
		return;

	/* tokenize the PATH variable */
	path = strtok(path_env, ":");
	while (path != NULL)
	{
		path_len = strlen(path);
		cmd_len = strlen(cmd->cmd_name);

		/* allocate memory for the concatenated command name */
		new_cmd_name = malloc(path_len + cmd_len + 2);
		if (new_cmd_name == NULL)
		{
			perror("malloc");
			return;
		}
		/* construct the full path to the command */
		strcpy(new_cmd_name, path);
		strcat(new_cmd_name, "/");
		strcat(new_cmd_name, cmd->cmd_name);

		/* check if the new path exists using stat */
		if (stat(new_cmd_name, &file_info) == 0)
		{
			/* update the command name and the first argument */
			/*free(cmd->cmd_name);*/
			strcat(new_cmd_name, "\0");	/* append '\0' to end of new cmd */
			cmd->cmd_name = new_cmd_name;
			cmd->args[0] = new_cmd_name;	/* Update the first argument as well */
			/*return; *//* Stop after finding the first matching path */
		}

		path = strtok(NULL, ":");
	}
}
