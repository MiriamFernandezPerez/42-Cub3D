/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 22:58:20 by mirifern          #+#    #+#             */
/*   Updated: 2025/02/22 07:08:20 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	*load_xpm_image(t_data *data, int i)
{
	void	*img;
	t_mlx	*info;
	int		width;
	int		height;
	char	*path;

	info = data->mlx_data;
	width = data->start->width;
	height = data->start->height;
	path = (load_path(i));
	img = mlx_xpm_file_to_image(info->mlx_ptr, path, &width, &height);
	if (!img)
	{
		destroy_arr_img(data, (void **)img);
	}
	return (img);
}

void	render_fade_in(t_data *data)
{
	int		i;
	t_mlx	*info;

	i = 0;
	info = data->mlx_data;
	while (i < 6)
	{
		mlx_put_image_to_window(info->mlx_ptr, info->win_ptr,
			data->start->img[i], 0, 0);
		usleep(500000);
		i++;
	}
}

int	calculate_pos(t_data *data, char *src_data, char *new_data, t_img_size size)
{
	int	x;
	int	y;

	y = 0;
	while (y < size.dst_height)
	{
		x = 0;
		while (x < size.dst_width)
		{
			data->start->src_x = (x * size.src_width) / size.dst_width;
			data->start->src_y = (y * size.src_height) / size.dst_height;
			if (data->start->src_x < 0 || data->start->src_x >= size.src_width
				|| data->start->src_y < 0
				|| data->start->src_y >= size.src_height)
				return (1);
			data->start->color = *(int *)(src_data + (data->start->src_y
						* size.src_width * 4 + data->start->src_x * 4));
			*(int *)(new_data + (y * size.dst_width * 4 + x
						* 4)) = data->start->color;
			x++;
		}
		y++;
	}
	return (0);
}

void	*resize_image(t_data *data, t_mlx *mlx, void *src_img, t_img_size size)
{
	void	*new;
	char	*src_data;
	char	*new_data;

	if (size.dst_width == 0 || size.dst_height == 0 || size.src_width == 0
		|| size.src_height == 0)
		return (NULL);
	new = mlx_new_image(mlx->mlx_ptr, size.dst_width, size.dst_height);
	if (!new)
		return (NULL);
	src_data = mlx_get_data_addr(src_img, &(int){0}, &(int){0}, &(int){0});
	new_data = mlx_get_data_addr(new, &(int){0}, &(int){0}, &(int){0});
	if (!src_data || !new_data)
		return (NULL);
	if (calculate_pos(data, src_data, new_data, size))
		return (NULL);
	if (src_img)
		mlx_destroy_image(data->mlx_data->mlx_ptr, src_img);
	return (new);
}

void	resize_images(t_data *data, void **image, t_img_size size)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (image[i])
		{
			mlx_get_data_addr(image[i], &data->start->bpp,
				&data->start->size_line, &data->start->endian);
			size.src_width = data->start->size_line / (data->start->bpp / 8);
			size.src_height = HEIGHT;
			data->start->img[i] = resize_image(data, data->mlx_data,
					image[i], size);
		}
		i++;
	}
}
