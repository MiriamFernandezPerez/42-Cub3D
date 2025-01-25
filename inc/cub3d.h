/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:08:03 by mirifern          #+#    #+#             */
/*   Updated: 2025/01/22 19:03:05 by igarcia2         ###   ########.fr       */
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
# include "../src/libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>


# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

/*Constants*/
# define WIDTH 60
# define HEIGHT 30
# define BLOCK_SIZE 64
# define FOV 60

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
# define ERR_MALLOC "Error\nMemory allocation failed\n"

# define ERR_FILE "Error\nInvalid file\n"
# define ERR_OPEN "Error\nCould not open file\n"
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

/*Coordinates*/
typedef enum
{
    X = 0,  // Represents index 0
    Y = 1   // Represents index 1
} coordinates;

/*Tile Type*/
typedef enum
{
    TILE_WALL = '1',
    TILE_EMPTY = '0',
    TILE_PLAYER_N = 'N',
    TILE_PLAYER_E = 'E',
    TILE_PLAYER_W = 'W',
    TILE_PLAYER_S = 'S',
	TILE_DOOR = 'D',
    TILE_EXIT = 'X'
} tile_type;

/*Player*/
typedef struct s_player
{
	int		pos[2]; //X and Y 
	double	angle; //Direction
}	t_player;

/*Color*/
typedef struct s_color
 {
	int r;
	int g;
	int b;
} t_color;

/*Map info*/
typedef struct s_map
{
	char		**map;
	int			max_height;
	int			max_width;
	char		*north_texture_path;
	char		*south_texture_path;
	char		*east_texture_path;
	char		*west_texture_path;
	t_color		*floor;
	t_color		*ceiling;
	char		**next_map;
}	t_map;

/*Raycasting data*/
typedef struct s_raycast
{
	double	distance_pp; //Distance to project plane
	double	angle_increment; //Angle increment
	int		h_intersect[2];
	int		v_intersect[2];
	double	h_distance;
	double	v_distance;
}	t_raycast;

/*Cub3d*/
typedef struct s_data
{
	t_map			*map_data;
	t_raycast		*ray_data;
	char			**cub_file;
	t_player		*player;
}	t_data;


/*main.c*/
int		main(int ac, char **av);

/*open_file.c*/
int		open_file(char *path, t_data *data);

/*error.c*/
void	ft_error(char *msg);
void	ft_perror(char *msg);

/*str_utils.c*/
char	**add_to_array(char ***current, char *new_value);

/*free_utils*/
void	free_data(t_data *data);
void	free_str_array(char ***str_array);

/*utils.c*/
void	malloc_protection(void *ptr, t_data *data);
double	deg_to_rad(double degrees);

/*test_utils.c*/
void	print_str_array(char **str_array);
void	init_map_test(t_map *map, t_data *data);

/*draw_map.c*/
void	draw_map(t_raycast *ray_data, t_data *data);

#endif

