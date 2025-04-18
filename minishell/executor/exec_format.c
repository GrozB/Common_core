/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:59:02 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 15:59:31 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	needs_quoting(const char *token)
{
	const char	*p;

	p = token;
	while (*p)
	{
		if (!isprint((unsigned char)*p))
			return (1);
		p++;
	}
	return (0);
}

static size_t	append_nonprint(char *res, size_t pos, unsigned char c)
{
	const char	*hex = "0123456789ABCDEF";

	res[pos++] = '\\';
	res[pos++] = 'x';
	res[pos++] = hex[(c >> 4) & 0xF];
	res[pos++] = hex[c & 0xF];
	return (pos);
}

static size_t	append_escaped_char(char *res, size_t pos, unsigned char c)
{
	if (c == '\t')
	{
		res[pos++] = '\\';
		res[pos++] = 't';
	}
	else if (c == '\n')
	{
		res[pos++] = '\\';
		res[pos++] = 'n';
	}
	else if (c == '\'')
	{
		res[pos++] = '\\';
		res[pos++] = '\'';
	}
	else if (!isprint(c))
		pos = append_nonprint(res, pos, c);
	else
		res[pos++] = (char)c;
	return (pos);
}

static char	*quote_token(const char *token)
{
	size_t	len;
	size_t	buf_size;
	size_t	pos;
	size_t	i;
	char	*res;

	len = ft_strlen(token);
	buf_size = 3 + len * 4 + 1;
	res = malloc(buf_size);
	if (!res)
		return (NULL);
	ft_strcpy(res, "$'");
	pos = 2;
	i = 0;
	while (i < len)
	{
		pos = append_escaped_char(res, pos, (unsigned char)token[i]);
		i++;
	}
	res[pos++] = '\'';
	res[pos] = '\0';
	return (res);
}

char	*format_token(const char *token)
{
	if (!needs_quoting(token))
		return (ft_strdup(token));
	return (quote_token(token));
}
