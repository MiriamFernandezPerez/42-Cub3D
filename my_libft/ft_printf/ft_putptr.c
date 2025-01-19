/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:21:06 by mirifern          #+#    #+#             */
/*   Updated: 2024/06/05 21:56:21 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	ft_putptrhex(unsigned long nb, char *base, int *len)
{
	char	n;

	if (nb >= 16)
	{
		if (ft_putptrhex(nb / 16, base, len) == -1)
			return (-1);
		if (ft_putptrhex(nb % 16, base, len) == -1)
			return (-1);
	}
	else
	{
		if (nb <= 9)
			n = nb + 48;
		else
			n = base[nb];
		if (ft_putchar(n, 1, len) == -1)
			return (-1);
	}
	return (0);
}

int	ft_putptr(unsigned long nb, char *base, int *len)
{
	if (ft_putstr("0x", 1, len) == -1)
		return (-1);
	ft_putptrhex(nb, base, len);
	return (0);
}
