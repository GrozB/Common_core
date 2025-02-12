#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

int	main(void)
{
	char	**tokens;
	int		i;

	tokens = parse_input("  echo    hello     world    ");
	if (!tokens)
		return (1);
	i = 0;
	while (tokens[i])
	{
		printf("Token %d: '%s'\n", i, tokens[i]);
		i++;
	}
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
	return (0);
}
