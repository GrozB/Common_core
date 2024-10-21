/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:02:20 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/21 17:57:00 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"

void	send_bit(pid_t pid, char bit);
void	send_char(pid_t pid, char c);
void	acknowledge_signal(int sig);
void	send_size(pid_t pid, size_t size);
void	send_message(pid_t pid, const char *message);

typedef struct s_message
{
	int				bit_count;
	size_t			size;
	size_t			received;
	char			*message;
	int				state;
	unsigned char	c;
}				t_message;

#endif