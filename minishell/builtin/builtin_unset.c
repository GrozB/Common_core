/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:02:39 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/18 13:28:43 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_valid_unset_name(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (!ft_isalnum((unsigned char)str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	my_unsetenv(t_shell *shell, const char *name)
{
	size_t	name_len;
	int		index;
	int		i;
	int		old_env_len;

	if (!shell || !shell->envp || !name)
		return ;
	name_len = ft_strlen(name);
	index = find_env_index(shell, name, name_len);
	if (index < 0)
		return ;
	free(shell->envp[index]);
	old_env_len = env_len(shell->envp);
	i = index;
	while (i < old_env_len - 1)
	{
		shell->envp[i] = shell->envp[i + 1];
		i++;
	}
	shell->envp[i] = NULL;
}

int	builtin_unset(t_shell *shell, char **args)
{
	int	i;

	i = 1;
	if (!args || !args[1])
		return (0);
	while (args[i])
	{
		if (is_valid_unset_name(args[i]))
		{
			remove_plain_name(shell, args[i]);
			my_unsetenv(shell, args[i]);
		}
		i++;
	}
	return (0);
}

char	*cd_resolve_home(char *arg, t_shell *shell)
{
	char	*home;
	char	*target;

	home = my_getenv(shell, "HOME");
	if (!home)
	{
		write(STDERR_FILENO, "cd: HOME not set\n", 18);
		target = ft_strdup(arg);
	}
	else
		target = ft_strjoin(home, arg + 1);
	return (target);
}
