/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_delimier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:26:00 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 17:32:04 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static char	*process_delimiter_quotes(const char *delimiter, int *no_expand)
{
	char	*real_delim;
	char	*tmp;

	real_delim = ft_strdup(delimiter);
	if (!real_delim)
		return (NULL);
	if (ft_strchr(real_delim, '\"') || ft_strchr(real_delim, '\''))
	{
		*no_expand = 1;
		tmp = remove_quotes(real_delim);
		free(real_delim);
		real_delim = tmp;
	}
	return (real_delim);
}

char	*process_delimiter(const char *delimiter,
	int last_exit_status, int *no_expand, t_shell *shell)
{
	char	*real_delim;
	char	*tmp;

	if (delimiter[0] == '\x01')
	{
		*no_expand = 1;
		real_delim = ft_strdup(delimiter + 1);
	}
	else
	{
		real_delim = process_delimiter_quotes(delimiter, no_expand);
		if (real_delim && !(*no_expand))
		{
			*no_expand = 0;
			tmp = expand_vars(real_delim, last_exit_status, shell);
			free(real_delim);
			real_delim = tmp;
		}
	}
	return (real_delim);
}

int	setup_signal_handler(struct sigaction *sa, struct sigaction *old_sa)
{
	sa->sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	if (sigaction(SIGINT, sa, old_sa) < 0)
		return (-1);
	return (0);
}

int	handle_line_input(int pipe_fd, char *line,
	char *cmp_line, int no_expand)
{
	const char	*to_write;

	if (no_expand)
		to_write = line;
	else
		to_write = cmp_line;
	if (write(pipe_fd, to_write, ft_strlen(to_write)) < 0
		|| write(pipe_fd, "\n", 1) < 0)
	{
		perror("write");
		return (-1);
	}
	return (0);
}

int	process_heredoc_line(char *line,
	char **cmp_line, t_heredoc_info *info, t_shell *shell)
{
	if (info->no_expand)
		*cmp_line = line;
	else
		*cmp_line = expand_vars(line, info->last_exit_status, shell);
	if (!(*cmp_line))
	{
		free(line);
		return (-1);
	}
	if (ft_strcmp(*cmp_line, info->real_delim) == 0)
	{
		if (!info->no_expand)
			free(*cmp_line);
		free(line);
		return (1);
	}
	return (0);
}
