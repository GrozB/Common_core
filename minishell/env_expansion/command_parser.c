/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:43:53 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 15:54:00 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_expansion.h"

t_command	*parse_command(char **tokens, int last_exit_status, t_shell *shell)
{
	t_command	*cmd;
	int			env[3];

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_command));
	env[0] = last_exit_status;
	env[1] = 0;
	env[2] = 10;
	cmd->is_special_case = tokens[0] && (ft_strcmp(tokens[0], "export") == 0
			|| ft_strcmp(tokens[0], "unset") == 0);
	cmd->args = malloc(sizeof(char *) * env[2]);
	if (!cmd->args)
		return (free(cmd), NULL);
	ft_memset(cmd->args, 0, sizeof(char *) * env[2]);
	if (process_tokens_env(cmd, &tokens, env, shell) < 0)
		return (free_command(cmd), NULL);
	if (finalize_arguments(cmd, env[1]) < 0)
		return (free_command(cmd), NULL);
	return (cmd);
}

void	free_command_resources(t_command *cmd)
{
	int	i;

	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->redirs)
	{
		i = 0;
		while (i < cmd->nb_redirs)
		{
			free(cmd->redirs[i].filename);
			if (cmd->redirs[i].here_doc_fd != -1)
				close(cmd->redirs[i].here_doc_fd);
			i++;
		}
		free(cmd->redirs);
	}
}

void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	free_command_resources(cmd);
	free(cmd);
}
