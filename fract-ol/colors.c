/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:06:08 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/20 17:08:45 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	red_mode(double t)
{
	int	red;
	int	green;
	int	blue;

	red = (int)(9 * (1 - t) * t * t * t * 255);
	green = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	blue = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return (red << 16 | green << 8 | blue);
}

int	green_mode(double t)
{
	int	red;
	int	green;
	int	blue;

	red = (int)(t * 255);
	green = (int)((1 - t) * 255);
	blue = (int)(t * 128);
	return (red << 16 | green << 8 | blue);
}

int	blue_mode(double t)
{
	int	red;
	int	green;
	int	blue;

	red = (int)(t * 128);
	green = (int)(t * 255);
	blue = (int)((1 - t) * 255);
	return (red << 16 | green << 8 | blue);
}

int	calculate_color(double t, int color_mode)
{
	if (color_mode == 1)
		return (red_mode(t));
	else if (color_mode == 2)
		return (green_mode(t));
	else if (color_mode == 3)
		return (blue_mode(t));
	else
		return (red_mode(t));
}

int	get_color(int n, int color_mode)
{
	double	t;

	if (n == MAX_ITER)
		return (0x000000);
	t = (double)n / (double)MAX_ITER;
	return (calculate_color(t, color_mode));
}
