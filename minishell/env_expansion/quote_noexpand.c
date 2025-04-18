/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_noexpand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:44:05 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 14:29:41 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_expansion.h"

int	handle_quote_noexpand(const char *input, int *i, t_buf_info *bi)
{
	if (input[*i] == '\"')
		return (parse_dq_noexpand(input, i, bi));
	else if (input[*i] == '\'')
		return (parse_sq_noexpand(input, i, bi));
	return (0);
}

int	parse_dq_noexpand(const char *input, int *i, t_buf_info *bi)
{
	(*i)++;
	while (input[*i] && input[*i] != '\"')
	{
		if (ensure_buf_capacity(&bi->buf, &bi->buf_len, bi->pos, 1) < 0)
			return (-1);
		bi->buf[bi->pos++] = input[*i];
		(*i)++;
	}
	if (input[*i] != '\"')
		return (-1);
	(*i)++;
	return (0);
}

int	parse_sq_noexpand(const char *input, int *i, t_buf_info *bi)
{
	(*i)++;
	while (input[*i] && input[*i] != '\'')
	{
		if (ensure_buf_capacity(&bi->buf, &bi->buf_len, bi->pos, 1) < 0)
			return (-1);
		bi->buf[bi->pos++] = input[*i];
		(*i)++;
	}
	if (input[*i] != '\'')
		return (-1);
	(*i)++;
	return (0);
}
