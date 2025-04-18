/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_builder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:50:01 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 17:52:13 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*finalize_buffer_with_prefix(t_buf_info *bi)
{
	char	*new_buf;
	int		new_len;

	new_len = bi->pos + 2;
	new_buf = malloc(new_len);
	if (!new_buf)
	{
		free(bi->buf);
		return (NULL);
	}
	new_buf[0] = '\x01';
	ft_strcpy(new_buf + 1, bi->buf);
	free(bi->buf);
	return (new_buf);
}

static char	*finalize_buffer(t_buf_info *bi, int unquoted, int had_var)
{
	char	*new_buf;

	if (ensure_buf_capacity(&(bi->buf), &(bi->buf_len), bi->pos, 1) < 0)
	{
		free(bi->buf);
		return (NULL);
	}
	bi->buf[bi->pos] = '\0';
	if (!unquoted || (had_var && (ft_strcmp(bi->buf, ">") == 0
				|| ft_strcmp(bi->buf, ">>") == 0 || ft_strcmp(bi->buf, "<") == 0
				|| ft_strcmp(bi->buf, "<<") == 0
				|| ft_strcmp(bi->buf, "|") == 0)))
		return (finalize_buffer_with_prefix(bi));
	new_buf = ft_strdup(bi->buf);
	free(bi->buf);
	return (new_buf);
}

char	*initialize_token_builder(t_buf_info *bi)
{
	bi->buf_len = 64;
	bi->buf = malloc(bi->buf_len);
	if (!bi->buf)
		return (NULL);
	bi->pos = 0;
	return (bi->buf);
}

char	*token_builder(const char *input, int *i,
	int last_exit_status, t_shell *shell)
{
	t_token_info	ti;
	t_buf_info		bi;
	t_tok_ctx		ctx;
	int				result;

	ti.unquoted = 0;
	ti.had_var = 0;
	ti.last_exit_status = last_exit_status;
	if (!initialize_token_builder(&bi))
		return (NULL);
	ctx.ti = &ti;
	ctx.shell = shell;
	while (input[*i] && !is_whitespace(input[*i]))
	{
		result = process_token_char(input, i, &bi, &ctx);
		if (result < 0)
		{
			free(bi.buf);
			return (NULL);
		}
		if (result > 0)
			break ;
	}
	return (finalize_buffer(&bi, ti.unquoted, ti.had_var));
}

char	*g_empty_str(void)
{
	return ("");
}
