/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_apply.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:50:08 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 19:52:10 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	apply_single_redirection(t_redir *r,
	t_command *cmd, t_plchild_data *d, t_shell *shell)
{
	if (r->type == REDIR_IN)
		handle_in_redir(r, cmd, d, shell);
	else if (r->type == REDIR_OUT)
		handle_out_redir(r->filename);
	else if (r->type == REDIR_OUT_APPEND)
		handle_append_redir(r->filename);
	else if (r->type == REDIR_HEREDOC)
		handle_heredoc_redirect(r->here_doc_fd);
}

void	apply_redirections(t_command *cmd, t_plchild_data *d, t_shell *shell)
{
	int	i;

	i = 0;
	while (i < cmd->nb_redirs)
	{
		apply_single_redirection(&cmd->redirs[i], cmd, d, shell);
		i++;
	}
}

void	free_commands(t_command **cmds, int num_commands)
{
	int	i;

	i = 0;
	while (i < num_commands)
	{
		free_command(cmds[i]);
		i++;
	}
	free(cmds);
}

void	close_heredoc_fds(t_command *cmd)
{
	int	r;

	r = 0;
	while (r < cmd->nb_redirs)
	{
		if (cmd->redirs[r].type == REDIR_HEREDOC)
			close(cmd->redirs[r].here_doc_fd);
		r++;
	}
}

void	close_heredoc_fds_pipeline(t_command *cmd)
{
	int	r;

	r = 0;
	while (r < cmd->nb_redirs)
	{
		if (cmd->redirs[r].type == REDIR_HEREDOC)
			close(cmd->redirs[r].here_doc_fd);
		r++;
	}
}
