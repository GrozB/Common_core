/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:46:42 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 16:27:57 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	putstr_stderr(const char *s)
{
	if (!s)
		return ;
	write(STDERR_FILENO, s, ft_strlen(s));
}

static void	putendl_stderr(const char *s)
{
	putstr_stderr(s);
	write(STDERR_FILENO, "\n", 1);
}

void	err_msg(const char *prefix, const char *message)
{
	if (!prefix || !message)
		return ;
	putstr_stderr(prefix);
	write(STDERR_FILENO, ": ", 2);
	putendl_stderr(message);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
