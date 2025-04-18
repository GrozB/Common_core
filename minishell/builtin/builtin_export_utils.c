/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:01:29 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/13 17:30:26 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	**copy_env(char **envp)
{
	int		count;
	char	**copy;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = envp[i];
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	sort_env(char **env, int size)
{
	int		sorted;
	int		i;
	char	*tmp;

	if (size < 2)
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(env[i], env[i + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
}

static void	get_key(char *env_entry, char *key_buf, int *key_len)
{
	char	*eq;

	eq = ft_strchr(env_entry, '=');
	*key_len = eq - env_entry;
	if (*key_len >= 256)
		*key_len = 255;
	ft_strlcpy(key_buf, env_entry, *key_len + 1);
}

void	print_export_var(char *env_entry)
{
	char	*eq;
	int		key_len;
	char	key_buf[256];
	int		shlvl;

	eq = ft_strchr(env_entry, '=');
	if (eq)
	{
		get_key(env_entry, key_buf, &key_len);
		if (ft_strcmp(key_buf, "_") == 0)
			return ;
		if (ft_strcmp(key_buf, "SHLVL") == 0)
		{
			shlvl = ft_atoi(eq + 1);
			printf("export %s=\"%d\"\n", key_buf, shlvl);
		}
		else
			printf("export %s=\"%s\"\n", key_buf, eq + 1);
	}
	else
		printf("export %s\n", env_entry);
}

int	export_set_with_value(t_shell *shell, char *arg, char *eq)
{
	int		key_len;
	char	*key;

	key_len = (int)(eq - arg);
	key = ft_substr(arg, 0, key_len);
	if (!key)
	{
		write(STDERR_FILENO, "export: memory allocation error\n", 32);
		return (1);
	}
	if (my_setenv(shell, key, eq + 1, 1) != 0)
	{
		write(STDERR_FILENO, "export: failed to set variable: ", 32);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, "\n", 1);
		free(key);
		return (1);
	}
	free(key);
	return (0);
}
