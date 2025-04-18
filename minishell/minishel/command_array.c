/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:32:56 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 16:37:03 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

t_command	**allocate_command_array(int count)
{
	t_command	**cmds;

	cmds = malloc(sizeof(t_command *) * (count + 1));
	if (!cmds)
		return (NULL);
	return (cmds);
}

void	free_command_array(t_command **cmds, int cmd_index)
{
	while (cmd_index > 0)
		free_command(cmds[--cmd_index]);
	free(cmds);
}
