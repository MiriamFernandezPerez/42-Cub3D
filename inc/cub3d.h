/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:08:03 by mirifern          #+#    #+#             */
/*   Updated: 2025/02/18 22:47:59 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
/*Libraries to Bass*/
# include <stdint.h>
# include <stdbool.h>
# include "../bass/bass.h"
/******************/
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stddef.h>
# include <stdbool.h>
# include <sys/time.h>
# include "../src/libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>

/*Constants*/
# define WIDTH 800 
# define HEIGHT 500
# define TILE_SIZE 32
# define FOV 60
# define PLAYER_SPEED 5
# define EPSILON 0.0001
# define M_PI 3.14159265358979323846
# define ROTATION_SPEED 0.09
# define ALPHA_COLOR 0x08ff00
# define COLLISION_MARGIN 0.15
# define SHADING 1 
# define SHADING_MAX_DISTANCE 500 
# define DOOR_OPEN_DISTANCE TILE_SIZE * 2.5
# define DOOR_CLOSE_DISTANCE TILE_SIZE * 4
# define DOOR_OPEN_TIME 1.5
# define TITLE_IMAGES 8
# define FRAME_DURATION 100

/*audio*/
# define TITLE_AUDIO 'T'
# define DOOR_AUDIO 'D'
# define CHEST_AUDIO 'C'

/*Keys*/
# define KEY_ESC 65307
# define KEY_ENTER 65293
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_SPACE 32

/*cub_file*/
# define NORTH_TXT "NO "
# define SOUTH_TXT "SO "
# define WEST_TXT "WE "
# define EAST_TXT "EA "
# define FLOOR "F "
# define CEIL "C "
# define DOOR "D "
# define NEXT_MAP "NEXT "
# define EXIT "EXIT "
# define CHEST "CHEST "
# define KEY "KEY " 
# define COIN "COIN "
# define VALID_TILES "01NSWEDXQKC "
# define SPRITE_TILES "XQKC"
# define INTERACTABLE_TILES "CKQX"
# define COLLECTABLE_TILES "CQK"
# define CROSSABLE_TILES "0DNSEWXLQC"

/*id_cub_file_settings & textures ID*/
# define ID_NORTH 'N'
# define ID_SOUTH 'S'
# define ID_WEST 'W'
# define ID_EAST 'E'
# define ID_FLOOR 'F'
# define ID_CEIL 'C'
# define ID_DOOR 'D' //Door_id
# define ID_CHEST 'Q' //Chest_id
# define ID_KEY 'K' //Key_id
# define ID_COIN 'I' //Coin_id
# define ID_EXIT 'X' //Exit_id
# define ID_MAP 'M' //Next Map_id

/*Minimap*/
# define MINIMAP_WIDTH 0.2
# define MINIMAP_HEIGHT 0.2
# define MINIMAP_MARGIN 0.02
# define TILES_VERTICAL 13
# define MINIMAP_BACK_COLOR 0x5A5858
# define MINIMAP_PLAYER_COLOR 0xFF0000
# define MINIMAP_WALL_COLOR 0xA7A6A6
# define MINIMAP_FLOOR_COLOR 0x363333
# define MINIMAP_DOOR_COLOR 0x505050
# define MINIMAP_BORDER_COLOR 0x000000
# define MINIMAP_SHADOW_COLOR 0x2C2C2C

