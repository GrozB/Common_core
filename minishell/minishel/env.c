/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:32:56 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 16:55:48 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int	count_env(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

char	**copy_envp(char **envp)
{
	int		count;
	int		i;
	char	**new_envp;
	int		j;

	count = count_env(envp);
	new_envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			j = 0;
			while (j < i)
				free(new_envp[j++]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

void	initialize_shell(t_shell *shell, char **envp)
{
	shell->last_exit_status = 0;
	shell->envp = copy_envp(envp);
}
