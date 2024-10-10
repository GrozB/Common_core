/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:11:56 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/10 18:12:24 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_acknowledgment(pid_t client_pid)
{
	kill(client_pid, SIGUSR1);
}

void	reset_static_vars(int *bit_count, char *c)
{
	*bit_count = 0;
	*c = 0;
}
