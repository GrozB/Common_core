/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:59:50 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 17:01:59 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	env_count(char **env)
{
	int	n;

	n = 0;
	while (env[n])
		n++;
	return (n);
}

char	*create_env_entry_v1(const char *cmd_path)
{
	char	*tmp;

	tmp = malloc(ft_strlen(cmd_path) + 3);
	if (!tmp)
		return (NULL);
	ft_strcpy(tmp, "_=");
	ft_strcpy(tmp + 2, cmd_path);
	return (tmp);
}

char	**allocate_env_array(int size)
{
	char	**res;

	res = (char **)malloc(sizeof(char *) * (size + 2));
	if (!res)
		return (NULL);
	return (res);
}

int	copy_env_entry(char **res, char *env_entry, int j)
{
	int	k;

	res[j] = ft_strdup(env_entry);
	if (!res[j])
	{
		k = 0;
		while (k < j)
			free(res[k++]);
		free(res);
		return (0);
	}
	return (1);
}

char	**build_envp(t_shell *shell, const char *cmd_path)
{
	char	**res;
	int		size;
	int		found;

	size = env_count(shell->envp);
	res = copy_env_with_cmd_path(shell, cmd_path, size, &found);
	if (!res)
		return (NULL);
	if (!found)
		res = add_cmd_path_to_env(res, cmd_path);
	return (res);
}
