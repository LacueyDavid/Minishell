#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <unistd.h>
#include "libft/libft.h"
#include <sys/wait.h>
#include <fcntl.h>
#include "get_next_line/get_next_line.h"

extern char **environ;

static bool is_interactive_mode(void)
{
	if (isatty(STDIN_FILENO))
		return true;
	return false;
}

static void exec_command(char *input)
{
	char	**argv;
	pid_t	pid1;
	char	**paths;
	char	*command;

	argv = ft_split(input, ' ');
	paths = find_paths(environ);
	command = get_command(argv[0], paths);
	pid1 = fork();
	if (pid1 == 0)
		execve(command, argv, environ);
	waitpid(pid1, NULL, 0);
}

void	interactive_mode(void)
{
	char *input;

	while(true)
	{
		input = readline("Wesh: ");
		if (!input)
			break;
		add_history(input);
		exec_command(input);
		free(input);
	}
}

void	non_interactive_mode(void)
{
	char *input = NULL;

	while(true)
	{
		input = get_next_line(STDIN_FILENO);
		if (!input)
			break;
		size_t input_size = ft_strlen(input);
		input[input_size - 1] = '\0';
		add_history(input);
		exec_command(input);
		free(input);
	}
}

int main(void)
{
	if (is_interactive_mode())
		interactive_mode();
	else
		non_interactive_mode();
	return (0);
}
