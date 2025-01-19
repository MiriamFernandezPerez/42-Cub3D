/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:50:48 by mirifern          #+#    #+#             */
/*   Updated: 2024/01/20 20:52:19 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*ptr_d;
	char	*ptr_s;

	if (!dst && !src)
		return (NULL);
	ptr_d = (char *)dst;
	ptr_s = (char *)src;
	if (ptr_d > ptr_s)
	{
		while (len > 0)
		{
			ptr_d[len - 1] = ptr_s[len - 1];
			len--;
		}
	}
	else
	{
		while (len-- > 0)
			*(ptr_d)++ = *(ptr_s)++;
	}
	return (dst);
}
