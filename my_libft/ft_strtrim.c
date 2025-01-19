/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 22:13:16 by mirifern          #+#    #+#             */
/*   Updated: 2024/01/25 00:04:33 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*ptr;

	i = 0;
	j = ft_strlen(s1);
	k = 0;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	while (j > i && ft_strchr(set, s1[j - 1]))
		j--;
	ptr = malloc(sizeof(char) * (j - i + 1));
	if (!ptr)
		return (NULL);
	while (i < j)
	{
		ptr[k] = s1[i];
		i++;
		k++;
	}
	ptr[k] = '\0';
	return (ptr);
}
