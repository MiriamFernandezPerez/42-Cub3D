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
		if (sprite->txt_num > 1) //TODO añadir solo si sprite visible?
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

//Manages the doors opening/closing status
void	update_doors(t_data *data)
{
	t_door	*curr_door;
	double	elapsed;

	curr_door = data->map_data->door_list;
	while (curr_door)
	{
		elapsed = (get_time() - curr_door->timer) / 1000.0;
		if (curr_door->state == OPENING || curr_door->state == CLOSING)
			data->mlx_data->redraw = 1;
		if (curr_door->state == OPENING && elapsed / DOOR_OPEN_TIME >= 1.0)
		{
			curr_door->offset = TILE_SIZE;
			curr_door->state = OPENED;
		}
		else if (curr_door->state == OPENING)
			curr_door->offset = TILE_SIZE * (elapsed / DOOR_OPEN_TIME);
		else if (curr_door->state == CLOSING && elapsed / DOOR_OPEN_TIME >= 1.0)
		{
			curr_door->offset = 0;
			curr_door->state = CLOSED;
		}
		else if (curr_door->state == CLOSING)
			curr_door->offset = TILE_SIZE * (1.0 - (elapsed / DOOR_OPEN_TIME));
		curr_door = curr_door->next;
	}
}

//Checks for nearby doors
void	check_doors(t_data *data)
{
	t_door	*curr_door;
	double	distance;

	curr_door = data->map_data->door_list;
	while (curr_door)
	{
		distance = calculate_distance(data->player->pos[X],
				data->player->pos[Y], curr_door->grid[X] * TILE_SIZE
				+ (TILE_SIZE / 2), curr_door->grid[Y] * TILE_SIZE
				+ (TILE_SIZE / 2));
		if ((curr_door->state == CLOSED && distance <= DOOR_OPEN_DISTANCE)
			|| (curr_door->state == OPENED && distance > DOOR_CLOSE_DISTANCE))
		{
			//play_sound(DOOR_AUDIO, true, false, data);
			curr_door->timer = get_time();
			data->mlx_data->redraw = 1;
			if (curr_door->state == CLOSED)
				curr_door->state = OPENING;
			else
				curr_door->state = CLOSING;
		}
		curr_door = curr_door->next;
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
	print_ui(data);
	data->mlx_data->redraw = 0;
	mlx_put_image_to_window(data->mlx_data->mlx_ptr,
		data->mlx_data->win_ptr, new_img_ptr, 0, 0);
	if (data->mlx_data->img_ptr)
		mlx_destroy_image(data->mlx_data->mlx_ptr, data->mlx_data->img_ptr);
	data->mlx_data->img_ptr = new_img_ptr;
	data->mlx_data->img_addr = data->mlx_data->new_img_addr;
	data->mlx_data->new_img_addr = NULL;
	//print_player_info(data); //TEST
}

//Manages the game main loop
int	game_loop(t_data *data)
{
	if (data->player->exit_reached)
	{
		if (load_next_map(data) == EXIT_FAILURE)
			return (free_data(data), EXIT_FAILURE);
	}
	check_doors(data);
	update_doors(data);
	update_sprites(data);
	if (data->mlx_data->redraw)
		redraw_scene(data);
	return (0);
}
