/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:08:03 by mirifern          #+#    #+#             */
/*   Updated: 2025/01/26 21:43:41 by igarcia2         ###   ########.fr       */
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
# define WIDTH 1000
# define HEIGHT 500
# define TILE_SIZE 64
# define FOV 60

/*Keys*/
# define ESC 65307
# define ENTER 65293
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
# define ERR_EMPTY "Error\nFile is Empty\n"
# define ERR_MAP "Error\nInvalid map\n"

# define ERR_FILE "Error\nInvalid file\n"
# define ERR_OPEN "Error\nCould not open file\n"

# define ERR_MLX_INIT "Error\nmlx : initialization failed\n"
# define ERR_MLX_WIN "Error\nmlx : window creation failed\n"
# define ERR_MLX_IMG "Error\nmlx : image creation failed\n"

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
	char		*ceiling;
	char		*floor;
	int			ceiling_color;
	int			floor_color;
	char		**next_map;
}	t_map;

/*Raycasting data*/
typedef struct	s_raycast
{
	double	distance_pp; //Distance to project plane
	double	angle_increment; //Angle increment
	int		horz_hit[2];
	int		vert_hit[2];
	double	shortest_distance;
	double	corrected_distance;
	int		wall_height;
	int		wall_y;
}	t_raycast;

/*Mlx*/
typedef struct	s_mlx
{
	void	*mlx_ptr; // Puntero a la conexión con MiniLibX
	void	*win_ptr; // Puntero a la ventana
	void	*img_ptr; // Puntero a la imagen
	char	*img_addr; // Dirección de memoria de la imagen
	int		bpp;      // Bits por píxel
	int		line_len; // Longitud de cada línea de la imagen
	int     endian;   // Orden de los bytes (endianess)
	int		redraw;
} t_mlx;

/*Cub3d*/
typedef struct	s_data
{
	t_map			*map_data;
	t_raycast		*ray_data;
	t_mlx			*mlx_data;
	t_player		*player;
	char			**cub_file;
}	t_data;


/*main.c*/
int		main(int ac, char **av);

/*open_file.c*/
int		open_file(char *path, t_data *data);

/*error.c*/
void	ft_error_exit(char *msg, t_data *data);
void	ft_error(char *msg);
void	ft_perror(char *msg);

/*str_utils.c*/
char	**add_to_array(char ***current, char *new_value);

/*free_utils*/
void	free_data(t_data *data);
void	free_str_array(char ***str_array);
void	destroy_mlx(t_data *data);

/*utils.c*/
void	malloc_protection(void *ptr, t_data *data);
double	deg_to_rad(double degrees);
double	normalize_angle(double angle);

/*test_utils.c*/
void	print_str_array(char **str_array);
void	init_map_test(t_map *map, t_data *data);

/*draw_map.c*/
void	draw_map(t_raycast *ray_data, char *img_addr, t_data *data);

/*hit_wall.c*/
void vert_wall_hit(double alpha, t_player *player, t_data *data);
void horz_wall_hit(double alpha, t_player *player, t_data *data);

/*mlx.c*/
int	game_loop(t_data *data);
int	key_hook(int keycode, t_data *data);
void	print_pixel(int x, int y, int color, t_mlx *mlx_data, char *img_addr);

/*mlx_utils.c*/
void	print_nbr(t_mlx *mlx_data, int x, int y, int nbr);
void	print_str(t_mlx *mlx_data, int x, int y, char *str);

#endif

