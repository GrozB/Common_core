/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:58:16 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 16:14:50 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	handle_in_builtin(t_redir *r, int saved_in, int saved_out)
{
	int	fd;

	fd = open(r->filename, O_RDONLY);
	if (fd < 0)
	{
		perror(r->filename);
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		perror("dup2");
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		return (1);
	}
	close(fd);
	return (0);
}

static int	handle_out_builtin(t_redir *r, int saved_in, int saved_out)
{
	int	fd;

	fd = open(r->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(r->filename);
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		perror("dup2");
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		return (1);
	}
	close(fd);
	return (0);
}

static int	handle_append_builtin(t_redir *r, int saved_in, int saved_out)
{
	int	fd;

	fd = open(r->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(r->filename);
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		perror("dup2");
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		return (1);
	}
	close(fd);
	return (0);
}

static int	handle_heredoc_builtin(t_redir *r, int saved_in, int saved_out)
{
	if (dup2(r->here_doc_fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		return (1);
	}
	close(r->here_doc_fd);
	return (0);
}

int	single_redir(t_redir *redir, int saved_in, int saved_out)
{
	if (redir->type == REDIR_IN)
	{
		if (handle_in_builtin(redir, saved_in, saved_out))
			return (1);
	}
	else if (redir->type == REDIR_OUT)
	{
		if (handle_out_builtin(redir, saved_in, saved_out))
			return (1);
	}
	else if (redir->type == REDIR_OUT_APPEND)
	{
		if (handle_append_builtin(redir, saved_in, saved_out))
			return (1);
	}
	else if (redir->type == REDIR_HEREDOC)
	{
		if (handle_heredoc_builtin(redir, saved_in, saved_out))
			return (1);
	}
	return (0);
}