/*Errors*/
# define ERR_ARGS "Error\nInvalid number of arguments\n"
# define ERR_EXT "Error\nInvalid file extension\n"
# define ERR_MALLOC "Error\nMemory allocation failed\n"
# define ERR_CPY "Error\nMemory error when duplicating map\n"
# define ERR_EMPTY "Error\nFile is Empty\n"
# define ERR_MAP "Error\nInvalid map\n"
# define ERR_TXT "Error\nInvalid textures in configuration map\n"
# define ERR_PATH "Error\nCan't open texture path\n"
# define ERR_NEXT "Error\nNext map file is not a .cub file\n"
# define ERR_OPEN_NEXT "Error\nCan't open next_map file\n"
# define ERR_COLOR "Error\n.Invalid color format\n"
# define ERR_RGB "Error\n. Invalid RGB configuration\n"
# define ERR_FILE "Error\nInvalid file\n"
# define ERR_OPEN "Error\nCould not open file\n"
# define ERR_CONF "Error\nRequired sections missing from .cub file\n"
# define ERR_INV_CHAR "Error\nInvalid character in map\n"
# define ERR_PLAYER "Error\nMap must have only one player\n"
# define ERR_EXIT "Error\nMap must have one exit as a maximum\n"
# define ERR_NO_EXIT "Error\nPlayer can't access to the exit\n"
# define ERR_DOOR "Error\nInvalid door at map\n"
# define ERR_NO_COLLECT "Error\nPlayer can't access to all the collectibles\n"
# define ERR_KEY "Error\nPlayer can't access to all the key\n"
# define ERR_KET_QT "Error\nMap must have one key exit as a maximun\n"
# define ERR_BORDER "Error\nThe map must be closed/surrounded by walls\n"
# define ERR_SOLUT "Error\nInvalid Map, player can't visit all the spaces\n"
# define ERR_START "Error\nCan't open start screen files\n"
# define NO_PLAY "Don't you want to play? Maybe later, see you :)!!\n"
# define ERR_MLX_INIT "Error\nmlx : initialization failed\n"
# define ERR_MLX_WIN "Error\nmlx : window creation failed\n"
# define ERR_MLX_IMG "Error\nmlx : image creation failed\n"
# define ERR_LOAD_TXT "Error\nTextures load failed\n"
# define ERR_LOAD_IMG "Error\nError loading images\n"
# define ERR_MAP_CHAR "Error\nInvalid map character\n"
# define ERR_MAP_BORDER "Error\nMap is not closed\n"
# define ERR_MAP_PLAYER "Error\nPlayer is not in the map\n"
# define ERR_MAP_EMPTY "Error\nMap is empty\n"
# define ERR_BASS "Error\nBass Library failed\n"
# define ERR_BASS_FILE "Error\nBass Create File failed\n"

/*Coordinates*/
typedef enum e_coord
{
	X = 0,
	Y = 1,
	HORZ = 0,
	VERT = 1,
	TRUE = 1,
	FALSE = 0
}	t_coord;

typedef enum e_rgb_matrix
{
	R = 0,
	G = 1,
	B = 2
}	t_rgb_matrix;

/*Tile Type*/
typedef enum e_tile_type
{
	TILE_WALL = '1',
	TILE_FLOOR = '0',
	TILE_SPACE = ' ',
	TILE_N = 'N',
	TILE_E = 'E',
	TILE_W = 'W',
	TILE_S = 'S',
	TILE_DOOR = 'D',
	TILE_EXIT = 'X',
	TILE_CHEST = 'Q',
	TILE_KEY = 'K',
	TILE_COIN = 'C'
}	t_tile_type;

typedef enum e_door_state
{
	CLOSED,
	OPENED,
	OPENING,
	CLOSING
}	t_door_state;

typedef enum e_sprite_type
{
	COLLECTABLE,
	DECORATION,
	ENEMY
}	t_sprite_type;

typedef enum e_collectable_type
{
	T_CHEST,
	T_COIN,
	T_KEY
}	t_collectable_type;

/*Player*/
typedef struct s_player
{
	int		pos[2];
	int		coord[2];
	double	angle;
	int		exit_reached;
}	t_player;

/*Texture images*/
typedef struct s_texture
{
	void				*img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
	char				id_txt;
	int					width;
	int					height;
	char				*path;
	struct s_texture	*next;
}				t_texture;

/*Images*/
typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_sprite
{
	t_sprite_type	type;
	int				subtype;
	int				grid[2];
	int				world[2];
	int				size[2];
	int				start[2];
	double			distance;
	int				txt_num;
	int				frame;
	unsigned long	last_frame_time;
	int				visible_horz;
	int				visible_vert;
	struct s_sprite	*next;
}	t_sprite;


/*Door data*/
typedef struct s_door
{
	int				grid[2];
	int				orient;
	t_door_state	state;
	float			offset;
	double			timer;
	struct s_door	*next;
}	t_door;

