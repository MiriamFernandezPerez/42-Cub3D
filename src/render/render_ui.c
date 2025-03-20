/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 02:27:49 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/18 22:44:15 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../inc/ui.h"

int	get_ui_txt_color(int x, int y, int sprite_size, t_texture *texture)
{
	int			color;
	double		txt[2];

	color = 0x000000;
	if (!texture)
		return (color);
	txt[X] = x / ((double)sprite_size * (texture->width / texture->height));
	txt[X] = txt[X] * texture->width;
	txt[Y] = y / (double)sprite_size * texture->height;
	txt[X] = fmod(txt[X], texture->width);
	txt[Y] = fmod(txt[Y], texture->height);
	color = get_texture_pxl(texture, txt[X], txt[Y]);
	return (color);
}

void	print_ui_sprite(int pos[2], int sprite_size, int txt_id, t_data *data)
{
	int			i[2];
	int			color;
	t_texture	*texture;

	texture = get_texture(txt_id, data);
	i[Y] = pos[Y];
	while (i[Y] < pos[Y] + sprite_size)
	{
		i[X] = pos[X];
		while (i[X] < pos[X]
			+ (sprite_size * (texture->width / texture->height)))
		{
			color = get_ui_txt_color(i[X] - pos[X], i[Y] - pos[Y],
					sprite_size, texture);
			print_gui_pixel(i[X], i[Y], color, data->mlx_data);
			i[X]++;
		}
		i[Y]++;
	}
	pos[X] = pos[X] + (sprite_size * (texture->width / texture->height));
}

void	select_digit_txt(int pos[2], int sprite_size, int num, t_data *data)
{
	if (num == 0)
		print_ui_sprite(pos, sprite_size, ID_DIGIT_0_UI, data);
	else if (num == 1)
		print_ui_sprite(pos, sprite_size, ID_DIGIT_1_UI, data);
	else if (num == 2)
		print_ui_sprite(pos, sprite_size, ID_DIGIT_2_UI, data);
	else if (num == 3)
		print_ui_sprite(pos, sprite_size, ID_DIGIT_3_UI, data);
	else if (num == 4)
		print_ui_sprite(pos, sprite_size, ID_DIGIT_4_UI, data);
	else if (num == 5)
		print_ui_sprite(pos, sprite_size, ID_DIGIT_5_UI, data);
	else if (num == 6)
		print_ui_sprite(pos, sprite_size, ID_DIGIT_6_UI, data);
	else if (num == 7)
		print_ui_sprite(pos, sprite_size, ID_DIGIT_7_UI, data);
	else if (num == 8)
		print_ui_sprite(pos, sprite_size, ID_DIGIT_8_UI, data);
	else if (num == 9)
		print_ui_sprite(pos, sprite_size, ID_DIGIT_9_UI, data);
}

void	print_num_sprite(int pos[2], int sprite_size, int num, t_data *data)
{
	if (num > 9)
	{
		print_num_sprite(pos, sprite_size, num / 10, data);
		num = num % 10;
	}
	select_digit_txt(pos, sprite_size, num, data);
	pos[X] -= (data->minimap_data->size[X] / 10) / 2;
}

void	print_ui_score(int pos[2], int sprite_size, t_data *data)
{
	int	digits;
	int	score;

	score = data->player->score;
	digits = 1;
	while (score / 10 > 0)
	{
		digits++;
		score = score / 10;
	}
	print_ui_sprite(pos, sprite_size, ID_SCORE_UI, data);
	while (5 - digits != 0)
	{
		print_num_sprite(pos, sprite_size, 0, data);
		digits++;
	}
	print_num_sprite(pos, sprite_size, data->player->score, data);
	pos[X] += (data->minimap_data->size[X] / 10) * 2;
}

void	print_collectable_found(int pos[2], int sprite_size, t_data *data)
{
	print_ui_sprite(pos, sprite_size, ID_CHEST_UI, data);
	print_num_sprite(pos, sprite_size, data->map_data->chest_found, data);
	print_ui_sprite(pos, sprite_size, ID_BAR_UI, data);
	pos[X] -= (data->minimap_data->size[X] / 10) / 2;
	print_num_sprite(pos, sprite_size, data->map_data->chest_qt, data);
	pos[X] += (data->minimap_data->size[X] / 10) * 2;
	print_ui_sprite(pos, sprite_size, ID_COIN_UI, data);
	print_num_sprite(pos, sprite_size, data->map_data->coin_found, data);
	print_ui_sprite(pos, sprite_size, ID_BAR_UI, data);
	pos[X] -= (data->minimap_data->size[X] / 10) / 2;
	print_num_sprite(pos, sprite_size, data->map_data->coin_qt, data);
	pos[X] += (data->minimap_data->size[X] / 10) * 2;
}

void	render_ui(t_data *data)
{
	int	pos[2];
	int	sprite_size;

	sprite_size = WIDTH / 50;
	pos[X] = WIDTH * 0.02;
	pos[Y] = (HEIGHT * UI_SIZE) / 2 - (sprite_size / 2);
	if (pos[Y] < 0)
		pos[Y] = HEIGHT * 0.01;
	print_ui_sprite(pos, sprite_size, ID_LEVEL_UI, data);
	print_num_sprite(pos, sprite_size, data->player->level + 1, data);
	pos[X] += (data->minimap_data->size[X] / 10) * 13;
	print_collectable_found(pos, sprite_size, data);
	if (data->map_data->key_qt == 1 && data->map_data->key_found)
		print_ui_sprite(pos, sprite_size, ID_KEY_UI, data);
	else if (data->map_data->key_qt == 1 && !data->map_data->key_found)
		print_ui_sprite(pos, sprite_size, ID_KEY_SHADOW_UI, data);
	else
		pos[X] = pos[X] + sprite_size * 2;
	pos[X] += (data->minimap_data->size[X] / 10) * 15;
	print_ui_score(pos, sprite_size, data);
}
