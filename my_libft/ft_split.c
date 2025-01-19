/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 00:04:42 by mirifern          #+#    #+#             */
/*   Updated: 2024/01/30 23:42:52 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int	i;
	int	num;
	int	x;

	i = 0;
	num = 0;
	x = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && x == 0)
		{
			x = 1;
			num++;
		}
		else if (s[i] == c)
			x = 0;
		i++;
	}
	return (num);
}

static char	**ft_free(char **ptr, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

static int	ft_cut_word(char **ptr, char const *str, char c, int index)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (str[end])
	{
		if (str[end] == c || str[end] == '\0')
			start = end + 1;
		if (str[end] != c && (str[end + 1] == c || str[end + 1] == '\0'))
		{
			ptr[index] = malloc(((end - start) + 2) * sizeof(char));
			if (!ptr[index])
			{
				ft_free(ptr, index);
				return (0);
			}
			ft_strlcpy(ptr[index], (str + start), end - start + 2);
			index++;
		}
		end++;
	}
	ptr[index] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**ptr;

	if (!s)
		return (NULL);
	words = ft_count(s, c);
	ptr = ft_calloc((words + 1), sizeof(char *));
	if (!ptr)
		return (NULL);
	if (!ft_cut_word(ptr, s, c, 0))
		return (NULL);
	return (ptr);
}
