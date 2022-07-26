#include "main.h"

int cmd_checker(char **commands)
{
	struct stat st;
	char *cmd = command_verify(commands);

	if (stat(commands[0], &st) == 0)
	{
		exec(commands);
	}
	else
	{
		if (is_builtin(commands) == 0)
			run_built(commands);
		else if (cmd != NULL)
		{
			commands[0] = cmd;
			exec(commands);
			free(cmd);
		}
		else
			perror("Error: ");
	}
	return (0);
}

char **line_parse(char *prompt)
{
	char **tokens, *token;
	int size = 1024, i = 0;

	tokens = malloc(sizeof(char *) * size);
	if (tokens == NULL)
	{
		free(tokens);
		printf("Error\n");
		exit(1);
	}
	token = strtok(prompt, " \n\t\r");
	for (i = 0; token; i++)
	{
		tokens[i] = token;
		token = strtok(NULL, " \n\t\r");
	}
	tokens[i] = NULL;
	free(token);
	return (tokens);
}

void print_prompt(void)
{
	char *usr = _getenv("USER");
	_puts(usr);
	_putchar('@');
	_puts("hsh> ");
}

char *_getenv(const char *name)
{
	int i, j, found;

	for (i = 0; environ[i]; i++)
	{
		found = 1;
		for (j = 0; environ[i][j] != '='; j++)
		{
			if (name[j] != environ[i][j])
			{
				found = 0;
				break;
			}
		}

		if (found)
			return (&environ[i][j + 1]);
	}
	return (NULL);
}
char *line_read(void)
{
	int status;
	char *cmd = NULL;
	size_t size = 1024;
	status = getline(&cmd, &size, stdin);

	if (status == -1)
	{
		if (status == EOF)
		{
			printf("\n");
		}
		else
		{
			printf("Error\n");
			exit (1);
		}
	}
	return (cmd);
}
