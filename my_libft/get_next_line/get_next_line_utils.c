/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 00:40:54 by mirifern          #+#    #+#             */
/*   Updated: 2024/06/05 23:01:58 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*f_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	while (i < count * size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*f_strchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;

	i = 0;
	ch = (unsigned char) c;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)s + i + 1);
		i++;
	}
	if (ch == s[i])
		return ((char *)s + i + 1);
	return (NULL);
}

char	*f_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*ptr;
	size_t	len_d;

	i = 0;
	if (s1 == (void *)0 && s2 == (void *)0)
		return (NULL);
	len_d = f_strlen(s1);
	ptr = (char *)malloc((len_d + f_strlen(s2) + 1) * sizeof(char));
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

size_t	f_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_free_str(char *str)
{
	free(str);
	return (NULL);
}
