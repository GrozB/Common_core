/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_dollar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:07:44 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 18:10:51 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	handle_dollar_dq_question(const char *input,
	int *i, t_buf_info *bi, int last_exit_status)
{
	int		j;
	char	*num;

	(void)input;
	*i = *i + 2;
	num = ft_itoa(last_exit_status);
	if (!num)
		return (-1);
	j = 0;
	while (num[j])
	{
		if (ensure_buf_capacity(&(bi->buf), &(bi->buf_len), bi->pos, 1) < 0)
		{
			free(num);
			return (-1);
		}
		bi->buf[bi->pos++] = num[j];
		j++;
	}
	free(num);
	return (0);
}

int	handle_dollar_dq_default(const char *input, int *i, t_buf_info *bi)
{
	(void)input;
	if (ensure_buf_capacity(&(bi->buf), &(bi->buf_len), bi->pos, 1) < 0)
		return (-1);
	bi->buf[bi->pos++] = '$';
	*i = *i + 1;
	return (0);
}
