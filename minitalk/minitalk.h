/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:05:44 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/10 18:19:48 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"

void	append_char_to_string(char **str, char c, int *len);
void	reset_and_print(char **str, int *len);
void	send_acknowledgment(pid_t client_pid);
void	reset_static_vars(int *bit_count, char *c);
void	handle_signal(int sig, siginfo_t *info, void *context);
void	init_server(void);

#endif
