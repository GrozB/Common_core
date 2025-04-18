/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_allocation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:43:36 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 14:27:59 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_expansion.h"

int	expand_args_capacity(t_command *cmd, int *args_capacity)
{
	char	**temp;
	int		old_capacity;
	int		new_capacity;

	old_capacity = *args_capacity;
	new_capacity = old_capacity * 2;
	temp = malloc(sizeof(char *) * new_capacity);
	if (!temp)
		return (-1);
	ft_memcpy(temp, cmd->args, sizeof(char *) * old_capacity);
	ft_memset(temp + old_capacity, 0,
		sizeof(char *) * (new_capacity - old_capacity));
	free(cmd->args);
	cmd->args = temp;
	*args_capacity = new_capacity;
	return (0);
}

int	add_argument(t_command *cmd, char *arg,
	int *args_count, int *args_capacity)
{
	if (*args_count + 1 >= *args_capacity)
	{
		if (expand_args_capacity(cmd, args_capacity) < 0)
		{
			free(arg);
			return (-1);
		}
	}
	cmd->args[*args_count] = arg;
	(*args_count)++;
	cmd->args[*args_count] = NULL;
	return (0);
}

int	handle_split_words(t_command *cmd, char **words,
	int *args_count, int *args_capacity)
{
	int		k;
	char	*arg;

	k = 0;
	while (words[k])
	{
		arg = ft_strdup(words[k]);
		if (!arg || add_argument(cmd, arg, args_count, args_capacity) < 0)
		{
			free_str_array(words);
			return (-1);
		}
		k++;
	}
	free_str_array(words);
	return (0);
}

int	handle_argument(t_command *cmd, char *token,
	int *args_count, int *args_capacity)
{
	char	**words;
	char	*arg;

	if (token[0] == '\x01' || cmd->is_special_case
		|| (ft_strlen(token) > 0 && token[ft_strlen(token) - 1] == ' '))
	{
		if (token[0] == '\x01')
			arg = ft_strdup(token + 1);
		else
			arg = ft_strdup(token);
	}
	else
	{
		words = word_split(token);
		if (!words)
			return (-1);
		return (handle_split_words(cmd, words, args_count, args_capacity));
	}
	if (!arg || add_argument(cmd, arg, args_count, args_capacity) < 0)
		return (-1);
	return (0);
}

int	allocate_final_arguments(t_command *cmd, int args_count)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(char *) * (args_count + 1));
	if (!tmp)
		return (-1);
	i = 0;
	while (i < args_count)
	{
		tmp[i] = cmd->args[i];
		i++;
	}
	tmp[args_count] = NULL;
	free(cmd->args);
	cmd->args = tmp;
	return (0);
}
