/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:27:22 by mirifern          #+#    #+#             */
/*   Updated: 2024/02/11 23:27:35 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s, int fd, int *len)
{
	int	i;

	i = 0;
	if (!s)
	{
		s = "(null)";
		if (ft_putstr(s, 1, len) == -1)
			return (-1);
	}
	else
	{
		while (s[i] != '\0')
		{
			if (ft_putchar(s[i], fd, len) == -1)
				return (-1);
			i++;
		}
	}
	return (0);
}
