/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:05:41 by mirifern          #+#    #+#             */
/*   Updated: 2024/12/19 21:05:48 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/cub3d.h"

int	main(int ac, char **av)
{

	if (check_args(ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	/*if (open(av[1], O_RDONLY) == -1)
		return (ft_error(ERR_OPEN), EXIT_FAILURE);*/
	return (0);
}
