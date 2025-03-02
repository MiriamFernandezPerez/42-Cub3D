/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 02:27:49 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/18 22:44:15 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_textures(t_texture *txt_list, t_mlx *mlx_data, t_data *data)
{
	t_texture	*current;

	current = txt_list;
	while (current)
	{
		if (current->path)
		{
			current->img = mlx_xpm_file_to_image(mlx_data->mlx_ptr,
					current->path, &current->width, &current->height);
			if (current->img == NULL)
				ft_error_exit(ERR_LOAD_TXT, data);
			current->addr = mlx_get_data_addr(current->img, &current->bpp,
					&current->line_len, &current->endian);
			if (current->addr == NULL)
				ft_error_exit("Error\nmlx_get_data_addr failed\n", data);
		}
		current = current->next;
	}
}

void	init_mlx(t_data *data)
{
	data->mlx_data = malloc(sizeof(t_mlx));
	malloc_protection(data->mlx_data, data);
	data->mlx_data->mlx_ptr = mlx_init();
	if (!data->mlx_data->mlx_ptr)
		ft_error_exit(ERR_MLX_INIT, data);
	data->mlx_data->win_ptr
		= mlx_new_window(data->mlx_data->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	if (!data->mlx_data->win_ptr)
		ft_error_exit(ERR_MLX_WIN, data);
	mlx_mouse_move(data->mlx_data->mlx_ptr, data->mlx_data->win_ptr,
		WIDTH, HEIGHT);
	mlx_mouse_hide(data->mlx_data->mlx_ptr, data->mlx_data->win_ptr);
	data->mlx_data->img_ptr = NULL;
	data->mlx_data->img_addr = NULL;
	data->mlx_data->new_img_addr = NULL;
	data->mlx_data->img_ptr = NULL;
	data->mlx_data->img_addr = NULL;
	data->mlx_data->redraw = 1;
	data->mlx_data->mouse_pos = 0;
	//mlx_hook(data->mlx_data->win_ptr, 2, 1L << 0, key_press, data);
	//mlx_loop_hook(data->mlx_data->mlx_ptr, game_loop, data);
	mlx_hook(data->mlx_data->win_ptr, 17, 0, close_window, data);
	mlx_hook(data->mlx_data->win_ptr, 6, 1L << 6, mouse_handler, data);
}

void	init_map(t_map *map_data)
{
	map_data->map = NULL;
	map_data->max_height = 0;
	map_data->max_width = 0;
	map_data->ceiling_color = 0;
	map_data->floor_color = 0;
	map_data->next_map = NULL;
	map_data->floor_tiles_qt = 0;
	map_data->floor_tiles_found = 0;
	map_data->exit_qt = 0;
	map_data->key_qt = 0;
	map_data->txt_list = NULL;
	map_data->door_list = NULL;
	map_data->sprite_list = NULL;
}

void	init_minimap_data(t_minimap *minimap_data)
{
	minimap_data->size[X] = WIDTH * 0.2;
	minimap_data->size[Y] = HEIGHT * 0.2;
	minimap_data->margin[X] = WIDTH * MINIMAP_MARGIN;
	minimap_data->margin[Y] = HEIGHT * MINIMAP_MARGIN;
	minimap_data->tile_size = minimap_data->size[Y] / TILES_VERTICAL;
	minimap_data->size[Y] = (minimap_data->tile_size * TILES_VERTICAL) + 2;
	minimap_data->size[X] = (minimap_data->size[X] / minimap_data->tile_size)
		* minimap_data->tile_size + 2;
	minimap_data->tiles_horz = minimap_data->size[X] / minimap_data->tile_size;
	if (minimap_data->tiles_horz % 2 == 0)
	{
		minimap_data->tiles_horz++;
		minimap_data->size[X] += minimap_data->tile_size;
	}
	minimap_data->start[X]
		= WIDTH - minimap_data->size[X] - minimap_data->margin[X];
	minimap_data->start[Y] = minimap_data->margin[Y];
	minimap_data->angle_step = FOV / (double)minimap_data->size[X];
	minimap_data->scale = TILE_SIZE / (double)minimap_data->tile_size;
}

// Initializes data struct
void	init_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	malloc_protection(*data, NULL);
	(*data)->map_data = NULL;
	(*data)->ray_data = NULL;
	(*data)->mlx_data = NULL;
	(*data)->cub_file = NULL;
	(*data)->minimap_data = NULL;
	(*data)->title_data = NULL;
	(*data)->player = malloc(sizeof(t_player));
	malloc_protection((*data)->player, *data);
	(*data)->title_data = malloc(sizeof(t_title));
	malloc_protection((*data)->title_data, *data);
	(*data)->audio = malloc(sizeof(t_audio));
	malloc_protection((*data)->audio, *data);
	init_title((*data)->title_data);
	(*data)->ray_data = malloc(sizeof(t_raycast));
	malloc_protection((*data)->ray_data, *data);
	(*data)->map_data = malloc(sizeof(t_map));
	malloc_protection((*data)->map_data, *data);
	init_map((*data)->map_data);
	(*data)->minimap_data = malloc(sizeof(t_minimap));
	malloc_protection((*data)->minimap_data, (*data));
	init_minimap_data((*data)->minimap_data);
	(*data)->ray_data->angle_increment = (double)FOV / (double)WIDTH;
	(*data)->ray_data->distance_pp = (WIDTH / 2) / (tan(deg_to_rad(FOV / 2)));
}