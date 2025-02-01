/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:54:14 by igarcia2          #+#    #+#             */
/*   Updated: 2025/01/20 17:13:06 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	only_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	validate_map_border(t_data *data, char **map)
{
	int	i;
	int	j;
	int	row_len;

	i = -1;
	while (map[++i])
	{
		j = 0;
		row_len = ft_strlen(map[i]);
		while (j < row_len)
		{
			if (map[i][j] == '0' || ft_strchr("NSWE", map[i][j]))
			{
				if (i == 0 || j == 0 || !map[i + 1]
					|| j >= (int)ft_strlen(map[i + 1])
					|| (i > 0 && j < (int)ft_strlen(map[i - 1])
						&& map[i - 1][j] == ' ')
					|| (map[i + 1] && j < (int)ft_strlen(map[i + 1])
					&& map[i + 1][j] == ' ') || (j > 0 && map[i][j - 1] == ' ')
					|| (j < row_len - 1 && map[i][j + 1] == ' '))
					ft_error_exit(ERR_BORDER, data);
			}
			j++;
		}
	}
}

int	calculate_angle(char **map, int x, int y)
{
	if (map[x][y] == 'N')
		return (90);
	else if (map[x][y] == 'S')
		return (270);
	else if (map[x][y] == 'E')
		return (0);
	else if (map[x][y] == 'W')
		return (180);
	return (-1);
}

int	check_player(t_data *data, int i, int j)
{
	if (ft_strchr("NSWE", data->map_data->map[i][j]))
	{
		data->player->pos[Y] = (i * TILE_SIZE) + TILE_SIZE / 2;
		data->player->pos[X] = (j * TILE_SIZE) + TILE_SIZE / 2;
		data->player->angle = calculate_angle(data->map_data->map, i, j);
		return (1);
	}
	return (0);
}

void	validate_map(t_data *data, char **map)
{
	int	i;
	int	j;
	int	player_qt;
	int	max_j;

	i = 0;
	player_qt = 0;
	max_j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (check_player(data, i, j) == 1)
				player_qt++;
			//Anadir X para la salida, D para las puertas y C para coleccionable si lo implementamos
			else if (!ft_strchr("01DX ", map[i][j]))
				ft_error_exit(ERR_INV_CHAR, data);
			j++;
			if (max_j < j)
				max_j = j;
		}
		i++;
	}
	if (player_qt != 1)
		ft_error_exit(ERR_PLAYER, data);
	validate_map_border(data, map);
	data->map_data->max_width = max_j;
	data->map_data->max_height = i;
}

void	parse_map(t_data *data, char **map_line)
{
	int		i;
	char	*line_trimmed;

	i = 0;
	while (map_line[i])
	{
		if (only_spaces(map_line[i]))
			ft_error_exit(ERR_MAP, data);
		line_trimmed = ft_strtrim(map_line[i], "\n");
		data->map_data->map = add_to_array(&data->map_data->map, line_trimmed);
		i++;
		free(line_trimmed);
	}
	if (!data->map_data->map)
		ft_error_exit(ERR_MAP, data);
	validate_map(data, data->map_data->map);
}

void	validate_conf_textures(t_data *data)
{
	if (!data->map_data->north_txt_path
		|| !data->map_data->south_txt_path
		|| !data->map_data->west_txt_path
		|| !data->map_data->east_txt_path
		|| !data->map_data->floor_txt_path || !data->map_data->ceiling_txt_path)
		ft_error_exit(ERR_CONF, data);
	printf("1 - '%s'\n2 - '%s'\n3 - '%s'\n4 - '%s'\n5 - '%s'\n6 - '%s'\n 7 - '%s'\n 8 - '%s'\n 9 - '%s'\n", data->map_data->north_txt_path, data->map_data->south_txt_path, data->map_data->west_txt_path, data->map_data->east_txt_path, data->map_data->floor_txt_path, data->map_data->ceiling_txt_path, data->map_data->door_txt_path, data->map_data->next_map, data->map_data->exit_sprite_path);
	if (data->map_data->next_map)
		printf("7 - '%s'\n", data->map_data->next_map);
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
		if (id == 'F')
			data->map_data->floor_color = color;
		else if (id == 'C')
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

char	*parse_path(char *line, t_data *data, char id)
{
	char	*path;
	int		fd;

	path = ft_strtrim(line, " \t");
	if (!path || ft_strchr(path, ' '))
		ft_error_exit(ERR_TXT, data);
	if (id == 'N' || id == 'S' || id == 'W' || id == 'E' || id == 'X' || id == 'M')
	{
		fd = open(path, O_RDONLY);
		if (fd == -1)
		{
			printf("aqui %d\n", id);
			ft_error_exit(ERR_PATH, data);
		}
		close(fd);
	}
	else if (id == 'F' || id == 'C' || id == 'D')
		check_color_or_texture(data, path, id);
	if (id == 'X')
		check_exit_sprite(path, data, id);
	if (id == 'M')
	{
		if (ft_strncmp(path + ft_strlen(path) - 4, ".cub", 4))
			ft_error_exit(ERR_NEXT, data);
	}
	return (path);
}

int	parse_line(t_data *data, char *line)
{
	char	*trim_line;

	trim_line = ft_strtrim(line, "\t\n ");
	if (ft_strncmp(trim_line, "NO ", 3) == 0)
		data->map_data->north_txt_path = parse_path(trim_line + 3, data, 'N');
	else if (ft_strncmp(trim_line, "SO ", 3) == 0)
		data->map_data->south_txt_path = parse_path(trim_line + 3, data, 'S');
	else if (ft_strncmp(trim_line, "WE ", 3) == 0)
		data->map_data->west_txt_path = parse_path(trim_line + 3, data, 'W');
	else if (ft_strncmp(trim_line, "EA ", 3) == 0)
		data->map_data->east_txt_path = parse_path(trim_line + 3, data, 'E');
	else if (ft_strncmp(trim_line, "F ", 2) == 0)
		data->map_data->floor_txt_path = parse_path(trim_line + 2, data, 'F');
	else if (ft_strncmp(trim_line, "C ", 2) == 0)
		data->map_data->ceiling_txt_path = parse_path(trim_line + 2, data, 'C');
	else if (ft_strncmp(trim_line, "D ", 2) == 0)
		data->map_data->door_txt_path = parse_path(trim_line + 2, data, 'D');
	else if (ft_strncmp(trim_line, "MAP ", 4) == 0)
		data->map_data->next_map = parse_path(trim_line + 4, data, 'M');
	else if (ft_strncmp(trim_line, "EXIT ", 5) == 0)
		data->map_data->exit_sprite_path = parse_path(trim_line + 5, data, 'X');
	else
		return (free(trim_line), 1);
	return (free(trim_line), 0);
}

void	parse_cub_file(t_data *data, char **cub_file)
{
	int	i;

	i = 0;
	while (cub_file[i])
	{
		if (ft_strlen(cub_file[i]) == 0 || only_spaces(cub_file[i]))
			i++;
		else
		{
			if (parse_line(data, cub_file[i++]) == 1)
			{
				i--;
				break ;
			}
		}
	}
	validate_conf_textures(data);
	parse_map(data, cub_file + i);
	//print_str_array(data->map_data->map);
}

int	read_file(int fd, t_data *data)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		data->cub_file = add_to_array(&data->cub_file, line);
		malloc_protection(data->cub_file, data);
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	close(fd);
	if (!data->cub_file)
		return (ft_error(ERR_EMPTY), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	open_file(char *path, t_data *data)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_perror(path), EXIT_FAILURE);
	if (read_file(fd, data) == EXIT_FAILURE)
	{
		close(fd);
		return (ft_perror(path), EXIT_FAILURE);
	}
	parse_cub_file(data, data->cub_file);
	return (EXIT_SUCCESS);
}
