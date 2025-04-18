/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_cases.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:52:39 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 18:50:33 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	handle_special_case(const char *input,
	int *i, t_buf_info *bi, int *unquoted)
{
	*unquoted = 1;
	if (handle_special_chars(input, i, bi) < 0)
		return (-1);
	return (1);
}

static int	handle_dollar_case(const char *input,
	int *i, t_buf_info *bi, t_parse_context *ctx)
{
	*(ctx->unquoted) = 1;
	*(ctx->had_var) = 1;
	if (handle_dollar_2(input, i, bi, ctx->shell) < 0)
		return (-1);
	return (0);
}

static int	handle_quote_case(const char *input,
	int *i, t_buf_info *bi, t_shell *shell)
{
	if (handle_quote(input, i, bi, shell) < 0)
		return (-1);
	return (0);
}

static int	handle_regular_case(const char *input,
	int *i, t_buf_info *bi, int *unquoted)
{
	*unquoted = 1;
	if (handle_regular_char(input, i, bi) < 0)
		return (-1);
	return (0);
}

int	process_token_char(const char *input,
	int *i, t_buf_info *bi, t_tok_ctx *ctx)
{
	t_parse_context	dctx;

	if (input[*i] == '>' || input[*i] == '<' || input[*i] == '|')
	{
		if (bi->pos > 0)
			return (1);
		return (handle_special_case(input, i, bi, &ctx->ti->unquoted));
	}
	else if (input[*i] == '$')
	{
		{
			dctx.shell = ctx->shell;
			dctx.unquoted = &ctx->ti->unquoted;
			dctx.had_var = &ctx->ti->had_var;
			return (handle_dollar_case(input, i, bi, &dctx));
		}
	}
	else if (input[*i] == '\"' || input[*i] == '\'')
		return (handle_quote_case(input, i, bi, ctx->shell));
	else
		return (handle_regular_case(input, i, bi, &ctx->ti->unquoted));
}
