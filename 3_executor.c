#include "shell.h"

/**
 * execute_command - executes a single not-built-in command using execve
 * @command: command struct
 * @c_status: command status
 *
 * Return: -1 on success, 0 otherwise
 */
int execute_command(cmd_info *command, int *c_status)
{
	pid_t child_pid;
	int status;
	int err_check, cmd_status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("./hsh");
	}
	else if	(child_pid == 0)
	{
		/* remember to add the environment parameter */
		err_check = execve(command->cmd_name, command->args, NULL);
		if (err_check < 0)
		{
			perror("./hsh");
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		/* wait for the child to terminate */
		wait(&status);

		if (WIFEXITED(status))
		{
			cmd_status = WEXITSTATUS(status);
			*c_status = cmd_status;
		}
	}
	return (-1);
}

/**
 * is_fullpath - checks if the command has a full path
 * @cmd: the user provided command
 *
 * Return: 1 if full path is given, and 0 otherwise
 */
int is_fullpath(char *cmd)
{
	/* check of the first word starts with a '/' */
	if ((cmd[0] == '/') | (cmd[0] == '.'))
	{
		return (1);
	}

	return (0);
}

/**
 * get_full_path - appends full path to the command name if it is not given
 * @cmd: command to be executed
 *
 * Return: command name with full path on success, NULL otherwise
 */
char *get_full_path(cmd_info *cmd)
{
	char *path_env, temp_path[MAX_CHARS], *path, *new_cmd_name;
	size_t cmd_len, path_len;
	struct stat file_info;
	char *end = NULL;

	path_env = getenv("PATH");
	if (path_env == NULL)
		return (NULL);
	_strcpy(temp_path, path_env);	/* duplicate path before it is changed */

	path = _strtok(temp_path, ":", &end);	/* first directory from PATH var */
	while (path != NULL)
	{
		path_len = _strlen(path);
		cmd_len = _strlen(cmd->cmd_name);

		new_cmd_name = malloc(path_len + cmd_len + 2);	/* stores current path */
		if (new_cmd_name == NULL)
			return (NULL);

		/* construct the full path to the command */
		_strcpy(new_cmd_name, path);
		_strcat(new_cmd_name, "/");
		_strcat(new_cmd_name, cmd->cmd_name);

		/* check if the new path / command exists using stat */
		if (stat(new_cmd_name, &file_info) == 0)
		{
			/* command exists */
			_strcat(new_cmd_name, "\0");	/* Append '\0' to end new cmd name */
			return (new_cmd_name);
		}
		/* else current path is not the right path */
		free(new_cmd_name);	/* free the memory that is not returned */
		path = _strtok(NULL, ":", &end);	/* continue searching */
	}
	return (NULL);
}
