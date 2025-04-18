/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:41:12 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 18:53:31 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	handle_dollar_question_2(int *i, t_buf_info *bi, int last_exit_status)
{
	char	*num;
	int		k;

	num = ft_itoa(last_exit_status);
	if (!num)
		return (-1);
	k = 0;
	while (num[k])
	{
		if (ensure_buf_capacity(&(bi->buf), &(bi->buf_len), bi->pos, 1) < 0)
		{
			free(num);
			return (-1);
		}
		bi->buf[bi->pos++] = num[k++];
	}
	free(num);
	(*i) += 2;
	return (0);
}

static int	handle_dollar_variable(const char *input,
	int *i, t_buf_info *bi, t_shell *shell)
{
	(*i)++;
	if (input[*i] && (isalpha((unsigned char)input[*i]) || input[*i] == '_'))
	{
		if (append_var(input, i, bi, shell) < 0)
			return (-1);
	}
	else
	{
		if (ensure_buf_capacity(&(bi->buf), &(bi->buf_len), bi->pos, 1) < 0)
			return (-1);
		bi->buf[bi->pos++] = '$';
	}
	return (0);
}

int	handle_dollar_2(const char *input,
	int *i, t_buf_info *bi, t_shell *shell)
{
	if (input[*i + 1] == '?')
	{
		if (handle_dollar_question_2(i, bi, shell->last_exit_status) < 0)
			return (-1);
	}
	else
	{
		if (handle_dollar_variable(input, i, bi, shell) < 0)
			return (-1);
	}
	return (0);
}

static int	handle_dollar_dq_var(const char *input,
	int *i, t_buf_info *bi, t_shell *shell)
{
	*i = *i + 1;
	return (append_var(input, i, bi, shell));
}

int	handle_dollar_dq(const char *input,
	int *i, t_buf_info *bi, t_shell *shell)
{
	if (input[*i + 1] == '?')
		return (handle_dollar_dq_question(input, i,
				bi, shell->last_exit_status));
	else if (input[*i + 1] && (isalpha(input[*i + 1]) || input[*i + 1] == '_'))
		return (handle_dollar_dq_var(input, i, bi, shell));
	else
		return (handle_dollar_dq_default(input, i, bi));
}
