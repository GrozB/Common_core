/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes_regular.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:53:45 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 18:12:05 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_dq(const char *input, int *i,
	t_buf_info *bi, t_shell *shell)
{
	*i = *i + 1;
	while (input[*i] && input[*i] != '\"')
	{
		if (input[*i] == '$')
		{
			if (handle_dollar_dq(input, i, bi, shell) < 0)
				return (-1);
		}
		else
		{
			if (ensure_buf_capacity(&(bi->buf), &(bi->buf_len), bi->pos, 1) < 0)
				return (-1);
			bi->buf[bi->pos++] = input[*i];
			*i = *i + 1;
		}
	}
	if (input[*i] != '\"')
		return (-1);
	*i = *i + 1;
	return (0);
}

int	parse_sq(const char *input, int *i, t_buf_info *bi)
{
	(*i)++;
	while (input[*i] && input[*i] != '\'')
	{
		if (ensure_buf_capacity(&(bi->buf), &(bi->buf_len), bi->pos, 1) < 0)
			return (-1);
		bi->buf[bi->pos++] = input[*i];
		(*i)++;
	}
	if (input[*i] != '\'')
		return (-1);
	(*i)++;
	return (0);
}

int	handle_quote(const char *input,
	int *i, t_buf_info *bi, t_shell *shell)
{
	if (input[*i] == '\"')
	{
		if (parse_dq(input, i, bi, shell) < 0)
			return (-1);
	}
	else if (input[*i] == '\'')
	{
		if (parse_sq(input, i, bi) < 0)
			return (-1);
	}
	return (0);
}

int	handle_regular_char(const char *input,
	int *i, t_buf_info *bi)
{
	if (ensure_buf_capacity(&(bi->buf), &(bi->buf_len), bi->pos, 1) < 0)
		return (-1);
	bi->buf[bi->pos++] = input[*i];
	(*i)++;
	return (0);
}

int	handle_special_chars(const char *input, int *i, t_buf_info *bi)
{
	if (ensure_buf_capacity(&(bi->buf), &(bi->buf_len), bi->pos, 1) < 0)
		return (-1);
	bi->buf[bi->pos++] = input[*i];
	if ((input[*i] == '>' || input[*i] == '<') && input[*i + 1] == input[*i])
	{
		(*i)++;
		if (ensure_buf_capacity(&(bi->buf), &(bi->buf_len), bi->pos, 1) < 0)
			return (-1);
		bi->buf[bi->pos++] = input[*i];
	}
	(*i)++;
	return (0);
}
