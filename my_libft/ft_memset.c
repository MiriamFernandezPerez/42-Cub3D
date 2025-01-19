/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 21:35:48 by mirifern          #+#    #+#             */
/*   Updated: 2024/01/20 20:48:36 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char			*ptr;
	size_t			i;
	unsigned char	a;

	ptr = (char *)b;
	i = 0;
	a = c;
	while (i < len)
	{
		ptr[i] = a;
		i++;
	}
	return (ptr);
}
