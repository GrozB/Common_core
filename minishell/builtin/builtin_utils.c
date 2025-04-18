/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:17:29 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 17:19:06 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

char	*my_getenv(t_shell *shell, const char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], name, len) == 0
			&& shell->envp[i][len] == '=')
			return (shell->envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	find_env_index(t_shell *shell, const char *name, size_t name_len)
{
	int	i;

	i = 0;
	while (shell->envp && shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], name, name_len) == 0
			&& shell->envp[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*create_env_entry(const char *name, const char *value)
{
	size_t	name_len;
	char	*new_entry;

	name_len = ft_strlen(name);
	new_entry = malloc(name_len + 1 + ft_strlen(value) + 1);
	if (!new_entry)
		return (NULL);
	ft_strcpy(new_entry, name);
	new_entry[name_len] = '=';
	ft_strcpy(new_entry + name_len + 1, value);
	return (new_entry);
}
