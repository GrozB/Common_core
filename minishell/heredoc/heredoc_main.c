/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:28:13 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 17:28:31 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static int	process_here_doc_loop(int *pipe_fd,
	t_heredoc_info *info, t_shell *shell)
{
	if (heredoc_loop(pipe_fd[1], info->real_delim,
			info->no_expand, shell) < 0)
		return (-1);
	return (0);
}

int	handle_here_doc(const char *delimiter, int last_exit_status, t_shell *shell)
{
	struct sigaction	sa;
	struct sigaction	old_sa;
	int					pipe_fd[2];
	t_heredoc_info		info;

	ft_bzero(&info, sizeof(t_heredoc_info));
	info.last_exit_status = last_exit_status;
	info.shell = shell;
	g_parent_interrupted = 0;
	if (!delimiter)
		return (-1);
	if (init_here_doc(delimiter, &info, &sa, &old_sa) < 0)
		return (-1);
	if (create_pipe(pipe_fd, &info, &old_sa) < 0)
		return (-1);
	if (process_here_doc_loop(pipe_fd, &info, shell) < 0)
		return (finalize_here_doc(pipe_fd, &info, &old_sa, -1));
	return (finalize_here_doc(pipe_fd, &info, &old_sa, 0));
}
