/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 00:41:13 by mirifern          #+#    #+#             */
/*   Updated: 2024/06/05 23:01:13 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free_strjoin(char *buffer, char *str)
{
	char	*new_str;

	if (!buffer)
	{
		buffer = malloc(sizeof(char) * 1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	new_str = f_strjoin(buffer, str);
	free(buffer);
	return (new_str);
}

char	*ft_clean_buffer(char *buffer)
{
	int		i;
	int		n;
	char	*new_buf;

	i = 0;
	n = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	new_buf = f_calloc(sizeof(char), f_strlen(buffer));
	if (!new_buf)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	while (buffer[i] != '\0')
		new_buf[n++] = buffer[i++];
	free(buffer);
	return (new_buf);
}

char	*ft_make_line(char *buffer)
{
	int		i;
	char	*line;
	int		bits;

	i = 0;
	bits = 1;
	if (buffer[i] == '\0')
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		bits = 2;
	line = f_calloc(sizeof(char), (i + bits));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*ft_read(int fd, char *buffer)
{
	int		nbytes;
	char	*str;

	str = f_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!str)
		return (ft_free_str(buffer));
	nbytes = 1;
	while (nbytes > 0)
	{
		nbytes = read(fd, str, BUFFER_SIZE);
		if (nbytes == -1)
		{
			free(str);
			free(buffer);
			return (NULL);
		}
		str[nbytes] = '\0';
		buffer = ft_free_strjoin(buffer, str);
		if (!buffer)
			return (ft_free_str(str));
		if (f_strchr(buffer, '\n'))
			break ;
	}
	free(str);
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = ft_read(fd, buffer[fd]);
	if (buffer[fd] == NULL)
		return (NULL);
	line = ft_make_line(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = ft_clean_buffer(buffer[fd]);
	return (line);
}
/*
int	main(void)
{
	int	fd;

	fd = open("../files_get_next_line/empty", O_RDONLY);
	//printf("fd=%i\n", fd);
	if (fd != -1)
	{
		printf("1-%s", get_next_line(fd));
		printf("2-%s\n", get_next_line(fd));
		printf("3-%s\n", get_next_line(fd));
		printf("4-%s\n", get_next_line(fd));
		printf("5-%s\n", get_next_line(fd));
		printf("6-%s\n", get_next_line(fd));
		printf("7-%s\n", get_next_line(fd));
		printf("8-%s\n", get_next_line(fd));
		printf("9-%s\n", get_next_line(fd));
		printf("10-%s\n", get_next_line(fd));
		printf("11-%s\n", get_next_line(fd));
		printf("12-%s\n", get_next_line(fd));
		printf("13-%s\n", get_next_line(fd));
		printf("14-%s\n", get_next_line(fd));
	}
	if (fd == -1)
		write(1, "Archivo no encontrado o no legible\n", 35);
	close(fd);
	return (fd);
}*/
