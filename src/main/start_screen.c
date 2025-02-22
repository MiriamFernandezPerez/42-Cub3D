/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:17:27 by mirifern          #+#    #+#             */
/*   Updated: 2025/02/18 22:17:29 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	key_menu(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
		data->start->selected = 7;
	if (keycode == KEY_RIGHT)
		data->start->selected = 6;
	if (keycode == KEY_SPACE && data->start->selected == 6)
	{
		mlx_loop_hook(data->mlx_data->mlx_ptr, game_loop, data);
		mlx_hook(data->mlx_data->win_ptr, 2, 1L << 0, key_press, data);
	}
	else if ((keycode == KEY_SPACE && data->start->selected == 7)
		|| keycode == KEY_ESC)
	{
		free_data(data);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	start_loop(t_data *data)
{
	int		index;
	t_mlx	*info;

	info = data->mlx_data;
	if (data->start->blink)
		index = data->start->selected;
	else
		index = 5;
	if (index < 5 || index >= 9 || !data->start->img[index])
	{
		ft_error(ERR_START);
		return (0);
	}
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr,
		data->start->img[index], 0, 0);
	usleep(160000);
	data->start->blink = !data->start->blink;
	return (0);
}

void	start_screen(t_data *data)
{
	int			i;
	void		*image[8];
	t_img_size	size;

	i = -1;
	data->start->src_x = 0;
	data->start->src_y = 0;
	size.dst_width = WIDTH;
	size.dst_height = HEIGHT;
	while (++i < 8)
	{
		image[i] = load_xpm_image(data, i);
	}
	image[i] = NULL;
	resize_images(data, image, size);
	data->start->blink = 0;
	data->start->selected = 6;
	render_fade_in(data);
	mlx_loop_hook(data->mlx_data->mlx_ptr, start_loop, data);
	mlx_hook(data->mlx_data->win_ptr, 2, 1L << 0, key_menu, data);
}
