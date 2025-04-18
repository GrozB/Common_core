/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_finalize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:43:50 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 15:47:40 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_expansion.h"

int	handle_empty_arguments(t_command *cmd)
{
	free(cmd->args);
	cmd->args = malloc(sizeof(char *) * 2);
	if (!cmd->args)
		return (-1);
	cmd->args[0] = ft_strdup("");
	cmd->args[1] = NULL;
	if (!cmd->args[0])
	{
		free(cmd->args);
		cmd->args = NULL;
		return (-1);
	}
	return (0);
}

int	finalize_arguments(t_command *cmd, int args_count)
{
	if (allocate_final_arguments(cmd, args_count) < 0)
		return (-1);
	if (args_count == 0 && cmd->nb_redirs == 0)
	{
		if (handle_empty_arguments(cmd) < 0)
			return (-1);
	}
	return (0);
}

int	process_tokens_env(t_command *cmd, char ***tokens, int *env, t_shell *shell)
{
	while (**tokens)
	{
		if (is_redirection(**tokens))
		{
			if (handle_redirection(cmd, tokens, env[0], shell) < 0)
				return (-1);
			continue ;
		}
		if (handle_argument(cmd, **tokens, &env[1], &env[2]) < 0)
			return (-1);
		(*tokens)++;
	}
	return (0);
}
