/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 23:35:58 by mirifern          #+#    #+#             */
/*   Updated: 2024/06/05 22:41:11 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*ptr;
	size_t	len_d;

	i = 0;
	if (s1 == (void *)0 && s2 == (void *)0)
		return (NULL);
	len_d = ft_strlen(s1);
	ptr = (char *)malloc((len_d + ft_strlen(s2) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		ptr[len_d + i] = s2[i];
		i++;
	}
	ptr[len_d + i] = '\0';
	return (ptr);
}
