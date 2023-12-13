#include "main.h"

/**
 * change_to_directory - funtion to change the current directory
 * @dir: the directory to chane to
 * Return: 0 on success , 1 0n erro
 */

int change_to_directory(const char *dir)
{
	if (chdir(dir) != 0)
	{
		perror("chdir failed");
		return (1);
	}
	return (0);
}

/**
 * cd_home - cd home funtion
 * Return: 0 on succes
 */

int cd_home(void)
{
	const char *home = getenv("HOME");

	if (home == NULL)
	{
		perror("HOME env vari not set");
		return (1);
	}
	return (change_to_directory(home));
}

/**
 * cd_previous - cd previous funtion
 * Return: 0 on succes
 */

int cd_previous(void)
{
	const char *prev_dir = getenv("OLDPWD");

	if (prev_dir == NULL)
	{
		perror("HOME env vari not set");
		return (1);
	}
	return (change_to_directory(prev_dir));
}

/**
 * cd_command - finton to handel the cd command
 * @command_line: command to be passed by the user
 * Return: 0 on success, 1 on error
 */

int cd_command(const char *command_line)
{
	char *token, *temp_command = _strdup(command_line);
	int arg_count = 0;
	char *args[20];

	if (temp_command == NULL)
	{
		perror("failed to allocate memory");
		return (1);
	}
	token = _strtok(temp_command, " ");
	while (token != NULL)
	{
		args[arg_count++] = token;
		token = _strtok(NULL, " ");
	}
	args[arg_count] = NULL;

	if (arg_count == 1)
		return (cd_home());
	else if (arg_count == 2)
	{
		if (_strcmp(args[1], "-") == 0)
			return (cd_previous());
		else
			return (change_to_directory(args[1]));
	}
	else
	{
		perror("cd comand not working");
		free(temp_command);
		return (1);
	}

		free(temp_command);
		return (0);
}
