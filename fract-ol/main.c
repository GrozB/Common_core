/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:00:22 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/20 17:01:39 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	close_window(t_data *data)
{
	if (data->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

void	init_window(t_data *data)
{
	data->mlx_ptr = check_mlx_instance(mlx_init(),
			"Error: MLX initialization failed\n");
	data->win_ptr = check_mlx_instance(mlx_new_window(data->mlx_ptr,
				WIDTH, HEIGHT, "Fractal Window"),
			"Error: Window creation failed\n");
	data->img_ptr = check_mlx_instance(mlx_new_image(data->mlx_ptr,
				WIDTH, HEIGHT),
			"Error: Image creation failed\n");
	data->addr = mlx_get_data_addr(data->img_ptr, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	data->zoom = 1.0;
	data->offset_x = 0.0;
	data->offset_y = 0.0;
	data->color_mode = 0;
	data->fractal_type = 0;
	data->julia_c_re = -0.7;
	data->julia_c_im = 0.27015;
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_window(data);
	else if (keycode == 65361)
		data->offset_x -= 0.1 / data->zoom;
	else if (keycode == 65363)
		data->offset_x += 0.1 / data->zoom;
	else if (keycode == 65362)
		data->offset_y -= 0.1 / data->zoom;
	else if (keycode == 65364)
		data->offset_y += 0.1 / data->zoom;
	else if (keycode == 99)
	{
		data->color_mode = (data->color_mode + 1) % 4;
	}
	else if (keycode == 106)
		data->fractal_type = 1;
	else if (keycode == 109)
		data->fractal_type = 0;
	render_fractal(data);
	return (0);
}

int	zoom_hook(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 4)
		data->zoom *= 1.2;
	else if (button == 5)
		data->zoom /= 1.2;
	render_fractal(data);
	return (0);
}

int	main(void)
{
	t_data	data;

	init_window(&data);
	render_fractal(&data);
	mlx_hook(data.win_ptr, 17, 0, close_window, &data);
	mlx_mouse_hook(data.win_ptr, zoom_hook, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
