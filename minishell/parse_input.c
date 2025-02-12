#include "minishell.h"
#include "env_expansion.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int	count_tokens(const char *str)
{
	int	count = 0;
	int	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && str[i] != ' ' && str[i] != '\t')
			{
				if (str[i] == '\"' || str[i] == '\'')
				{
					char	quote = str[i];
					i++;
					if (!str[i])
						return (-1);
					while (str[i] && str[i] != quote)
						i++;
					if (str[i] != quote)
						return (-1);
					i++;
				}
				else
					i++;
			}
		}
	}
	return (count);
}

char	**parse_input(const char *input)
{
	int		token_count;
	char	**result;
	int		index = 0;
	int		i = 0;
	int		start, len;

	token_count = count_tokens(input);
	if (token_count < 0)
	{
		fprintf(stderr, "minishell: syntax error: unmatched quote\n");
		return (NULL);
	}
	result = malloc(sizeof(char *) * (token_count + 1));
	if (!result)
		return (NULL);
	while (input[i])
	{
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		if (input[i])
		{
			start = i;
			while (input[i] && input[i] != ' ' && input[i] != '\t')
			{
				if (input[i] == '\"' || input[i] == '\'')
				{
					char	quote = input[i];
					i++;
					if (!input[i])
					{
						fprintf(stderr, "minishell: syntax error: unmatched %c\n", quote);
						return (NULL);
					}
					while (input[i] && input[i] != quote)
						i++;
					if (input[i] != quote)
					{
						fprintf(stderr, "minishell: syntax error: unmatched %c\n", quote);
						return (NULL);
					}
					i++;
				}
				else
					i++;
			}
			len = i - start;
			result[index] = malloc(len + 1);
			if (!result[index])
				return (NULL);
			strncpy(result[index], input + start, len);
			result[index][len] = '\0';
			{
				char	*temp = expand_variables(result[index]);
				free(result[index]);
				result[index] = temp;
			}
			index++;
		}
	}
	result[index] = NULL;
	return (result);
}
