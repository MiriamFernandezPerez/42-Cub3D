/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:24:31 by mirifern          #+#    #+#             */
/*   Updated: 2024/01/24 23:52:57 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				len;
	unsigned char	ch;

	len = ft_strlen(s);
	ch = (unsigned char) c;
	while (len >= 0)
	{
		if (s[len] == ch)
			return ((char *)s + len);
		len--;
	}
	return (NULL);
}
