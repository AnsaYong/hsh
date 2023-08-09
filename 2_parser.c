#include "shell.h"

/* Initialize parse_info struct using this function */
void init_info(cmd_data *parsed_commands)
{
	parsed_commands->numb_cmds = 0;
	parsed_commands->cmds = NULL;
}

/* tokenize a single command and populate the command info struct */
void parse_cmd(char *user_input, cmd_info *cmd)
{
	char *token;
	int arg_count = 0;

	/* First, extract the command name */
	token = strtok(user_input, " ");
	cmd->cmd_name = strdup(token);

	/* Now, extract the arguments */
	cmd->args = NULL;
	while (token != NULL)
	{
		cmd->args = realloc(cmd->args, (arg_count + 1) * sizeof(char *));
		cmd->args[arg_count] = strdup(token);
		arg_count++;
		token = strtok(NULL, " ");
	}
	cmd->numb_args = arg_count;
}

/* Break up multiple commands separated by the given separator, then call parse_cmd to tokenize the commands separately */
void handle_separator(char *cmd_line, cmd_data *input, const char *separator)
{
	char *token;
	/*char *cmd_line_copy;*/
	char *end = NULL;

	/* Duplicate the input cmdline, as strtok will modify the string */
	/*cmd_line_copy = strdup(cmd_line);*/
	printf("The separator is %s\n", separator);

	token = _strtok(cmd_line, separator, &end);
	printf("The first token is %s\n", token);
	while (token != NULL)
	{
		input->cmds = realloc(input->cmds, (input->numb_cmds + 1) * sizeof(cmd_info *));
		input->cmds[input->numb_cmds] = malloc(sizeof(cmd_info));
		parse_cmd(token, input->cmds[input->numb_cmds]);

		input->numb_cmds++;
		token = _strtok(NULL, separator, &end);
		printf("The next token is %s\n", token);
	}

	/*free(cmd_line_copy);*/
}

/* check the input and prepare commands for the executing function */
cmd_data *parse_input(char *cmd_line)
{
	cmd_data *parsed_cmds;

	parsed_cmds = malloc(sizeof(cmd_data));
	if (parsed_cmds == NULL)
	{
		return (NULL);
	}
	init_info(parsed_cmds);

	/* Look for specific separators in the user input */
	if (!strstr(cmd_line, "&&") && !strstr(cmd_line, "||") && !strstr(cmd_line, ";"))
	{
		/* If no separator is found, treat the entire input as a single command */
		parsed_cmds->cmds = realloc(parsed_cmds->cmds, (parsed_cmds->numb_cmds + 1) * sizeof(cmd_info *));
		parsed_cmds->cmds[parsed_cmds->numb_cmds] = malloc(sizeof(cmd_info));
		parse_cmd(cmd_line, parsed_cmds->cmds[parsed_cmds->numb_cmds]);

		parsed_cmds->numb_cmds++;
		printf("There is only %d command\n", parsed_cmds->numb_cmds);
	}
	else
	{
		/* Handle different separators */
		/* For each command in cmd_line, call parse_cmd() and store the result in cmd_data */
		if (strstr(cmd_line, "&&"))
		{
			handle_separator(cmd_line, parsed_cmds, "&&");
			printf("There are %d commands, separated by &&\n", parsed_cmds->numb_cmds);
		}
		else if (strstr(cmd_line, "||"))
		{
			handle_separator(cmd_line, parsed_cmds, "||");
			printf("There are multiple commands, separated by ||\n");
		}
		else
		{
			handle_separator(cmd_line, parsed_cmds, ";");
			printf("There are multiple commands, separated by ;\n");
		}
	}

	return (parsed_cmds);
}

/* prints out the parse_input() struct */
void print_cmd_info(cmd_data *parsed_cmds)
{
	int i, j;
	cmd_info *cmd;

	/* Print the content of the cmd_data struct */
	for (i = 0; i < parsed_cmds->numb_cmds; i++)
	{
		cmd = parsed_cmds->cmds[i];
		printf("Command %d: %s\n", i + 1, cmd->cmd_name);
		printf("Arguments: ");
		for (j = 0; j < cmd->numb_args; j++)
		{
			printf("%s ", cmd->args[j]);
		}
		printf("\n");
	}
}

/* free memory used in cmd_data */
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
