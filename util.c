#include "main.h"

/**
 * if_abs_path - function to execute command if it is an absolute path
 * @command: command passed
 * @args: arguments count
 * Return: 0 on success
 */

int if_abs_path(const char *command, char *const args[])
{
	int stat, exit_stat;
	pid_t child;

	child = fork();

	if (child == -1)
	{
		perror("No such file or directory found");
		exit(EXIT_FAILURE);
	}
	else if (child == 0)
	{
		if (execve(command, args, environ) == -1)
		{
			perror("Failed to execute command");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&stat);
		if (WIFEXITED(stat))
		{
			exit_stat = WEXITSTATUS(stat);
			if (exit_stat != 0)
				perror("child process terminated with signal");
		}
	}
	return (0);
}

/**
 * search_cmd - funtion to execute a command y seraching path
 * @cmd: command passed
 * @cmd_path: command's path
 * Return: 0 on sucess, 1 on error
 */

int search_cmd(const char *cmd, char *cmd_path)
{
	char *path = _getenv("PATH");
	char *path_copy = _strdup(path);
	char *path_token = strtok(path_copy, ":");

	if (path_copy == NULL)
	{
		perror("Memorr allocation failed");
		return (1);
	}
	while (path_token != NULL)
	{
		cmd_path[0] = '\0';
		_strcat(cmd_path, path_token);
		_strcat(cmd_path, "/");
		_strcat(cmd_path, cmd);

		if (access(cmd_path, X_OK) == 0)
		{
			free(path_copy);
			return (0);
		}

		path_token = _strtok(NULL, ":");
	}
	free(path_copy);
	return (1);
}

/**
 * search_path - funtion to execute a command y seraching path
 * @cmd: command passed
 * @args: argument count
 * Return: 0
 */
int search_path(const char *cmd, char *const args[])
{
	int stat;
	char cmd_path[1024];
	pid_t child = fork();

	if (search_cmd(cmd, cmd_path) == 0)
	{
		if (child == -1)
		{
			print_error(args[0], "No such file or directory", __LINE__);
			exit(EXIT_FAILURE);
		}
		if (child == 0)
		{
			if (execve(cmd_path, args, environ) == -1)
			{
				print_error(args[0], "Failed to execute command", __LINE__);
				exit(EXIT_FAILURE);
			}
			else
				execve(cmd_path, args, environ);
		}
		else
			wait(&stat);
		return (0);
	}
	else
	{
		print_error(args[0], "Command not found", __LINE__);
		return (1);
	}
}

/**
 * launch_command - function to execute a commnd from user input
 * @cmd_line: command passed by the user
 * Return: 0 on success, 1 on error
 */

int launch_command(const char *cmd_line)
{
	char *token, *tmp_cmd = _strdup(cmd_line), *args[20];
	int arg_count = 0;

	if (tmp_cmd == NULL)
	{
		perror("Memory allocation failed");
		return (1);
	}
	token = _strtok(NULL, " ");
	while (token != NULL)
	{
		args[arg_count++] = token;
		token = _strtok(NULL, " ");
	}
	args[arg_count] = NULL;
	if (arg_count > 0)
	{
		if (_strcmp(args[0], "exit") == 0)
			exit_cmd(cmd_line);
		else if (_strcmp(args[0], "env") == 0)
			launch_env();
		else if (_strcmp(args[0], "cd") == 0)
			cd_command(cmd_line);
		else if (_strchr(args[0], '/') != NULL)
			if_abs_path(args[0], args);
		else
			if (search_path(args[0], args) != 0)
			{
				print_error(args[0], "Command not found", __LINE__);
				free(tmp_cmd);
				return (1);
			}
	}
	free(tmp_cmd);
	return (0);
}
