/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_fix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:59:18 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 18:02:39 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	get_op_len(const char *token)
{
	int	op_len;

	if ((token[0] == '<' || token[0] == '>') && (token[1] == token[0]))
		op_len = 2;
	else if (token[0] == '<' || token[0] == '>')
		op_len = 1;
	else
		op_len = 0;
	return (op_len);
}

static char	**fill_redir_array(const char *token, int op_len)
{
	char	**res;

	res = malloc(sizeof(char *) * 3);
	if (!res)
		return (NULL);
	res[0] = ft_strndup(token, op_len);
	if (!res[0])
	{
		free(res);
		return (NULL);
	}
	if (token[op_len] != '\0')
	{
		res[1] = ft_strdup(token + op_len);
		if (!res[1])
		{
			free(res[0]);
			free(res);
			return (NULL);
		}
		res[2] = NULL;
	}
	else
		res[1] = NULL;
	return (res);
}

char	**split_redir_token(const char *token)
{
	int		op_len;
	char	**res;

	op_len = get_op_len(token);
	if (op_len == 0)
		return (NULL);
	res = fill_redir_array(token, op_len);
	return (res);
}

static int	count_new_tokens(char **tokens)
{
	int		i;
	int		new_count;

	i = 0;
	new_count = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '\x01')
			new_count++;
		else if (tokens[i][0] == '<' && tokens[i][1] == '<'
					&& tokens[i][2] != '\0')
			new_count += 2;
		else
			count_split_tokens(tokens, &new_count, i);
		i++;
	}
	return (new_count);
}

char	**fix_all_redirs_tokens(char **tokens)
{
	int		new_count;
	char	**new_tokens;

	if (!tokens)
		return (NULL);
	new_count = count_new_tokens(tokens);
	new_tokens = malloc(sizeof(char *) * (new_count + 1));
	if (!new_tokens)
		return (NULL);
	if (!fill_new_tokens(tokens, new_tokens, new_count))
	{
		return (NULL);
	}
	return (new_tokens);
}
