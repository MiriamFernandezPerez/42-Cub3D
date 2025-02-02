/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:25:31 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/01 21:30:07 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//Function that prints number in the rendering window
void	print_nbr(t_mlx *mlx_data, int x, int y, int nbr)
{
	char	*str;

	str = ft_itoa(nbr);
	mlx_string_put(mlx_data->mlx_ptr, mlx_data->win_ptr, x, y, 0xFFFFFF, str);
	free(str);
}

//Function that prints text in the rendering window
void	print_str(t_mlx *mlx_data, int x, int y, char *str)
{
	mlx_string_put(mlx_data->mlx_ptr, mlx_data->win_ptr, x, y, 0xFFFFFF, str);
}

void	print_pixel_render(int x, int y, int color, t_mlx *mlx_data)
{
	int	pixel;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	pixel = (y * mlx_data->line_len) + (x * (mlx_data->bpp / 8));
	mlx_data->new_img_addr[pixel] = color & 0xFF;
	mlx_data->new_img_addr[pixel + 1] = (color >> 8) & 0xFF;
	mlx_data->new_img_addr[pixel + 2] = (color >> 16) & 0xFF;
	if (mlx_data->bpp == 32)
		mlx_data->new_img_addr[pixel + 3] = (color >> 24);
}

void	print_tile_pixel(int x, int y, int tile_type, t_mlx *mlx_data)
{
	int	color;

	if (tile_type == TILE_WALL)
		color = MINIMAP_WALL_COLOR;
	else if (tile_type == TILE_FLOOR)
		color = MINIMAP_FLOOR_COLOR;
	else if (tile_type == TILE_SPACE)
		color = MINIMAP_BACK_COLOR;
	else if (tile_type == TILE_W || tile_type == TILE_N
		|| tile_type == TILE_S || tile_type == TILE_E)
		color = MINIMAP_FLOOR_COLOR;
	else if (tile_type == TILE_DOOR)
		color = MINIMAP_DOOR_COLOR;
	print_pixel_render(x, y, color, mlx_data);
}
