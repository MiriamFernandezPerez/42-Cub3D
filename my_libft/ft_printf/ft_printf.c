/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:11:21 by mirifern          #+#    #+#             */
/*   Updated: 2024/02/12 20:36:53 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_format(va_list arg, char c, int *len)
{
	int	ctr;

	ctr = 0;
	if (c == 'c')
		ctr = ft_putchar(va_arg(arg, int), 1, len);
	else if (c == 's')
		ctr = ft_putstr(va_arg(arg, char *), 1, len);
	else if (c == 'i' || c == 'd')
		ctr = ft_putnbr(va_arg(arg, int), len);
	else if (c == '%')
		ctr = ft_putchar('%', 1, len);
	else if (c == 'x')
		ctr = ft_puthex(va_arg(arg, unsigned int), "0123456789abcdef", len);
	else if (c == 'X')
		ctr = ft_puthex(va_arg(arg, unsigned int), "0123345789ABCDEF", len);
	else if (c == 'p')
		ctr = ft_putptr(va_arg(arg, unsigned long), "0123456789abcdef", len);
	else if (c == 'u')
		ctr = ft_putunsig(va_arg(arg, unsigned int), len);
	return (ctr);
}

int	ft_printf(char const *str, ...)
{
	int		len;
	int		i;
	va_list	args;
	int		ctr;

	len = 0;
	i = 0;
	ctr = 0;
	va_start(args, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
			ctr = ft_check_format(args, str[++i], &len);
		else
			ctr = ft_putchar(str[i], 1, &len);
		if (ctr == -1)
			return (-1);
		if (str[i] != '\0')
			i++;
	}
	return (len);
}
/*
#include <limits.h>

int	main()
{
	
	void	*ptr;

	ptr = "NULL noooooo";

	printf("\n****** Solo texto ******\n");
	printf("%i\n", printf("Hola\n"));
	printf("%i\n", ft_printf("Hola\n"));


	printf("\n***** CHAR ******\n");
	printf("%i\n", printf("Mi nombre empieza por la letra %c\n", 'M'));
	printf("%i\n", ft_printf("Mi nombre empieza por la letra %c\n", 'M'));
	

	printf("\n***** STR ******\n");
	printf("%i\n", printf("Hola %s\n", "Miriam"));
	printf("%i\n", ft_printf("Hola %s\n", "Miriam"));
	printf("%i\n", printf("%s", (char *)NULL));	
	printf("%i\n", ft_printf("%s", (char *)NULL));	
	printf("%i\n", printf(" NULL %s NULL ", NULL));
	printf("%i\n", ft_printf(" NULL %s NULL ", NULL));

	printf("\n***** NUM ******\n");
	printf("%i\n", printf("Hola %i\n", 42));
	printf("%i\n", ft_printf("Hola %i\n", 42));
	printf("%d\n", printf("Hola %d\n", -4242));
	printf("%d\n", ft_printf("Hola %d\n", -4242));
	printf("%i\n", printf("Hola %i\n", INT_MIN));	
	printf("%i\n", ft_printf("Hola %i\n", INT_MIN));	

	printf("\n***** UNSIGNED ******\n");
	printf("%i\n", printf("%u\n", -1));
	ft_printf("%i\n", ft_printf("%u\n", -1));

	printf("\n***** %% ******\n");
	//printf("%i\n", printf("Hola %%\n"));
	//printf("%i\n", ft_printf("Hola %%\n"));
	//printf("%i\n", printf("%"));
	printf("%i\n", ft_printf("%"));

	printf("\n***** HEXADECIMAL ******\n");
	printf("%i\n", printf("%x\n", -42));
	printf("%i\n", ft_printf("%x\n", -42));
	printf("%i\n", printf("%X\n", -1));
	printf("%i\n", ft_printf("%X\n", -1));

	printf("%i\n", printf("%X\n", 9));
	printf("%i\n", ft_printf("%X\n", 9));
	printf("%i\n", printf("%X\n", 10));
	printf("%i\n", ft_printf("%X\n", 10));
	
	printf("\n***** PUNTERO ******\n");
	printf("%i\n", printf("%p\n", ptr));
	ft_printf("%i\n", ft_printf("%p\n", ptr));
	
	printf("%i\n", printf("%p\n", (void *) -14523));
	printf("%i\n", ft_printf("%p\n", (void *) -14523));

	return (0);
}*/
