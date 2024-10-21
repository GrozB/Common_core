/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:23:13 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/20 16:27:22 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	*check_mlx_instance(void *ptr, const char *error_message)
{
	if (!ptr)
	{
		write(2, error_message, 33);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}
