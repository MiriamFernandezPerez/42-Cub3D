/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_txt_and_colors.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 01:38:56 by mirifern          #+#    #+#             */
/*   Updated: 2025/02/02 02:26:00 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	validate_conf_textures(t_data *data)
{
	if (!data->map_data->north_txt_path
		|| !data->map_data->south_txt_path
		|| !data->map_data->west_txt_path
		|| !data->map_data->east_txt_path
		|| !data->map_data->floor_txt_path || !data->map_data->ceiling_txt_path)
		ft_error_exit(ERR_CONF, data);
	printf("1 - '%s'\n2 - '%s'\n3 - '%s'\n4 - '%s'\n5 - '%s'\n6 - '%s'\n 7 - '%s'\n 8 - '%s'\n 9 - '%s'\n", data->map_data->north_txt_path, data->map_data->south_txt_path, data->map_data->west_txt_path, data->map_data->east_txt_path, data->map_data->floor_txt_path, data->map_data->ceiling_txt_path, data->map_data->door_txt_path, data->map_data->next_map, data->map_data->exit_sprite_path);
}

int	check_rgb(char *path, int *i)
{
	int	num;

	num = 0;
	while (path[*i] != '\0' && path[*i] != ',')
	{
		if (!ft_isdigit(path[*i]))
			return (-1);
		num = num * 10 + (path[*i] - '0');
		if (num < 0 || num > 255)
			return (-1);
		(*i)++;
	}
	return (num);
}

int	rgb_to_hex(char *path)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 0;
	r = check_rgb(path, &i);
	if (r == -1 || path[i] != ',')
		return (-1);
	i++;
	g = check_rgb(path, &i);
	if (g == -1 || path[i] != ',')
		return (-1);
	i++;
	b = check_rgb(path, &i);
	if (b == -1 || path[i] != '\0')
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

void	check_color_or_texture(t_data *data, char *path, char id)
{
	int	fd;
	int	color;

	color = -1;
	if (ft_strchr(path, ','))
	{
		color = rgb_to_hex(path);
		if (color == -1)
			ft_error_exit(ERR_COLOR, data);
		if (id == ID_FLOOR)
			data->map_data->floor_color = color;
		else if (id == ID_CEIL)
			data->map_data->ceiling_color = color;
	}
	else
	{
		fd = open(path, O_RDONLY);
		if (fd == -1)
			ft_error_exit(ERR_PATH, data);
	}
}

void	check_exit_sprite(char *path, t_data *data, int id)
{
	(void)path;
	(void)data;
	(void)id;
	printf("checkeo el sprite\n");
}
