#include "shell.h"

/**
 * is_builtin_command - checks if the command is a built-in command
 * @command: command struct
 *
 * Return: 1 if command is built-in, 0 if it is not built-in
 */
cmd_info *(*is_builtin_command(cmd_info *command))(cmd_info *)
{
	builtin_cmd builtins[] = {
			{"exit", execute_exit},
			{"env", execute_env},
			{"cd", execute_cd},
			{"setenv", execute_setenv},
			{"unsetenv", execute_unsetenv},
			{NULL, NULL}
	};
	int i;

	for (i = 0; builtins[i].cmd_name != NULL; i++)
	{
		if (strcmp(command->cmd_name, builtins[i].cmd_name) == 0)
		{
			return (builtins[i].func_ptr);
		}
	}

	return (NULL);
}
