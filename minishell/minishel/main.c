/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:32:56 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/14 18:57:39 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int	g_parent_interrupted = 0;

static void	handle_twenty_fine_line(t_shell *shell)
{
	if (shell->envp)
		free_envp(shell->envp);
	shell->envp = NULL;
	rl_clear_history();
	close_inherited_fds();
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_shell			shell;
	t_plchild_data	d;

	ft_bzero(&d, sizeof(t_plchild_data));
	(void)argc;
	(void)argv;
	initialize_shell(&shell, envp);
	setup_signal_handlers();
	while (1)
	{
		line = readline("minishell> ");
		handle_interruption(&shell);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		process_input_line(line, &shell, &d);
	}
	handle_twenty_fine_line(&shell);
	return (shell.last_exit_status);
}

size_t	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}
