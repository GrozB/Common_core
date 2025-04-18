/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tb_token2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:44:23 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 14:30:06 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_expansion.h"

int	tb_handle_current_char(t_tb *tb)
{
	char	c;

	c = tb->input[*tb->iptr];
	if (c == '>' || c == '<' || c == '|')
		return (tb_process_special(tb));
	else if (c == '$')
		return (tb_process_dollar(tb));
	else if (c == '\"' || c == '\'')
		return (tb_process_quote(tb));
	else
		return (tb_process_else(tb));
}

int	tb_loop(t_tb *tb)
{
	int	ret;

	while (tb->input[*tb->iptr] && !is_whitespace(tb->input[*tb->iptr]))
	{
		ret = tb_handle_current_char(tb);
		if (ret < 0)
			return (ret);
		if (ret == 99)
			break ;
	}
	return (0);
}

char	*tb_finalize(t_tb *tb)
{
	char	*new_buf;

	if (ensure_buf_capacity(&tb->buf, &tb->buf_len, tb->pos, 1) < 0)
	{
		free(tb->buf);
		return (NULL);
	}
	tb->buf[tb->pos] = '\0';
	if (!tb->unquoted)
	{
		new_buf = malloc(tb->pos + 2);
		if (!new_buf)
		{
			free(tb->buf);
			return (NULL);
		}
		new_buf[0] = '\x01';
		ft_strcpy(new_buf + 1, tb->buf);
	}
	else
	{
		new_buf = ft_strdup(tb->buf);
	}
	free(tb->buf);
	return (new_buf);
}

char	*token_builder_noexpand(const char *input, int *i)
{
	t_tb	tb;

	tb.input = input;
	tb.iptr = i;
	tb.buf_len = 64;
	tb.pos = 0;
	tb.unquoted = 0;
	tb.buf = malloc(tb.buf_len);
	if (!tb.buf)
		return (NULL);
	if (tb_loop(&tb) < 0)
		return (free(tb.buf), NULL);
	return (tb_finalize(&tb));
}
