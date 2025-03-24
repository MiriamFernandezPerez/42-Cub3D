/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:17:27 by mirifern          #+#    #+#             */
/*   Updated: 2025/02/18 22:17:29 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../inc/title_end.h"
#include "../../inc/audio.h"
#include "../../inc/error.h"
#include "../../inc/key.h"

void	draw_number(int pos[2], int sprite_size, int number, t_data *data)
{
	int	digit;
	int	i;

	i = 0;
	if (number == 0)
	{
		print_num_sprite(pos, sprite_size, 0, data);
		return ;
	}
	while (number > 0)
	{
		digit = number % 10;
		number /= 10;
		pos[X] += sprite_size;
		i++;
	}
}

int	load_end_screen(t_data *data)
{
	t_img	end_image;

	load_xpm_image(&end_image, END_PATH, data);
	scale_image(&end_image, HEIGHT, HEIGHT, data);
	mlx_put_image_to_window(data->mlx_data->mlx_ptr,
		data->mlx_data->win_ptr, end_image.ptr, WIDTH / 2 - HEIGHT / 2, 0);
	if (data->mlx_data->img_ptr)
		mlx_destroy_image(data->mlx_data->mlx_ptr, data->mlx_data->img_ptr);
	data->mlx_data->img_ptr = end_image.ptr;
	data->mlx_data->img_addr = end_image.addr;
	return (0);
}

void	end_screen(t_data *data)
{
	play_sound(END_AUDIO, true, true, data);
	mlx_loop_hook(data->mlx_data->mlx_ptr, load_end_screen, data);
}
