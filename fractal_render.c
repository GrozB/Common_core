/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:00:28 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/20 17:05:47 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	mandelbrot(double re, double im)
{
	t_complex	z;
	t_complex	c;
	int			n;
	double		temp;

	z.re = 0;
	z.im = 0;
	c.re = re;
	c.im = im;
	n = 0;
	while (n < MAX_ITER && (z.re * z.re + z.im * z.im) <= 4)
	{
		temp = z.re * z.re - z.im * z.im + c.re;
		z.im = 2 * z.re * z.im + c.im;
		z.re = temp;
		n++;
	}
	return (n);
}

int	julia(double z_re, double z_im, double c_re, double c_im)
{
	t_complex	z;
	int			n;
	double		temp;

	z.re = z_re;
	z.im = z_im;
	n = 0;
	while (n < MAX_ITER && (z.re * z.re + z.im * z.im) <= 4)
	{
		temp = z.re * z.re - z.im * z.im + c_re;
		z.im = 2 * z.re * z.im + c_im;
		z.re = temp;
		n++;
	}
	return (n);
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render_fractal_helper(t_data *data, int x, int y)
{
	double	re;
	double	im;
	int		color;
	int		n;

	re = (x - WIDTH / 2.0) * 4.0 / WIDTH / data->zoom + data->offset_x;
	im = (y - HEIGHT / 2.0) * 4.0 / HEIGHT / data->zoom + data->offset_y;
	if (data->fractal_type == 0)
		n = mandelbrot(re, im);
	else
		n = julia(re, im, data->julia_c_re, data->julia_c_im);
	color = get_color(n, data->color_mode);
	put_pixel(data, x, y, color);
}

void	render_fractal(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			render_fractal_helper(data, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}