/*Map info*/
typedef struct s_map
{
	char		**map;
	int			max_height;
	int			max_width;
	int			ceiling_color;
	int			floor_color;
	int			floor_tiles_qt;
	int			floor_tiles_found;
	int			exit_qt;
	int			key_qt;
	char		*next_map;
	t_texture	*txt_list;
	t_door		*door_list;
	t_sprite	*sprite_list;
}	t_map;

/*Raycasting data*/
typedef struct s_raycast
{
	double	distance_pp;
	double	angle_increment;
	double	alpha;
	double	horz_hit[2];
	double	vert_hit[2];
	int		vtx_hit;
	double	shortest_distance;
	double	corrected_distance;
	int		wall_height;
	int		wall_y;
	t_door	*door;
	float	pixel_distance;
	float	intensity;
}	t_raycast;

/*Minimap data*/
typedef struct s_minimap
{
	int		size[2];
	int		start[2];
	int		margin[2];
	int		tile_size;
	int		tiles_horz;
	double	shortest_distances[WIDTH];
	double	angle_step;
	double	scale;
}	t_minimap;

/*Title screen*/
typedef struct s_title
{
    t_img   imgs[TITLE_IMAGES];
	char	*paths[TITLE_IMAGES];
	int		blink; 
	int		selected;
}   t_title;

/*Mlx*/
typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_addr;
	char	*new_img_addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		redraw;
	int		key_pressed;
	int		mouse_pos;
}	t_mlx;




/*Audio*/
typedef struct s_audio
{
	uint32_t		bass_id;
	int				audio_id;
	struct s_audio	*next;
} 	t_audio;


/*Cub3d*/
typedef struct s_data
{
	t_map			*map_data;
	t_raycast		*ray_data;
	t_minimap		*minimap_data;
	t_mlx			*mlx_data;
	t_player		*player;
	t_title			*title_data;
	char			**cub_file;
	t_audio			*audio_list;
}	t_data;

/*main.c*/
int			main(int ac, char **av);

/*init.c*/
void		init_data(t_data **data);
void		init_minimap_data(t_minimap *minimap_data);
void		init_map(t_map *map_data);
void		init_mlx(t_data *data);
void		init_textures(t_texture *txt_data, t_mlx *mlx_data,	t_data *data);

/*open_file.c*/
void		try_open_path(t_data *data, char *path);
int			read_file(int fd, t_data *data);
int			open_cub_file(char *path, t_data *data);

/*parse_file.c*/
int			check_tiles_between(char **map, int y, int x);
char		*parse_path(char *line, t_data *data, char id);
int			parse_line(t_data *data, char *line);
void		parse_cub_file(t_data *data, char **cub_file);

/*parse_map.c*/
void		validate_extras(t_data *data, char **map);
int			check_tiles_between_door(char **map, int y, int x, t_data *data);
void		validate_map_border(t_data *data, t_map *map_data, char **map);
void		normalize_map(t_data *data, char **map);
void		parse_map(t_data *data, char **map_line);

/*validate_tiles.c*/
int			check_tiles_between_exit(char **map, int y, int x);
void		validate_exit(t_data *data, char **map, int *grid);
int			check_player(t_data *data, int y, int x);
void		validate_player(t_data *data, char **map);
void		validate_tiles(t_data *data, char **map);

/*validate_txt_and_colors.c*/
void		validate_conf_textures(t_data *data);
int			check_rgb(char *path, int *i);
int			rgb_to_hex(char *path);
int			check_color_or_texture(t_data *data, char *path, char id);
void		check_exit_sprite(char *path, t_data *data, int id);

/*flood_fill.c*/
void		validate_map_route(t_data *data);

/*error.c*/
void		ft_error_exit(char *msg, t_data *data);
void		ft_error(char *msg);
void		ft_perror(char *msg);

/*str_utils.c*/
char		*load_path(int i);
char		**add_to_array(char ***current, char *new_value);

/*free_utils*/
void		free_data(t_data *data);
void		free_str_array(char ***str_array);
void		destroy_mlx(t_data *data);

/*utils.c*/
void		malloc_protection(void *ptr, t_data *data);
double		deg_to_rad(double degrees);
double		normalize_angle(double angle);
int			only_spaces(const char *str);
int			calculate_angle(char **map, int x, int y);
long		get_time();

