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

// Function to convert degrees to radians
double	deg_to_rad(double degrees)
{
	return (degrees * M_PI / 180.0);
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 360);
	if (angle < 0)
		angle += 360;
	return (angle);
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
