/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_and_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:21:40 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/13 17:25:37 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	cd_update_env(t_shell *shell, char *oldcwd, char *newcwd)
{
	if (oldcwd)
	{
		if (my_setenv(shell, "OLDPWD", oldcwd, 1) != 0)
		{
			write(STDERR_FILENO, "cd: failed to set OLDPWD\n", 26);
			free(oldcwd);
			free(newcwd);
			return (1);
		}
		free(oldcwd);
	}
	if (my_setenv(shell, "PWD", newcwd, 1) != 0)
	{
		write(STDERR_FILENO, "cd: failed to set PWD\n", 23);
		free(newcwd);
		return (1);
	}
	free(newcwd);
	return (0);
}

const char	*custom_strerror(int errnum)
{
	if (errnum == EACCES)
		return ("Permission denied");
	else if (errnum == ENOENT)
		return ("No such file or directory");
	else if (errnum == ENOTDIR)
		return ("Not a directory");
	else if (errnum == ELOOP)
		return ("Too many symbolic links encountered");
	else if (errnum == ENAMETOOLONG)
		return ("File name too long");
	else if (errnum == EIO)
		return ("Input/output error");
	else
		return ("Unknown error");
}
