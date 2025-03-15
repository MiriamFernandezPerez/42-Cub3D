/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:27:13 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/02 21:14:20 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	door_type(char **map, int y, int x)
{
	if (map[y][x] == TILE_DOOR)
		return (0);
	else if (map[y][x] == TILE_LOCKED_DOOR)
		return (1);
	return (-1);
}

int	is_crossable(char tile)
{
	return (ft_strchr(CROSSABLE_TILES, tile) != NULL);
}

void	malloc_protection(void *ptr, t_data *data)
{
	if (ptr == NULL)
	{
		ft_error(ERR_MALLOC);
		if (data)
			free_data(data);
		exit(EXIT_FAILURE);
	}
}

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

//Get current time in milliseconds
long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
