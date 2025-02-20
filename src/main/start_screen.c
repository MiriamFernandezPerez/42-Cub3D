/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:17:27 by mirifern          #+#    #+#             */
/*   Updated: 2025/02/18 22:17:29 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*void	show_image_with_fade(t_data *data, t_start *img)
{
	int		alpha;
	t_mlx	*info;

	alpha = 0;
	info = data->mlx_data;
	while (alpha <= 255)
	{
		if (!img || !img->img)
			return ;
		mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, img->img, 0, 0);
		usleep(5000);
		alpha += 5;
	}
}*/

void	*load_xpm_image(char *path, t_data *data)
{
	void	*img;
	t_mlx	*info;
	int		width;
	int		height;

	info = data->mlx_data;
	width = data->start->width;
	height = data->start->height;
	img = mlx_xpm_file_to_image(info->mlx_ptr, path, &width, &height);
	if (!img)
		return (NULL);
	return (img);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
		data->start->selected = 2;
	if (keycode == KEY_RIGHT)
		data->start->selected = 1;
	if (keycode == KEY_SPACE && data->start->selected == 1)
	{
		printf("EMPIEZA EL JUEGO %d\n", keycode);
		mlx_loop_hook(data->mlx_data->mlx_ptr, game_loop, data);
	}
	else if (keycode == KEY_SPACE && data->start->selected == 2)
	{
		ft_putstr_fd(NO_PLAY, STDERR_FILENO);
		free_data(data);
		exit(0);
	}
	return (0);
}

int	start_loop(t_data *data)
{
	int		index;
	t_mlx	*info;
	//int		x;
	//int		y;

	info = data->mlx_data;
	if (data->start->blink)
		index = data->start->selected;
	else
		index = 0;
	if (index < 0 || index >= 3 || !data->start->img[index])
	{
		ft_error(ERR_START);
		return (0);
	}
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, data->start->img[index], 0, 0);
	usleep(160000);
	data->start->blink = !data->start->blink;
	return (0);
}

void	destroy_n_exit(t_data *data, void **image)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (image[i] != NULL)
		{
			mlx_destroy_image(data->mlx_data->mlx_ptr, image[i]);
			image[i] = NULL;
		}
		i++;
	}
	ft_putstr_fd(ERR_START, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	start_screen(t_data *data)
{
	void	*image[3];

	image[0] = load_xpm_image("./sources/start_screen/start_screen0.xpm", data);
	image[1] = load_xpm_image("./sources/start_screen/start_screen1.xpm", data);
	image[2] = load_xpm_image("./sources/start_screen/start_screen2.xpm", data);
	if (!image[0] || !image[1] || !image[2])
		destroy_n_exit(data, (void **)image);
	//show_image_with_fade(data, image[0]);
	data->start->img[0] = image[0];
	data->start->img[1] = image[1];
	data->start->img[2] = image[2];
	mlx_key_hook(data->mlx_data->win_ptr, key_hook, data);
	data->start->blink = 0;
	data->start->selected = 1;
	mlx_loop_hook(data->mlx_data->mlx_ptr, start_loop, data);
}

//iniciar loop_hook de la pantalla de inicio y quitar el game_loop
// y el key_hook, activarlo despues
//de que el player inicie el juego en el boton start 