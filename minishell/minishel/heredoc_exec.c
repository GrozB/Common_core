/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:32:56 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 16:42:42 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_parent_interrupted = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	ioctl(STDIN_FILENO, TIOCSTI);
	rl_done = 1;
}

int	process_heredoc_line_input(int *fd_line, char *line,
		t_heredoc_info *info, t_shell *shell)
{
	int	result;

	if (g_parent_interrupted)
	{
		free(line);
		return (-1);
	}
	result = handle_heredoc_line(fd_line[0], line, info, shell);
	if (result != 0)
		return (result);
	fd_line[1]++;
	return (0);
}

int	process_heredoc_input(int pipe_fd,
		t_heredoc_info *info, int *line_number, t_shell *shell)
{
	char	*line;
	int		fd_line[2];

	if (g_parent_interrupted)
		return (-1);
	line = readline("heredoc> ");
	if (!line)
	{
		if (g_parent_interrupted)
			return (-1);
		return (handle_heredoc_warning(line_number, info));
	}
	fd_line[0] = pipe_fd;
	fd_line[1] = *line_number;
	return (process_heredoc_line_input(fd_line, line, info, shell));
}
