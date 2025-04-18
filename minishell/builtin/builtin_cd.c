/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:55:08 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/18 13:21:23 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*check_env_path(const char *env_var, char *oldcwd, t_shell *shell)
{
	char	*target;

	target = my_getenv(shell, env_var);
	if (!target)
	{
		write(STDERR_FILENO, "cd: HOME not set\n", 18);
		free(oldcwd);
		return (NULL);
	}
	return (ft_strdup(target));
}

char	*cd_target(char **args, char *oldcwd, t_shell *shell)
{
	char	*target;

	if (!args)
	{
		free(oldcwd);
		return (NULL);
	}
	if (!args[1])
		target = check_env_path("HOME", oldcwd, shell);
	else if (ft_strcmp(args[1], "-") == 0)
		target = check_env_path("OLDPWD", oldcwd, shell);
	else if (args[1][0] == '~')
		target = cd_resolve_home(args[1], shell);
	else
		target = ft_strdup(args[1]);
	return (target);
}

static int	cd_change_directory(char **args,
	char *oldcwd, char **target, t_shell *shell)
{
	*target = cd_target(args, oldcwd, shell);
	if (!(*target))
		return (1);
	if (chdir(*target) != 0)
	{
		write(STDERR_FILENO, "cd: ", 4);
		write(STDERR_FILENO, *target, ft_strlen(*target));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, custom_strerror(errno),
			ft_strlen(custom_strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
		free(oldcwd);
		free(*target);
		return (1);
	}
	return (0);
}

static int	cd_execute(char **args, char *oldcwd, t_shell *shell)
{
	char	*target;
	char	*newcwd;
	char	*temp;

	if (cd_change_directory(args, oldcwd, &target, shell) != 0)
		return (1);
	if (args[1] && ft_strcmp(args[1], "-") == 0)
	{
		temp = getcwd(NULL, 0);
		if (temp)
		{
			printf("%s\n", temp);
			free(temp);
		}
	}
	newcwd = getcwd(NULL, 0);
	if (!newcwd)
	{
		free(oldcwd);
		return (1);
	}
	free(target);
	return (cd_update_env(shell, oldcwd, newcwd));
}

int	builtin_cd(t_shell *shell, char **args)
{
	int		argc;
	char	*oldcwd;

	argc = 0;
	while (args && args[argc])
		argc++;
	if (argc > 2)
	{
		write(2, "cd: too many arguments\n", 23);
		return (1);
	}
	oldcwd = getcwd(NULL, 0);
	if (!oldcwd)
		return (1);
	return (cd_execute(args, oldcwd, shell));
}
