#include "../../inc/cub3d.h"

//Function that prints number in the rendering window
void	print_nbr(t_mlx *mlx_data, int x, int y, int nbr)
{
	char	*str;

	str = ft_itoa(nbr);
	mlx_string_put(mlx_data->mlx_ptr, mlx_data->win_ptr, x, y, 0xA95C4C, str);
	free (str);
}

//Function that prints text in the rendering window
void	print_str(t_mlx *mlx_data, int x, int y, char *str)
{
	mlx_string_put(mlx_data->mlx_ptr, mlx_data->win_ptr, x, y, 0xA95C4C, str);
}
