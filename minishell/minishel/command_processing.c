/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:32:56 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 16:37:55 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

t_command	*process_segment(char **tokens, int *p, t_shell *shell)
{
	char		**seg;
	t_command	*cmd;

	if (!tokens || (p[1] - p[0]) <= 0)
	{
		if ((p[1] - p[0]) <= 0)
			write(STDERR_FILENO,
				"minishell: syntax error: empty command\n", 39);
		return (NULL);
	}
	seg = build_segment(tokens, p[0], p[1] - p[0]);
	if (!seg)
		return (NULL);
	cmd = parse_command(seg, p[2], shell);
	free_segment(seg);
	return (cmd);
}

t_command	*process_command_segment(char **tokens, int *seg, t_shell *shell)
{
	t_command	*cmd;

	cmd = process_segment(tokens, seg, shell);
	if (!cmd)
		return (NULL);
	return (cmd);
}

int	process_commands(char **tokens, t_command **cmds, int *info, t_shell *shell)
{
	int	i;
	int	seg[3];
	int	cmd_index;

	i = 0;
	cmd_index = 0;
	while (tokens[i])
	{
		seg[0] = i;
		seg[1] = next_pipe(tokens, i);
		seg[2] = info[0];
		cmds[cmd_index] = process_command_segment(tokens, seg, shell);
		if (!cmds[cmd_index])
			return (-1);
		cmd_index++;
		if (tokens[seg[1]])
			i = seg[1] + 1;
		else
			i = seg[1];
	}
	cmds[cmd_index] = NULL;
	info[1] = cmd_index;
	return (0);
}

t_command	**split_commands(char **tokens, int *num_commands,
	int last_exit_status, t_shell *shell)
{
	int			count;
	t_command	**cmds;
	int			info[2];

	if (validate_split_conditions(tokens, num_commands) < 0)
		return (NULL);
	count = count_pipes(tokens) + 1;
	cmds = allocate_command_array(count);
	if (!cmds)
		return (NULL);
	info[0] = last_exit_status;
	info[1] = 0;
	if (process_commands(tokens, cmds, info, shell) < 0)
	{
		free_command_array(cmds, *num_commands);
		return (NULL);
	}
	*num_commands = info[1];
	return (cmds);
}
