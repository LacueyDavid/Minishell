#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(/* int argc, char **argv, char **envp */)
{
	char	*input;

	while(1)
	{
		input = readline("Wesh: ");
		if (!input)
			break;
		add_history(input);
	}
	free(input);
	return (0);
}
