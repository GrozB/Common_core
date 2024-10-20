/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:05:53 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/20 17:07:03 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 600
# define MAX_ITER 100

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	zoom;
	double	offset_x;
	double	offset_y;
	int		color_mode;
	int		fractal_type;
	double	julia_c_re;
	double	julia_c_im;
}	t_data;

typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;

void	render_fractal(t_data *data);
int		close_window(t_data *data);
int		zoom_hook(int button, int x, int y, t_data *data);
int		get_color(int n, int color_mode);
void	*check_mlx_instance(void *ptr, const char *error_message);

#endif