/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:19:40 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/18 22:54:48 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	update_sprites(t_data *data)
{
	t_sprite	*sprite;

	sprite = data->map_data->sprite_list;
	while (sprite)
	{
		if (sprite->txt_num > 1)
		{
			if (get_time() - sprite->last_frame_time >= FRAME_DURATION)
			{
				sprite->frame = (sprite->frame + 1) % sprite->txt_num;
				sprite->last_frame_time = get_time();
				data->mlx_data->redraw = 1;
			}
		}
		sprite = sprite->next;
	}
}

//Redraws the scene
void	redraw_scene(t_data *data)
{
	void	*new_img_ptr;

	new_img_ptr = mlx_new_image(data->mlx_data->mlx_ptr, WIDTH, HEIGHT);
	data->mlx_data->new_img_addr
		= mlx_get_data_addr(new_img_ptr, &(data->mlx_data->bpp),
			&(data->mlx_data->line_len), &(data->mlx_data->endian));
	raycast_manager(data->ray_data, data);
	create_minimap(data->minimap_data, data->mlx_data, data);
	render_ui(data);
	render_player(data);
	data->mlx_data->redraw = 0;
	mlx_put_image_to_window(data->mlx_data->mlx_ptr,
		data->mlx_data->win_ptr, new_img_ptr, 0, 0);
	if (data->mlx_data->img_ptr)
		mlx_destroy_image(data->mlx_data->mlx_ptr, data->mlx_data->img_ptr);
	data->mlx_data->img_ptr = new_img_ptr;
	data->mlx_data->img_addr = data->mlx_data->new_img_addr;
	data->mlx_data->new_img_addr = NULL;
}

//Manages the game main loop
int	game_loop(t_data *data)
{
	if (data->player->exit_reached)
	{
		if (load_next_map(data) == EXIT_FAILURE)
			return (free_data(data), EXIT_FAILURE);
	}
	/*KeyRelease
	update_movement(data);*/
	check_doors(data);
	update_doors(data);
	update_sprites(data);
	redraw_scene(data);
	return (0);
}
