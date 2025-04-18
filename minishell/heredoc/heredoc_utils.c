/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:29:46 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 17:44:18 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

int	exit_status(int status)
{
	if ((status & 0x7F) == 0)
		return ((status >> 8) & 0xFF);
	return (128 + (status & 0x7F));
}

void	free_new_tokens_on_failure(char **new_tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(new_tokens[i]);
		i++;
	}
	free(new_tokens);
}
