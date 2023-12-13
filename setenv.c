#include "main.h"

/**
 * setenv_command - the setenv command
 * @command_line: command passed
 * Return: 1 on error, 0 onsucces
 */

int setenv_command(const char *command_line)
{
	char *token, *args[20];
	char *temp_command = _strdup(command_line);
	int arg_count = 0;

	if (temp_command == NULL)
	{
		perror("Memory allocation failed");
		return (1);
	}

	token = _strtok(temp_command, " ");

	while (token != NULL)
	{
		args[arg_count++] = token;
		token = _strtok(NULL, " ");
	}

	args[arg_count++] = NULL;

	if (arg_count == 3)
	{
		if (setenv(args[1], args[2], 1) != 0)
		{
			perror("setenv");
			free(temp_command);
			return (1);
		}
	}
	else
	{
		perror("Error: Setenv");
		free(temp_command);
		return (1);
	}

	free(temp_command);
	return (0);
}

/**
 * unsetenv_command - unsetenv funtion
 * @command_line: command passed
 * Return: 1 on error, 0 on success
 */

int unsetenv_command(const char *command_line)
{
	char *token, *args[20];
	char *temp_command = _strdup(command_line);
	int arg_count = 0;

	if (temp_command == NULL)
	{
		perror("Memory allocation failed");
		return (1);
	}

	token = _strtok(temp_command, " ");

	while (token != NULL)
	{
		args[arg_count++] = token;
		token = _strtok(NULL, " ");
	}

	args[arg_count++] = NULL;

	if (arg_count == 2)
	{
		if (unsetenv(args[1]) != 0)
		{
			perror("unsetenv");
			free(temp_command);
			return (1);
		}
	}
	else
	{
		perror("Error: Setenv");
		free(temp_command);
		return (1);
	}

	free(temp_command);
	return (0);
}
