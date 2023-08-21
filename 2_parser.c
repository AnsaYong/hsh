#include "shell.h"

/**
 * init_info - Initializes the cmd_data struct
 * @parsed_commands: cmd_data struct to be nitialized
 */
void init_info(cmd_data *parsed_commands)
{
	parsed_commands->numb_cmds = 0;
	parsed_commands->cmds = NULL;
}

/**
 * parse_cmd - tokenize a single command and populate the command info struct
 * @user_input: user command / cmd_line
 * @cmd: struct to contain tokenized command
 */
void parse_cmd(char *user_input, cmd_info *cmd)
{
	char *token, *end = NULL;
	int arg_count = 0;

	/* First, extract the command name */
	token = _strtok(user_input, " ", &end);
	cmd->cmd_name = _strdup(token);

	/* Now, extract the arguments */
	cmd->args = NULL;

	while (token != NULL)
	{
		cmd->args = realloc(cmd->args, (arg_count + 2) * sizeof(char *));

		if (cmd->args == NULL)
		{
			perror("realloc");
		}

		cmd->args[arg_count] = _strdup(token);

		if (cmd->args[arg_count] == NULL)
		{
			perror("args error");
		}

		arg_count++;
		token = _strtok(NULL, " ", &end);
	}

	cmd->numb_args = arg_count;
	cmd->args[arg_count] = NULL;  /* Null-terminate the array */
}

/**
 * handle_separator - Break up multiple commands separated by the specified
 * separator, then call parse_cmd to tokenize the commands separately
 * @cmd_line: command line
 * @input: cmd_data struct to store tokenized commands
 * @separator: separator
 */
void handle_separator(char *cmd_line, cmd_data *input, const char *separator)
{
	char *token;
	char *end = NULL;

	token = _strtok(cmd_line, separator, &end);

	while (token != NULL)
	{
		input->cmds = realloc(input->cmds, (input->numb_cmds + 1)
				* sizeof(cmd_info *));
		input->cmds[input->numb_cmds] = malloc(sizeof(cmd_info));
		parse_cmd(token, input->cmds[input->numb_cmds]);

		input->numb_cmds++;
		token = _strtok(NULL, separator, &end);
	}
}

/**
 * parse_input - check the input for any separators and tokenize commands
 * to prepare them for the executing function
 * @cmd_line: command line
 *
 * Return: cmd_data struct containing tokenized commands
 */
cmd_data *parse_input(char *cmd_line)
{
	cmd_data *parsed_cmds;

	parsed_cmds = malloc(sizeof(cmd_data));
	if (parsed_cmds == NULL)
	{
		return (NULL);
	}

	init_info(parsed_cmds);

	/* Process the cmd_line & separator to populate cmd_data struct */
	if (_strstr(cmd_line, "&&"))
	{
		handle_separator(cmd_line, parsed_cmds, "&&");
	}
	else if (_strstr(cmd_line, "||"))
	{
		handle_separator(cmd_line, parsed_cmds, "||");
	}
	else if (_strstr(cmd_line, ";"))
	{
		handle_separator(cmd_line, parsed_cmds, ";");
	}
	else
	{
		/* i.e. no separator is found, so treat entire line as a single command */
		parsed_cmds->cmds = realloc(parsed_cmds->cmds,
				(parsed_cmds->numb_cmds + 1) * sizeof(cmd_info *));
		parsed_cmds->cmds[parsed_cmds->numb_cmds] = malloc(sizeof(cmd_info));
		parse_cmd(cmd_line, parsed_cmds->cmds[parsed_cmds->numb_cmds]);

		parsed_cmds->numb_cmds++;
	}
	return (parsed_cmds);
}

/**
 * free_cmd_info - Free memory used in cmd_data
 * @parsed_cmds: pointer to cmd_data struct containing tokenized commands
 */
void free_cmd_info(cmd_data *parsed_cmds)
{
	int i, j;

	for (i = 0; i < parsed_cmds->numb_cmds; i++)
	{
		free(parsed_cmds->cmds[i]->cmd_name);
		for (j = 0; j < parsed_cmds->cmds[i]->numb_args; j++)
		{
			free(parsed_cmds->cmds[i]->args[j]);
		}
		free(parsed_cmds->cmds[i]->args);
		free(parsed_cmds->cmds[i]);
	}
	free(parsed_cmds->cmds);
	free(parsed_cmds);
}
