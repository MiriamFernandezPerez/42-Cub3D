/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:08:03 by mirifern          #+#    #+#             */
/*   Updated: 2024/12/19 21:08:15 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stddef.h>
# include "../my_libft/libft.h"
# include "../my_libft/get_next_line/get_next_line.h"
# include "../mlx_linux/mlx.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>

/*Keys*/
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

/*Errors*/
# define ERR_ARGS "Error\nInvalid number of arguments\n"
# define ERR_EXT "Error\nInvalid file extension\n"
# define ERR_FILE "Error\nInvalid file\n"


# define ERR_OPEN "Error\nCould not open file\n"
# define ERR_MALLOC "Error\nMemory allocation failed\n"
# define ERR_MAP "Error\nInvalid map\n"
# define ERR_PLAYER "Error\nInvalid player\n"
# define ERR_MAP_CHAR "Error\nInvalid map character\n"
# define ERR_MAP_BORDER "Error\nMap is not closed\n"
# define ERR_MAP_PLAYER "Error\nPlayer is not in the map\n"
# define ERR_MAP_EMPTY "Error\nMap is empty\n"
//# define ERR_MAP_RES "Error\nMap resolution is too low\n"
//# define ERR_MAP_RES2 "Error\nMap resolution is too high\n"
//# define ERR_MAP_TEX "Error\nMap texture is missing\n"
//# define ERR_MAP_COLOR "Error\nMap color is missing\n"
//# define ERR_RES "Error\nInvalid resolution\n"
//# define ERR_TEX "Error\nInvalid texture\n"
//# define ERR_COLOR "Error\nInvalid color\n"


typedef struct s_map
{
	char	**map;
	int		max_height;
	int		max_width;
	t_color floor;
	t_color ceiling;
	//textura este
	//texturo oeste
	//textura norte
	//textura sur
	t_player *player;
}	t_map;

/*Player*/
typedef struct s_player
{
	int		pos[2];
	char	dir;
}	t_player;

typedef struct s_color
 {
	int r;
	int g;
	int b;
} t_color;

/*Cub3d*/
typedef struct s_data
{

}	t_data;


/*main.c*/
int		main(int ac, char **av);

/*check_args.c*/
int	check_args(int ac, char **av);

#endif

