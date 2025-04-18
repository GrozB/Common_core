/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:56:37 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 16:54:14 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	env_len(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

static char	**realloc_envp(char **old_envp, int new_size)
{
	char	**new_envp;
	int		i;

	i = 0;
	new_envp = (char **)malloc(sizeof(char *) * (new_size + 1));
	if (!new_envp)
		return (NULL);
	while (i < new_size && old_envp[i])
	{
		new_envp[i] = old_envp[i];
		i++;
	}
	new_envp[i] = NULL;
	free(old_envp);
	return (new_envp);
}

int	update_existing_env(t_shell *shell,
	int index, char *new_entry, int overwrite)
{
	if (!overwrite)
	{
		free(new_entry);
		return (0);
	}
	free(shell->envp[index]);
	shell->envp[index] = new_entry;
	return (0);
}

int	add_new_env(t_shell *shell, char *new_entry)
{
	int		old_env_len;
	char	**tmp;

	old_env_len = env_len(shell->envp);
	tmp = realloc_envp(shell->envp, old_env_len + 1);
	if (!tmp)
	{
		free(new_entry);
		return (-1);
	}
	shell->envp = tmp;
	shell->envp[old_env_len] = new_entry;
	shell->envp[old_env_len + 1] = NULL;
	return (0);
}

int	my_setenv(t_shell *shell, const char *name,
	const char *value, int overwrite)
{
	size_t	name_len;
	int		index;
	char	*new_entry;

	if (!shell || !shell->envp || !name || !value)
		return (-1);
	name_len = ft_strlen(name);
	index = find_env_index(shell, name, name_len);
	new_entry = create_env_entry(name, value);
	if (!new_entry)
		return (-1);
	if (index >= 0)
		return (update_existing_env(shell, index, new_entry, overwrite));
	return (add_new_env(shell, new_entry));
}
