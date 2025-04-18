/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_collection1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:44:26 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 15:28:30 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_expansion.h"

int	skip_ws(const char *input, int i)
{
	while (input[i] && is_whitespace(input[i]))
		i++;
	return (i);
}

char	**allocate_tokens(int token_count)
{
	char	**tokens;

	tokens = malloc(sizeof(char *) * (token_count + 1));
	if (!tokens)
		return (NULL);
	return (tokens);
}

int	handle_token_error(char **tokens, int t)
{
	free_str_array_partial(tokens, t);
	free(tokens);
	return (-1);
}

static char	*handle_twenty_five_lines(int *noexpand, const char *input, int *i)
{
	*noexpand = 0;
	return (token_builder_noexpand(input, i));
}

int	collect_tokens(const char *input, int last_exit_status,
		char **tokens, t_shell *shell)
{
	int		i;
	int		t;
	int		noexpand;
	char	*tok;

	i = skip_ws(input, 0);
	t = 0;
	noexpand = 0;
	while (input[i])
	{
		if (noexpand)
			tok = handle_twenty_five_lines(&noexpand, input, &i);
		else
			tok = parse_token(input, &i, last_exit_status, shell);
		if (!tok)
			return (handle_token_error(tokens, t));
		tokens[t++] = tok;
		if (ft_strcmp(tok, "<<") == 0)
			noexpand = 1;
		i = skip_ws(input, i);
	}
	tokens[t] = NULL;
	return (0);
}
