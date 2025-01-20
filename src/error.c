/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:02:05 by igarcia2          #+#    #+#             */
/*   Updated: 2025/01/20 15:14:21 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_error(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
}

void	ft_perror(char *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	perror(msg);
}
