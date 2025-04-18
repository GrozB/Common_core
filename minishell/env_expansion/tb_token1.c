/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tb_token1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:44:20 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 14:30:02 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_expansion.h"

int	tb_append(t_tb *tb, char c)
{
	if (ensure_buf_capacity(&tb->buf, &tb->buf_len, tb->pos, 1) < 0)
		return (-1);
	tb->buf[tb->pos++] = c;
	return (0);
}

int	tb_process_special(t_tb *tb)
{
	if (tb->pos > 0)
		return (99);
	tb->unquoted = 1;
	if (tb_append(tb, tb->input[*tb->iptr]) < 0)
		return (-1);
	if ((tb->input[*tb->iptr] == '>' || tb->input[*tb->iptr] == '<')
		&& tb->input[*tb->iptr + 1] == tb->input[*tb->iptr])
	{
		(*tb->iptr)++;
		if (tb_append(tb, tb->input[*tb->iptr]) < 0)
			return (-1);
	}
	(*tb->iptr)++;
	return (1);
}

int	tb_process_dollar(t_tb *tb)
{
	tb->unquoted = 1;
	if (tb_append(tb, '$') < 0)
		return (-1);
	(*tb->iptr)++;
	return (1);
}

int	tb_process_quote(t_tb *tb)
{
	t_buf_info	bi;

	bi.buf = tb->buf;
	bi.buf_len = tb->buf_len;
	bi.pos = tb->pos;
	if (handle_quote_noexpand(tb->input, tb->iptr, &bi) < 0)
		return (-1);
	tb->buf = bi.buf;
	tb->buf_len = bi.buf_len;
	tb->pos = bi.pos;
	return (1);
}

int	tb_process_else(t_tb *tb)
{
	tb->unquoted = 1;
	if (tb_append(tb, tb->input[*tb->iptr]) < 0)
		return (-1);
	(*tb->iptr)++;
	return (1);
}
