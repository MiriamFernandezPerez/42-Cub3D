/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:27:13 by igarcia2          #+#    #+#             */
/*   Updated: 2025/01/26 21:37:12 by igarcia2         ###   ########.fr       */
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
	if (angle < 0)
		angle = 360 + angle;
	if (angle > 359)
		angle = angle - 360;
	return (angle);
}
