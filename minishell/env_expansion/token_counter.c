/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_counter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:44:31 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 14:30:17 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_expansion.h"

int	count_tokens(const char *input, int last_exit_status, t_shell *shell)
{
	int		i;
	int		count;
	char	*token;

	count = 0;
	i = 0;
	while (input[i])
	{
		while (input[i] && is_whitespace(input[i]))
			i++;
		if (!input[i])
			break ;
		token = token_builder(input, &i, last_exit_status, shell);
		if (!token)
			return (-1);
		count++;
		free(token);
	}
	return (count);
}
