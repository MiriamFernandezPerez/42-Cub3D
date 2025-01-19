/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:19:53 by mirifern          #+#    #+#             */
/*   Updated: 2024/01/22 23:14:13 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	*str;

	i = 0;
	if (dst == (void *)0 && src == (void *)0)
		return (dst);
	ptr = (unsigned char *) dst;
	str = (unsigned char *) src;
	while (i < n)
	{
		ptr[i] = str[i];
		i++;
	}
	return (dst);
}
