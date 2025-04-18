/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:27:14 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 17:35:27 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

int	handle_heredoc_line(int pipe_fd, char *line,
	t_heredoc_info *info, t_shell *shell)
{
	char	*cmp_line;
	int		result;

	result = process_heredoc_line(line, &cmp_line, info, shell);
	if (result != 0)
		return (result);
	if (handle_line_input(pipe_fd, line, cmp_line, info->no_expand) < 0)
	{
		if (!info->no_expand)
			free(cmp_line);
		free(line);
		return (-1);
	}
	if (!info->no_expand)
		free(cmp_line);
	free(line);
	return (0);
}

int	heredoc_loop(int pipe_fd, char *real_delim,
	int no_expand, t_shell *shell)
{
	t_heredoc_info	info;
	int				line_number;
	int				result;

	info.real_delim = real_delim;
	info.last_exit_status = shell->last_exit_status;
	info.no_expand = no_expand;
	line_number = 1;
	while (1)
	{
		if (g_parent_interrupted)
			return (-1);
		result = process_heredoc_input(pipe_fd, &info, &line_number, shell);
		if (result == 1)
			break ;
		else if (result < 0)
			return (-1);
	}
	return (0);
}

int	init_here_doc(const char *delimiter, t_heredoc_info *info,
	struct sigaction *sa, struct sigaction *old_sa)
{
	info->real_delim = process_delimiter(delimiter,
			info->last_exit_status, &info->no_expand, info->shell);
	if (!info->real_delim)
		return (-1);
	if (setup_signal_handler(sa, old_sa) < 0)
	{
		free(info->real_delim);
		return (-1);
	}
	return (0);
}

int	create_pipe(int *pipe_fd, t_heredoc_info *info,
	struct sigaction *old_sa)
{
	size_t		ft_strlen(const char *s);

	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		free(info->real_delim);
		sigaction(SIGINT, old_sa, NULL);
		return (-1);
	}
	return (0);
}

int	finalize_here_doc(int *pipe_fd, t_heredoc_info *info,
	struct sigaction *old_sa, int result)
{
	close(pipe_fd[1]);
	free(info->real_delim);
	sigaction(SIGINT, old_sa, NULL);
	if (result < 0)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	return (pipe_fd[0]);
}
