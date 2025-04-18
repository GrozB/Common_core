/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_line_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:25:16 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 17:25:39 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static int	handle_regular_char(const char *line, int *i, t_buf_info *bi)
{
	if (ensure_buf_capacity(&(bi->buf), &(bi->buf_len), bi->pos, 1) < 0)
		return (-1);
	bi->buf[bi->pos++] = line[(*i)++];
	return (1);
}

static int	handle_quotes(const char *line,
	int *i, t_buf_info *bi, t_quote_state *qs)
{
	if (line[*i] == '\'' && !(qs->in_dquote))
	{
		qs->in_squote = !(qs->in_squote) && handle_single_quote(line, i, bi);
		return (1);
	}
	if (line[*i] == '\"' && !(qs->in_squote))
	{
		qs->in_dquote = !(qs->in_dquote) && handle_double_quote(line, i, bi);
		return (1);
	}
	return (0);
}

static int	handle_dollar_or_regular(const char *line,
	int *i, t_buf_info *bi, t_shell *shell)
{
	if (line[*i] == '$')
	{
		if (handle_dollar(line, i, bi, shell) < 0)
			return (-1);
	}
	else if (handle_regular_char(line, i, bi) < 0)
		return (-1);
	return (1);
}

static char	*finalize_buffer(t_buf_info *bi)
{
	if (ensure_buf_capacity(&(bi->buf), &(bi->buf_len), bi->pos, 1) < 0)
	{
		free(bi->buf);
		return (NULL);
	}
	bi->buf[bi->pos] = '\0';
	return (bi->buf);
}

char	*expand_vars(const char *line, int last_exit_status, t_shell *shell)
{
	int				i;
	t_buf_info		bi;
	t_quote_state	qs;

	(void)last_exit_status;
	qs.in_squote = 0;
	qs.in_dquote = 0;
	i = 0;
	bi.buf_len = 64;
	bi.buf = malloc(bi.buf_len);
	if (!bi.buf)
		return (NULL);
	bi.pos = 0;
	while (line[i])
	{
		if (handle_quotes(line, &i, &bi, &qs))
			continue ;
		if (handle_dollar_or_regular(line, &i, &bi, shell) < 0)
		{
			free(bi.buf);
			return (NULL);
		}
	}
	return (finalize_buffer(&bi));
}
