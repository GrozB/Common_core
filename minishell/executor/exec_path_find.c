/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_find.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:52:56 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/18 12:59:21 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*search_in_path(const char *path_env, const char *cmd)
{
	char	*path_copy;
	char	*res;

	path_copy = ft_strdup(path_env);
	res = NULL;
	if (!path_copy)
		return (NULL);
	res = search_in_path_loop(path_copy, cmd);
	free(path_copy);
	return (res);
}

char	*find_command_path(t_shell *shell, const char *cmd)
{
	char	*path_env;
	char	*found;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = my_getenv(shell, "PATH");
	if (!path_env || !*path_env)
		path_env = ".";
	found = search_in_path(path_env, cmd);
	return (found);
}

void	check_if_directory(t_command *cmd, char *cmd_path)
{
	struct stat	st;

	if (stat(cmd->args[0], &st) == 0 && S_ISDIR(st.st_mode))
	{
		err_msg(cmd->args[0], "Is a directory");
		free(cmd_path);
		free_command(cmd);
		exit(126);
	}
}

void	print_error_message(const char *cmd_name)
{
	if (errno == EACCES)
		err_msg(cmd_name, "Permission denied");
	else if (errno == ENOENT || errno == ENOTDIR)
		err_msg(cmd_name, "No such file or directory");
	else if (errno == ENOEXEC)
		err_msg(cmd_name, "Exec format error");
	else if (errno == EISDIR)
		err_msg(cmd_name, "Is a directory");
	else
		err_msg(cmd_name, "command not found");
}

int	get_exit_code_by_errno(void)
{
	if (errno == EACCES)
		return (126);
	if (errno == ENOENT)
		return (127);
	if (errno == ENOTDIR)
		return (126);
	if (errno == ENOEXEC)
		return (126);
	if (errno == EISDIR)
		return (126);
	return (1);
}
