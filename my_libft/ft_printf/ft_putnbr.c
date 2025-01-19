/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:24:11 by mirifern          #+#    #+#             */
/*   Updated: 2024/02/11 23:46:45 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	ft_print_nbr(int nb, int *len)
{
	if (nb > 9)
	{
		if (ft_putnbr(nb / 10, len) == -1)
			return (-1);
		if (ft_putnbr(nb % 10, len) == -1)
			return (-1);
	}
	else
	{
		if (ft_putchar(nb + 48, 1, len) == -1)
			return (-1);
	}
	return (0);
}

int	ft_putnbr(int nb, int *len)
{
	if (nb == -2147483648)
	{
		if (ft_putstr("-2147483648", 1, len) == -1)
			return (-1);
	}
	else if (nb < 0)
	{
		if (ft_putchar('-', 1, len) == -1)
			return (-1);
		nb = -nb;
		if (ft_putnbr(nb, len) == -1)
			return (-1);
	}
	else
	{
		if (ft_print_nbr(nb, len) == -1)
			return (-1);
	}
	return (0);
}
