/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:21:08 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/17 18:26:25 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_name_in_env(char **envp, const char *name)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strcmp(envp[i], name)
			|| (ft_strncmp(envp[i], name, ft_strlen(name)) == 0
				&& envp[i][ft_strlen(name)] == '='))
			return (1);
		i++;
	}
	return (0);
}

static char	**create_new_env_with_name(char **envp, const char *name)
{
	int		n;
	int		i;
	char	**new_env;
	char	*entry;

	n = env_count(envp);
	new_env = malloc(sizeof(char *) * (n + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < n)
	{
		new_env[i] = envp[i];
		i++;
	}
	entry = ft_strdup(name);
	if (!entry)
	{
		free(new_env);
		return (NULL);
	}
	new_env[i++] = entry;
	new_env[i] = NULL;
	return (new_env);
}

int	add_name_no_value(t_shell *shell, const char *name)
{
	char	**new_env;

	if (is_name_in_env(shell->envp, name))
		return (0);
	new_env = create_new_env_with_name(shell->envp, name);
	if (!new_env)
		return (1);
	free(shell->envp);
	shell->envp = new_env;
	return (0);
}

void	remove_plain_name(t_shell *shell, const char *name)
{
	int	i;
	int	j;

	if (!shell->envp)
		return ;
	i = 0;
	while (shell->envp[i])
	{
		if (ft_strcmp(shell->envp[i], name) == 0)
		{
			free(shell->envp[i]);
			j = i;
			while (shell->envp[j + 1])
			{
				shell->envp[j] = shell->envp[j + 1];
				j++;
			}
			shell->envp[j] = NULL;
			return ;
		}
		i++;
	}
}

int	handle_export_no_value(t_shell *shell, char *arg)
{
	if (!is_valid_identifier(arg))
	{
		write(2, "minishell: export: `", 20);
		write(2, arg, ft_strlen(arg));
		write(2, "': not a valid identifier\n", 26);
		return (1);
	}
	return (add_name_no_value(shell, arg));
}
