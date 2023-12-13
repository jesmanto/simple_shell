#include "main.h"

/**
 * show_prompt - function to display shell prompt
 * Return: Nothing
 */

void show_prompt(void)
{
	char prompt[] = "my_shell# ";

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, prompt, _strlen(prompt));
}

/**
 * main - the main funtion for th simple shell
 * Return: 0 on success
 */

int main(void)
{
	int term = 1;
	char *tmp = NULL;
	ssize_t cmd = 0;
	size_t tmp_size = 0;

	while (term)
	{
		show_prompt();
		cmd = getline(&tmp, &tmp_size, stdin);
		if (cmd == EOF)
		{
			free(tmp);
			break;
		}
		else if (cmd == -1)
		{
			perror("Input Probably wrong");
		}
		else
		{
			if (tmp[cmd - 1] == '\n')
				tmp[cmd - 1] = '\0';
			if (_strcmp(tmp, "exit") == 0)
			{
				free(tmp);
				break;
			}
			else if (_strcmp(tmp, "setenv") == 0)
				setenv_command(tmp);
			else if (_strcmp(tmp, "unsetenv") == 0)
				unsetenv_command(tmp);
			else
				launch_command(tmp);
		}
	free(tmp);
	tmp = NULL;
	tmp_size = 0;
	}
	return (0);
}
