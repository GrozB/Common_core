/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:47:55 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 19:50:45 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	open_in_redir_file(t_redir *redir,
	t_command *cmd, t_plchild_data *d, t_shell *shell)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
	{
		perror(redir->filename);
		free_command(cmd);
		if (d && d->pids)
		{
			free(d->pids);
			d->pids = NULL;
		}
		if (shell && shell->envp)
		{
			free_envp(shell->envp);
			shell->envp = NULL;
		}
		exit(1);
	}
	return (fd);
}

void	handle_in_redir(t_redir *redir, t_command *cmd,
	t_plchild_data *d, t_shell *shell)
{
	int	fd;

	fd = open_in_redir_file(redir, cmd, d, shell);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		free_command(cmd);
		if (d && d->pids)
		{
			free(d->pids);
			d->pids = NULL;
		}
		exit(1);
	}
	close(fd);
}

void	handle_out_redir(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		perror(filename);
		exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit(1);
	}
	close(fd);
}

void	handle_append_redir(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
	{
		perror(filename);
		exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit(1);
	}
	close(fd);
}

void	handle_heredoc_redirect(int here_doc_fd)
{
	if (dup2(here_doc_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(here_doc_fd);
		exit(1);
	}
	close(here_doc_fd);
}
