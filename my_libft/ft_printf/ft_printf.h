/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:30:46 by mirifern          #+#    #+#             */
/*   Updated: 2024/02/11 23:35:15 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

int	ft_printf(char const *str, ...);
int	ft_putchar(char c, int fd, int *len);
int	ft_putstr(char *s, int fd, int *len);
int	ft_putnbr(int nb, int *len);
int	ft_putunsig(unsigned int nb, int *len);
int	ft_putptr(unsigned long nb, char *base, int *len);
int	ft_puthex(unsigned int nb, char *base, int *len);

#endif
