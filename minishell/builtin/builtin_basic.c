/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_basic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:36:33 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/17 18:25:01 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	echo_flags(char **args, int *i)
{
	int	j;
	int	n_flag;

	n_flag = 0;
	while (args[*i] && args[*i][0] == '-' && args[*i][1] == 'n')
	{
		j = 1;
		while (args[*i][j] == 'n')
			j++;
		if (args[*i][j] != '\0')
			break ;
		n_flag = 1;
		(*i)++;
	}
	return (n_flag);
}

int	builtin_echo(char **args)
{
	int	i;
	int	n_flag;

	if (!args || !args[1])
	{
		printf("\n");
		return (0);
	}
	i = 1;
	n_flag = echo_flags(args, &i);
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}

int	builtin_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}

int	builtin_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp && shell->envp[i])
	{
		if (ft_strchr(shell->envp[i], '='))
		{
			write(1, shell->envp[i], ft_strlen(shell->envp[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	return (0);
}
