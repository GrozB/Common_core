/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:01:12 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 16:58:16 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	**handle_env_entry(const char *cmd_path,
	char **res, int *found, int j)
{
	int	k;

	res[j] = create_env_entry_v1(cmd_path);
	if (!res[j])
	{
		k = 0;
		while (k < j)
			free(res[k++]);
		free(res);
		return (NULL);
	}
	*found = 1;
	return (res);
}

static char	**process_env_entries(t_shell *shell,
	const char *cmd_path, char **res, int *found)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (shell->envp[i])
	{
		if (shell->envp[i][0] == '_' && shell->envp[i][1] == '=')
		{
			res = handle_env_entry(cmd_path, res, found, j);
			if (!res)
				return (NULL);
		}
		else
		{
			if (!copy_env_entry(res, shell->envp[i], j))
				return (NULL);
		}
		j++;
		i++;
	}
	res[j] = NULL;
	return (res);
}

static char	**populate_env_array(t_shell *shell,
	const char *cmd_path, char **res, int *found)
{
	return (process_env_entries(shell, cmd_path, res, found));
}

char	**copy_env_with_cmd_path(t_shell *shell,
	const char *cmd_path, int size, int *found)
{
	char	**res;

	res = allocate_env_array(size);
	if (!res)
		return (NULL);
	*found = 0;
	return (populate_env_array(shell, cmd_path, res, found));
}

char	**add_cmd_path_to_env(char **res, const char *cmd_path)
{
	int	j;
	int	k;

	j = 0;
	while (res[j])
		j++;
	res[j] = create_env_entry_v1(cmd_path);
	if (!res[j])
	{
		k = 0;
		while (k < j)
			free(res[k++]);
		free(res);
		return (NULL);
	}
	res[j + 1] = NULL;
	return (res);
}
