/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:52:02 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 16:22:33 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	*build_full_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

static size_t	path_segment_len(const char *p)
{
	const char	*colon;

	colon = ft_strchr(p, ':');
	if (colon)
		return ((size_t)(colon - p));
	return (ft_strlen(p));
}

static char	*try_stat_command(const char *full_path)
{
	struct stat	st;

	if (stat(full_path, &st) == 0)
	{
		if (!S_ISDIR(st.st_mode))
			return (ft_strdup(full_path));
	}
	return (NULL);
}

static char	*process_single_path_segment(char **p, const char *cmd)
{
	char	*res;
	size_t	len;
	char	*dir;
	char	*full;

	len = path_segment_len(*p);
	dir = malloc(len + 1);
	if (!dir)
		return (NULL);
	ft_memcpy(dir, *p, len);
	dir[len] = '\0';
	*p += len;
	if (**p == ':')
		(*p)++;
	full = build_full_path(dir, cmd);
	free(dir);
	if (!full)
		return (NULL);
	res = try_stat_command(full);
	free(full);
	return (res);
}

char	*search_in_path_loop(char *p, const char *cmd)
{
	char	*res;

	res = NULL;
	while (*p)
	{
		res = process_single_path_segment(&p, cmd);
		if (res)
			break ;
	}
	return (res);
}
