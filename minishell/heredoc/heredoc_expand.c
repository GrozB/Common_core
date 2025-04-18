/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:24:01 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 18:47:14 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

int	handle_single_quote(const char *line, int *i, t_buf_info *bi)
{
	bi->buf[bi->pos++] = line[(*i)++];
	return (1);
}

int	handle_double_quote(const char *line, int *i, t_buf_info *bi)
{
	bi->buf[bi->pos++] = line[(*i)++];
	return (1);
}

int	handle_dollar_question(int *i, t_buf_info *bi, int last_exit_status)
{
	char	*num;
	int		j;

	j = 0;
	num = ft_itoa(last_exit_status);
	if (!num)
		return (-1);
	while (num[j])
	{
		if (ensure_buf_capacity(&(bi->buf), &(bi->buf_len), bi->pos, 1) < 0)
		{
			free(num);
			return (-1);
		}
		bi->buf[bi->pos++] = num[j++];
	}
	free(num);
	*i += 2;
	return (1);
}

static int	handle_dollar_var(const char *line,
	int *i, t_buf_info *bi, t_shell *shell)
{
	(*i)++;
	if (append_var(line, i, bi, shell) < 0)
		return (-1);
	return (1);
}

int	handle_dollar(const char *line,
	int *i, t_buf_info *bi, t_shell *shell)
{
	if (line[*i + 1] == '?')
		return (handle_dollar_question(i, bi, shell->last_exit_status));
	else if (line[*i + 1] && (isalpha((unsigned char)line[*i + 1])
			|| line[*i + 1] == '_'))
		return (handle_dollar_var(line, i, bi, shell));
	else
	{
		if (ensure_buf_capacity(&(bi->buf), &(bi->buf_len), bi->pos, 1) < 0)
			return (-1);
		bi->buf[bi->pos++] = line[(*i)++];
	}
	return (1);
}
