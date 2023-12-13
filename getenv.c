#include "main.h"

/**
 * _getenv - coustom getenv function
 * @cmd_name: thename of the command
 * Return: NULL
 */

char *_getenv(const char *cmd_name)
{
	int i = 0;
	size_t name_len = _strlen(cmd_name);

	while (environ[i] != NULL)
	{
		if (_strncmp(environ[i], cmd_name, name_len) == 0
				&& environ[i][name_len] == '=')
		{
			return (environ[i] + name_len + 1);
		}
		i++;
	}
	return (NULL);
}

/**
 * compare_env_variables - funtion to compare environment variables
 * @a: first string to compare
 * @b: second string to compare
 * Return: strcmp
 */

int compare_env_variables(const void *a, const void *b)
{
	const char *env_var_a = *(const char **)a;
	const char *env_var_b = *(const char **)b;

	return (_strcmp(env_var_a, env_var_b));
}


/**
 * launch_env - fucntion responsible for the executing the env command
 * the funstion will print the current environment varables
 * Return: 0 on success
 */

int launch_env(void)
{
	const char *env_variables[1024];
	int env_var_count = 0, i;
	char **env = environ;

	for (; *env != NULL; ++env)
	{
		env_variables[env_var_count++] = *env;
	}

	qsort(env_variables, env_var_count, sizeof(const char *),
			compare_env_variables);

	for (i = 0; i < env_var_count; ++i)
	{
		write(STDOUT_FILENO, env_variables[i], _strlen(env_variables[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

/**
 * print_error - custom error orinting function
 * @cmd_line: command passwd
 * @message: error message
 * @line_number: line number
 * Retunr: nothing
 */

void print_error(const char *cmd_line, const char *message, int line_number)
{
	int i = 0, line_copy = line_number, num_digits = 0, j, digit;
	char error_message[1024], line_number_str[10];

	while (cmd_line[i] != '\0')
	{
		error_message[i] = cmd_line[i];
		i++;
	}
	error_message[i++] = ':';
	error_message[i++] = ' ';

	while (line_copy > 0)
	{
		line_copy /= 10;
		num_digits++;
	}

	for (j = num_digits - 1; j >= 0; j--)
	{
		digit = line_number % 10;
		line_number_str[j] = '0' + digit;
		line_number /= 10;
	}

	for (j = 0; j < num_digits; j++)
		error_message[i++] = line_number_str[j];
	error_message[i++] = ':';
	error_message[i++] = ' ';

	j = 0;
	while (message[j] != '\0')
	{
		error_message[i] = message[j];
		i++;
		j++;
	}
	error_message[i++] = '\n';
	error_message[i] = '\0';

	write(STDERR_FILENO, error_message, i);
}
