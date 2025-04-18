/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:09:31 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/17 19:01:43 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	cleanup_and_exit(char **args, t_plchild_data *d, long long num)
{
	int	i;

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
	exit((unsigned char)num);
}

void	exit_no_args(char **args, t_plchild_data *d, t_shell *shell)
{
	int	i;

	cleanup_exit_resources(args, d);
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
	exit((unsigned char)shell->last_exit_status);
}

static void	exit_cleanup_and_execute(char **args,
	t_plchild_data *d, t_shell *shell, long long num)
{
	if (shell && shell->envp)
	{
		free_envp(shell->envp);
		shell->envp = NULL;
	}
	rl_clear_history();
	cleanup_and_exit(args, d, num);
}

void	exit_with_args(char **args, t_plchild_data *d,
	t_shell *shell, int argc)
{
	long long	num;
	int			error;

	num = parse_exit_number(args[1], &error);
	if (error)
		handle_exit_error(args, d, shell);
	if (argc > 2)
	{
		write(STDERR_FILENO, "exit: too many arguments\n", 25);
		exit_cleanup_and_execute(args, d, shell, 1);
	}
	exit_cleanup_and_execute(args, d, shell, num);
}

int	builtin_exit(char **args, t_plchild_data *d, t_shell *shell)
{
	int	argc;
	int	interactive;

	argc = 0;
	while (args[argc])
		argc++;
	interactive = (!d || !d->cmds);
	if (interactive)
		return (handle_exit_interactive(args, d, shell, argc));
	return (handle_exit_non_interactive(args, d, shell, argc));
}
