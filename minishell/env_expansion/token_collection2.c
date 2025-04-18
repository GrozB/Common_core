/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_collection2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:44:28 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/18 14:33:03 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_expansion.h"

char	**collect_tokens_loop(const char *input, int last_exit_status,
		int token_count, t_shell *shell)
{
	char	**tokens;

	tokens = allocate_tokens(token_count);
	if (!tokens)
		return (NULL);
	if (collect_tokens(input, last_exit_status, tokens, shell) < 0)
		return (NULL);
	return (tokens);
}

char	**handle_token_fixing(char **tokens)
{
	char	**tmp;
	char	**fixed_tokens;

	tmp = fix_all_redirs_tokens(tokens);
	if (!tmp)
	{
		free_str_array(tokens);
		return (NULL);
	}
	free(tokens);
	fixed_tokens = fix_here_doc_tokens(tmp);
	if (!fixed_tokens)
	{
		free_str_array(tmp);
		return (NULL);
	}
	free(tmp);
	return (fixed_tokens);
}

char	**collect_and_fix_tokens(const char *input, int last_exit_status,
		int token_count, t_shell *shell)
{
	char	**tokens;

	tokens = collect_tokens_loop(input, last_exit_status, token_count, shell);
	if (!tokens)
		return (NULL);
	tokens = handle_token_fixing(tokens);
	if (!tokens)
	{
		free_str_array(tokens);
		return (NULL);
	}
	return (tokens);
}

char	**parse_input(const char *input, int last_exit_status, t_shell *shell)
{
	int		token_count;
	char	**tokens;

	if (!input)
		return (NULL);
	token_count = count_tokens(input, last_exit_status, shell);
	if (token_count < 0)
	{
		write(2, "minishell: syntax error: unmatched quote\n", 41);
		return (NULL);
	}
	tokens = collect_and_fix_tokens(input,
			last_exit_status, token_count, shell);
	if (!tokens)
	{
		write(2, "minishell: memory allocation failed\n", 36);
		return (NULL);
	}
	return (tokens);
}
