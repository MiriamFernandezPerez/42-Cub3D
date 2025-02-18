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
		usleep(5000); // Controla la velocidad del fade-in
		alpha += 5;
	}
}

t_start *load_xpm_image(char *path, t_data *data)
{
	t_start *img;

	img = malloc(sizeof(t_start));
	malloc_protection(img, data);
	if (!img)
		return (NULL);
	img->img = mlx_xpm_file_to_image(data->mlx_data->mlx_ptr, path, &img->width, &img->height);
	if (img->img == NULL)
	{
		free(img);
		printf("salgo aquin\n");
		return (NULL);
	}
	return (img);
}

int key_hook(int keycode, t_data *data)
{
	(void)data;
	if (keycode == KEY_LEFT)
		data->selected = 2;
	if (keycode == KEY_RIGHT)
		data->selected = 1;
	if (keycode == KEY_ENTER && data->selected == 1)
		printf("entro al juego\n");
	else if (keycode == KEY_ENTER && data->selected == 2)
		printf("salgo y libero\n"); //utilizar la funcion free_data y anadir los free que faltan en data
	return (0);
}

int	start_loop(t_data *data)
{

	printf("mehagotodoelrato\n");
	printf("selected: %d\n", data->blink ? data->selected : 0);
	mlx_put_image_to_window(data->mlx_data->mlx_ptr, data->mlx_data->win_ptr, data->start[data->blink ? data->selected: 0]->img, 0, 0);
	usleep(150000);
	printf("usle?\n");
	data->blink = !data->blink;
	return (0);
}

void start_screen(t_data *data)
{
	t_start *images[3];


	images[0] = load_xpm_image("./sources/start_screen/start_screen0.xpm", data);
	images[1] = load_xpm_image("./sources/start_screen/start_screen1.xpm", data);
	images[2] = load_xpm_image("./sources/start_screen/start_screen2.xpm", data);

	if (!images[0] || !images[1] || !images[2])
	{
		printf("Error: No se pudieron cargar las imágenes de la pantalla de inicio\n");
		exit(1);
	}

	show_image_with_fade(data, images[0]);

	data->start[0] = images[0];
	data->start[1] = images[1];
	data->start[2] = images[2];
	mlx_key_hook(data->mlx_data->win_ptr, key_hook, data);
	data->blink = 0;
	data->selected = 1;
	mlx_loop_hook(data->mlx_data->mlx_ptr, start_loop, data);
}

//iniciar loop_hook de la pantalla de inicio y quitar el game_loop y el key_hook, activarlo despues
//de que el player inicie el juego en el boton start 