/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:14:52 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/17 19:01:56 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

long long	parse_exit_number(char *arg, int *error)
{
	char		*endptr;
	long long	num;

	while (*arg && ft_isspace((unsigned char)*arg))
		arg++;
	if (arg[0] == '\x01')
		ft_strcpy(arg, arg + 1);
	errno = 0;
	num = ft_atoll(arg, &endptr);
	while (*endptr && ft_isspace((unsigned char)*endptr))
		endptr++;
	*error = 0;
	if (errno != 0 || *endptr != '\0' || arg[0] == '\0')
	{
		*error = 1;
		return (0);
	}
	if (ft_strlen(arg) == ft_strlen("-9223372036854775808")
		&& ft_strncmp(arg, "-9223372036854775808", ft_strlen(arg)) == 0)
		return (LLONG_MIN);
	return (num);
}

void	handle_exit_error(char **args, t_plchild_data *d, t_shell *shell)
{
	int	i;

	write(STDERR_FILENO, "exit: ", 6);
	write(STDERR_FILENO, args[1], ft_strlen(args[1]));
	write(STDERR_FILENO, ": numeric argument required\n", 28);
	if (d && d->cmds)
	{
		i = 0;
		while (d->cmds[i])
		{
			free_command(d->cmds[i]);
			i++;
		}
		free(d->cmds);
		d->cmds = NULL;
	}
	else
		free_str_array(args);
	close_inherited_fds();
	if (shell && shell->envp)
	{
		free_envp(shell->envp);
		shell->envp = NULL;
	}
	exit(2);
}

void	cleanup_exit_resources(char **args, t_plchild_data *d)
{
	int	i;

	free_str_array(args);
	if (d && d->cmds)
	{
		i = 0;
		while (d->cmds[i])
		{
			if (d->cmds[i]->args == args)
			{
				d->cmds[i]->args = NULL;
				break ;
			}
			i++;
		}
	}
	close_inherited_fds();
}

int	handle_exit_interactive(char **args, t_plchild_data *d,
	t_shell *shell, int argc)
{
	if (argc == 1)
	{
		write(2, "exit\n", 5);
		if (shell && shell->envp)
		{
			free_envp(shell->envp);
			shell->envp = NULL;
		}
		rl_clear_history();
		exit_no_args(args, d, shell);
	}
	if (argc > 2)
	{
		write(2, "exit\n", 5);
		write(2, "exit: too many arguments\n", 25);
		free_str_array(args);
		return (1);
	}
	write(2, "exit\n", 5);
	exit_with_args(args, d, shell, argc);
	return (0);
}

int	handle_exit_non_interactive(char **args, t_plchild_data *d,
	t_shell *shell, int argc)
{
	if (argc == 1)
	{
		if (shell && shell->envp)
		{
			free_envp(shell->envp);
			shell->envp = NULL;
		}
		rl_clear_history();
		exit_no_args(args, d, shell);
	}
	if (argc > 2)
	{
		write(2, "exit: too many arguments\n", 25);
		free_str_array(args);
		return (1);
	}
	exit_with_args(args, d, shell, argc);
	return (0);
}
