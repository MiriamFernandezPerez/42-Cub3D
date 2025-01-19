/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsig.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:23:04 by mirifern          #+#    #+#             */
/*   Updated: 2024/02/11 23:23:20 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsig(unsigned int nb, int *len)
{
	if (nb > 9)
	{
		if (ft_putunsig(nb / 10, len) == -1)
			return (-1);
		if (ft_putunsig(nb % 10, len) == -1)
			return (-1);
	}
	else
	{
		if (ft_putchar(nb + 48, 1, len) == -1)
			return (-1);
	}
	return (0);
}
