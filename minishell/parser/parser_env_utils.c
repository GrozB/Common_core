/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:06:19 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 18:07:05 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*dup;

	if (!s)
		return (NULL);
	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_var_char(char c)
{
	return ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9')
		|| c == '_');
}

int	ensure_buf_capacity(char **buf, int *buf_len, int pos, int needed)
{
	int		new_size;
	char	*new_buf;

	if (pos + needed + 1 < *buf_len)
		return (0);
	new_size = *buf_len;
	while (pos + needed + 1 >= new_size)
		new_size *= 2;
	new_buf = malloc(new_size);
	if (!new_buf)
		return (-1);
	ft_memcpy(new_buf, *buf, pos);
	free(*buf);
	*buf = new_buf;
	*buf_len = new_size;
	return (0);
}

int	append_var(const char *input, int *i, t_buf_info *bi, t_shell *shell)
{
	int		start;
	char	*tmp;
	char	*val;
	int		j;

	start = *i;
	while (input[*i] && is_var_char(input[*i]))
		(*i)++;
	tmp = ft_strndup(input + start, *i - start);
	if (!tmp)
		return (-1);
	val = my_getenv(shell, tmp);
	free(tmp);
	if (!val)
		val = "";
	j = 0;
	while (val[j])
	{
		if (ensure_buf_capacity(&(bi->buf), &(bi->buf_len), bi->pos, 1) < 0)
			return (-1);
		bi->buf[bi->pos++] = val[j];
		j++;
	}
	return (0);
}
