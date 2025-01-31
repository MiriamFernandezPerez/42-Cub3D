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

char	**ft_array_cpy(char **array, t_data *data)
{
	int		i;
	int		length;
	char	**duplicate;

	i = 0;
	length = 0;
	while (array[length])
		length++;
	duplicate = malloc(sizeof(char *) * (length + 1));
	malloc_protection(duplicate, data);
	while (i < length)
	{
		duplicate[i] = ft_strdup(array[i]);
		if (!duplicate[i])
		{
			while (i > 0)
				free(duplicate[--i]);
			free(duplicate);
			ft_error_exit("ERR_CPY", data);
		}
		i++;
	}
	duplicate[i] = NULL;
	return (duplicate);
}

void	validate_map_border(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || ft_strchr("NSWE", map[i][j]))
			{
				if (i == 0 || j == 0 || !map[i + 1] || !map[i][j + 1])
					ft_error_exit(ERR_BORDER, data);
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' ||
					map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
					ft_error_exit(ERR_BORDER, data);
			}
			j++;
		}
		i++;
	}
}

int	calulate_angle(char **map, int x, int y)
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
		data->player->pos[0] = (i * TILE_SIZE) + TILE_SIZE/2;
		data->player->pos[1] = (j * TILE_SIZE) + TILE_SIZE/2;
		data->player->angle = calulate_angle(data->map_data->map, i, j);
		return (1);
	}
	return (0);
}

void	validate_map(t_data *data, char **map)
{
	int	i;
	int	j;
	int	player_qt;
	int max_j;

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
			else if (!ft_strchr("01 ", map[i][j]))
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
	data->map_data->max_width = i;
	data->map_data->max_height = max_j;
}

void	parse_map(t_data *data, char **map_line)
{
	int		i;
	char	*map_line_trimmed;

	i = 0;
	while(map_line[i])
	{
		map_line_trimmed = ft_strtrim(map_line[i], "\n");
		data->map_data->map = add_to_array(&data->map_data->map, map_line_trimmed);
		i++;
		free(map_line_trimmed);
	}
	/*printf("map data array:\n");
	for (int i = 0; data->map_data->map[i] != NULL; i++)
		printf("%s\n", data->map_data->map[i]);*/
	validate_map(data, data->map_data->map);
}

void	validate_conf_textures(t_data *data)
{
	if (!data->map_data->north_texture_path
		|| !data->map_data->south_texture_path
		|| !data->map_data->west_texture_path
		|| !data->map_data->east_texture_path
		|| !data->map_data->floor || !data->map_data->ceiling)
		ft_error_exit(ERR_CONF, data);
	printf("1 - '%s'\n2 - '%s'\n3 - '%s'\n4 - '%s'\n5 - '%s'\n6 - '%s'\n", data->map_data->north_texture_path, data->map_data->south_texture_path, data->map_data->west_texture_path, data->map_data->east_texture_path, data->map_data->floor, data->map_data->ceiling);
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
		(*i)++;
	}
	if (num < 0 || num > 255)
		return (-1);
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

char	*parse_path(char *line, t_data *data, char id)
{
	char	*path;
	int		fd;

	path = ft_strtrim(line, " \t");
	if (!path || ft_strchr(path, ' '))
		ft_error_exit(ERR_TXT, data);
	if (id == 'N' || id == 'S' || id == 'W' || id == 'E')
	{
		fd = open(path, O_RDONLY);
		if (fd == -1)
			ft_error_exit(ERR_PATH, data);
		close(fd);
	}
	else if (id == 'F' || id == 'C')
		check_color_or_texture(data, path, id);
	if (id == 'X')
	{
		if (ft_strncmp(path + ft_strlen(path) - 4, ".cub", 4))
			ft_error_exit(ERR_NEXT, data);
		fd = open(path, O_RDONLY);
		if (fd == -1)
			ft_error_exit(ERR_OPEN_NEXT, data);
		close(fd);
	}
	return (path);
}

int	parse_line(t_data *data, char *line)
{
	char	*trim_line;

	trim_line = ft_strtrim(line, "\t\n ");
	if (ft_strncmp(trim_line, "NO ", 3) == 0)
		data->map_data->north_texture_path = parse_path(trim_line + 3, data, 'N');
	else if (ft_strncmp(trim_line, "SO ", 3) == 0)
		data->map_data->south_texture_path = parse_path(trim_line + 3, data, 'S');
	else if (ft_strncmp(trim_line, "WE ", 3) == 0)
		data->map_data->west_texture_path = parse_path(trim_line + 3, data, 'W');
	else if (ft_strncmp(trim_line, "EA ", 3) == 0)
		data->map_data->east_texture_path = parse_path(trim_line + 3, data, 'E');
	else if (ft_strncmp(trim_line, "F ", 2) == 0)
		data->map_data->floor = parse_path(trim_line + 2, data, 'F');
	else if (ft_strncmp(trim_line, "C ", 2) == 0)
		data->map_data->ceiling = parse_path(trim_line + 2, data, 'C');
	else if (ft_strncmp(trim_line, "X ", 2) == 0)
		data->map_data->next_map = parse_path(trim_line + 2, data, 'X');
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
		ft_error_exit(ERR_EMPTY, data);
	return (EXIT_SUCCESS);
}

int	open_file(char *path, t_data *data)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_perror(path), EXIT_FAILURE);
	if (read_file(fd, data) == EXIT_FAILURE)
		return (ft_perror(path), EXIT_FAILURE);
	parse_cub_file(data, data->cub_file);
	return (EXIT_SUCCESS);
}
