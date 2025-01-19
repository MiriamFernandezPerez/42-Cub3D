/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:25:30 by mirifern          #+#    #+#             */
/*   Updated: 2024/06/05 21:55:31 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex(unsigned int nb, char *base, int *len)
{
	char	n;

	if (nb >= 16)
	{
		if (ft_puthex(nb / 16, base, len) == -1)
			return (-1);
		if (ft_puthex(nb % 16, base, len) == -1)
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
