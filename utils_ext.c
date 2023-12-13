#include "main.h"

/**
 * exit_cmd - funciton that handle exit with status
 * @cmd_line: command passed by the user
 * Return: 0 on success, 1 on error
 */

void exit_cmd(const char *cmd_line)
{
	char *token;
	char *tmp_cmd = _strdup(cmd_line);
	int arg_count = 0, stat;
	char *args[20];

	if (tmp_cmd == NULL)
	{
		perror("failed to allocate memory");
		exit(1);
	}

	token = strtok(tmp_cmd, " ");
	while (token != NULL)
	{
		args[arg_count++] = token;
		token = strtok(NULL, " ");
	}

	args[arg_count] = NULL;

	if (arg_count == 1)
	{
		free(tmp_cmd);
		exit(0);
	}
	else if (arg_count == 2)
	{
		stat = atoi(args[1]);
		free(tmp_cmd);
		exit(stat);
	}
	else
	{
		write(STDERR_FILENO, "Usage:exit [stat]\n", 21);
		free(tmp_cmd);
		exit(1);
	}
}

/**
 * _strncmp - custom strncmp funtion
 * @s1: first string
 * @s2: second string
 * @n: number of char tobe compared
 * Return: 0 on success
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

/**
 * _strcat - custom strcat funtion
 * @dest: destination
 * @src: sorce
 * Return: the destination
 */

char *_strcat(char *dest, const char *src)
{
	size_t dest_len = _strlen(dest);
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];

	dest[dest_len + i] = '\0';

	return (dest);
}
