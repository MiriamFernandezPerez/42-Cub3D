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

void	print_score(t_data *data)
{
	int	pos[2];

	pos[X] = WIDTH / 2;
	pos[Y] = HEIGHT / 2;
	print_num_sprite(pos, 32, 23, data);
}

void	clear_screen(t_data *data)
{
	void	*new_img_ptr;

	new_img_ptr = mlx_new_image(data->mlx_data->mlx_ptr, WIDTH, HEIGHT);
	data->mlx_data->new_img_addr
		= mlx_get_data_addr(new_img_ptr, &(data->mlx_data->bpp),
			&(data->mlx_data->line_len), &(data->mlx_data->endian));
	mlx_put_image_to_window(data->mlx_data->mlx_ptr,
		data->mlx_data->win_ptr, new_img_ptr, 0, 0);
	if (data->mlx_data->img_ptr)
		mlx_destroy_image(data->mlx_data->mlx_ptr, data->mlx_data->img_ptr);
	data->mlx_data->img_ptr = new_img_ptr;
	data->mlx_data->img_addr = data->mlx_data->new_img_addr;
	data->mlx_data->new_img_addr = NULL;

}

void	print_end_screen(t_data *data)
{
	t_img	end_image;
	void	*new_img_ptr;

	load_xpm_image(&end_image, END_PATH, data);
	scale_image(&end_image, HEIGHT, HEIGHT, data);
	new_img_ptr = end_image.ptr;
	data->mlx_data->new_img_addr
		= mlx_get_data_addr(new_img_ptr, &(data->mlx_data->bpp),
			&(data->mlx_data->line_len), &(data->mlx_data->endian));
	mlx_put_image_to_window(data->mlx_data->mlx_ptr,
		data->mlx_data->win_ptr, new_img_ptr, WIDTH / 2 - HEIGHT / 2, 0);
	if (data->mlx_data->img_ptr)
		mlx_destroy_image(data->mlx_data->mlx_ptr, data->mlx_data->img_ptr);
	data->mlx_data->img_ptr = new_img_ptr;
	data->mlx_data->img_addr = data->mlx_data->new_img_addr;
	data->mlx_data->new_img_addr = NULL;
}

void	end_screen(t_data *data)
{
	clear_screen(data);
	print_end_screen(data);
	//print_score(data);
}
