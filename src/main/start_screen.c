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

void show_image_with_fade(t_data *data, t_start *img)
{
	int alpha = 0;
	while (alpha <= 255)
	{
		if (!img || !img->img)
			return;
		mlx_put_image_to_window(data->mlx_data->mlx_ptr, data->mlx_data->win_ptr, img->img, 0, 0);
		usleep(5000);
		alpha += 5;
	}
}

void *load_xpm_image(char *path, t_data *data)
{
	void	*img;

	img = mlx_xpm_file_to_image(data->mlx_data->mlx_ptr, path, &data->start->width, &data->start->height);
	if (!img)
		return (NULL);
	return (img);
}

int key_hook(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
		data->start->selected = 2;
	if (keycode == KEY_RIGHT)
		data->start->selected = 1;
	if (keycode == KEY_ENTER && data->start->selected == 1)
	{
		printf("EMPIEZA EL JUEGO %d\n", keycode);
	}
	else if (keycode == KEY_ENTER && data->start->selected == 2)
	{	
		ft_putstr_fd(NO_PLAY, STDERR_FILENO);
        free_data(data);
		exit(0);
	}
	return (0);
}

int	start_loop(t_data *data)
{

	int index;

	index = data->start->blink ? data->start->selected : 0;
    printf("selected: %d\n", index);
    if (index < 0 || index >= 3 || !data->start->img[index])
    {
        fprintf(stderr, "Error: imagen inválida en start->img[%d]\n", index);
        return (0);
    }
    mlx_put_image_to_window(data->mlx_data->mlx_ptr, data->mlx_data->win_ptr, data->start->img[index], 0, 0);
    usleep(150000);
    data->start->blink = !data->start->blink;
    return (0);
}

void	start_screen(t_data *data)
{
	void *image[3];

	image[0] = load_xpm_image("./sources/start_screen/start_screen0.xpm", data);
	image[1] = load_xpm_image("./sources/start_screen/start_screen1.xpm", data);
	image[2] = load_xpm_image("./sources/start_screen/start_screen2.xpm", data);

	if (!image[0] || !image[1] || !image[2])
		ft_error_exit(ERR_START, data);
	//show_image_with_fade(data, image[0]);

	data->start->img[0] = image[0];
	data->start->img[1] = image[1];
	data->start->img[2] = image[2];
	mlx_key_hook(data->mlx_data->win_ptr, key_hook, data);
	data->start->blink = 0;
	data->start->selected = 1;
	mlx_loop_hook(data->mlx_data->mlx_ptr, start_loop, data);
}

//iniciar loop_hook de la pantalla de inicio y quitar el game_loop y el key_hook, activarlo despues
//de que el player inicie el juego en el boton start 