/*free_utils.c*/
void		free_map(t_map *map_data, t_mlx *mlx_data);

/*title_screen.c*/
void		init_title(t_title *title_data);
void 		title_screen(t_title *title_data, t_data *data);

/*image_utils.c*/
t_img		create_new_img(int width, int height, t_data *data);
void		load_xpm_image(t_img *img, char *path, t_data *data);
void		scale_image(t_img *img, int new_width, int new_height, t_data *data);

/*test_utils.c*/
void		print_str_array(char **str_array);
void		init_map_test(t_map *map, t_data *data);
void		print_player_info(t_data *data);
void		print_nbr(t_mlx *mlx_data, int x, int y, int nbr);
void		print_str(t_mlx *mlx_data, int x, int y, char *str);
void		print_ray_data(t_raycast *ray_data);

/*texture_list.c*/
void		add_texture_node(char id_texture, char *path, t_data *data);
void		clear_txt_list(t_texture **txt_list, t_mlx *mlx_data);
t_texture	*get_texture(char id_txt, t_data *data);

/*door_list.c*/
void		add_door_node(int grid[2], int orient, t_data *data);
void		clear_door_list(t_door **door_list);
t_door		*get_door(int grid[2], t_data *data);

/*audio_list.c*/
void		add_audio_node(char id_audio, uint32_t bass_id, t_data *data);
void		clear_audio_list(t_audio **audio_list);
t_audio		*get_audio(char audio_id, t_data *data);

/*sprite_list.c*/
void		add_sprite_node(t_sprite_type type, int subtype, int grid[2],
			t_data *data);
void		clear_sprite_list(t_sprite **sprite_list);
t_sprite	*get_sprite(int grid[2], t_data *data);
void		delete_sprite(t_sprite *sprite, t_data *data);

/*raycast_manager.c*/
void		raycast_manager(t_raycast *ray_data, t_data *data);

/*hit_wall.c*/
void		vert_hit(double alpha, t_player *player, t_data *data);
void		horz_hit(double alpha, t_player *player, t_data *data);

/*render_wall.c*/
void		render_wall(int x, int *y, t_raycast *ray_data, t_data *data);

/*render_ceil_floor.c*/
void		render_ceil_floor(int x, int *y, t_data *data);

/*door.c*/
int			door_hit(t_door *door, double hit[2], double delta[2]);
int			is_door_hit(t_raycast *ray_data, t_data *data);
void		render_door(int x, int *y, t_raycast *ray_data, t_data *data);

/*render_sprite.c*/
void		render_sprite(int x, int y, t_data *data);

/*sprite.c*/
void		reset_sprite_visibility(t_map *map_data);
void		set_sprite_visible(int grid[2], int intersection,  t_data *data);

/*render_utils.c*/
int			get_texture_pxl(t_texture *texture, int x, int y);
int			get_tile_type(int grid[2], t_map *map_data);
void		get_grid_back_hit(int grid[2], t_raycast *ray_data);
double		calculate_distance(double x1, double y1, double x2, double y2);

/*minimap.c*/
void		create_minimap(t_minimap *minimap_data, t_mlx *mlx_data,
				t_data *data);

/*minimap_utils.c*/
void		print_tile_pixel(int x, int y, int map_idx[2], t_data *data);
void		print_triangle(int v[3][2], int color, t_mlx *mlx_data);

/*mlx.c*/
int			key_press(int keycode, t_data *data);
int			key_release(int keycode, t_data *data);
int			close_window(t_data *data);

/*game_loop.c*/
int			game_loop(t_data *data);

/*mlx_print.c*/
void		print_pixel_render(int x, int y, int color, t_data *data);
void		print_pixel_sprite(int pos[2], int color, t_sprite sprite, t_data *data);
void		print_gui_pixel(int x, int y, int color, t_mlx *mlx_data);

/*mlx_mouse*/
int 		mouse_handler(int x, int y, t_data *data);

/*audio.c*/
void	play_sound(char audio_id, bool play, bool loop, t_data *data);
void	stop_audio(char audio_id, t_data *data);
void	init_audio(t_data *data);

#endif
