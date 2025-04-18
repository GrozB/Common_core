/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:58:33 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/17 18:24:41 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha((unsigned char)str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		if (!ft_isalnum((unsigned char)str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_export(t_shell *shell, char **args)
{
	if (!args || !args[1])
		return (export_print(shell));
	return (export_set_vars(shell, args));
}

int	export_print(t_shell *shell)
{
	char	**copy_envp;
	int		count;
	int		i;

	count = 0;
	while (shell->envp[count])
		count++;
	copy_envp = copy_env(shell->envp);
	if (!copy_envp)
		return (1);
	sort_env(copy_envp, count);
	i = 0;
	while (i < count)
	{
		print_export_var(copy_envp[i]);
		i++;
	}
	free(copy_envp);
	return (0);
}

int	export_set_var(t_shell *shell, char *arg)
{
	char	*eq;
	int		status;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return (handle_export_no_value(shell, arg));
	*eq = '\0';
	if (!is_valid_identifier(arg))
	{
		write(2, "minishell: export: `", 20);
		write(2, arg, ft_strlen(arg));
		write(2, "': not a valid identifier\n", 26);
		*eq = '=';
		return (1);
	}
	remove_plain_name(shell, arg);
	status = my_setenv(shell, arg, eq + 1, 1);
	*eq = '=';
	return (status);
}

int	export_set_vars(t_shell *shell, char **args)
{
	int	ret;
	int	i;

	i = 1;
	ret = 0;
	while (args[i])
	{
		ret |= export_set_var(shell, args[i]);
		i++;
	}
	return (ret);
}
