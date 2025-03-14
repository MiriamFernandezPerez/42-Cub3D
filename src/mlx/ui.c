/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 02:27:49 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/18 22:44:15 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../inc/ui.h"

void	add_ui_textures(t_data *data)
{
	add_texture_node(ID_CHEST_UI, ft_strdup(CHEST_UI_TXT_PATH), data);
	//add_texture_node(ID_CHEST_SHDW_UI, ft_strdup(CHEST_SHDW_UI_TXT_PATH), data);
	add_texture_node(ID_COIN_UI, ft_strdup(COIN_UI_TXT_PATH), data);
	add_texture_node(ID_KEY_UI, ft_strdup(KEY_UI_TXT_PATH), data);
	add_texture_node(ID_KEY_SHADOW_UI, ft_strdup(KEY_SHADOW_UI_TXT_PATH), data);
	add_texture_node(ID_DIGIT_0_UI, ft_strdup(UI_0_TXT_PATH), data);
	add_texture_node(ID_DIGIT_1_UI, ft_strdup(UI_1_TXT_PATH), data);
	add_texture_node(ID_DIGIT_2_UI, ft_strdup(UI_2_TXT_PATH), data);
	add_texture_node(ID_DIGIT_3_UI, ft_strdup(UI_3_TXT_PATH), data);
	add_texture_node(ID_DIGIT_4_UI, ft_strdup(UI_4_TXT_PATH), data);
	add_texture_node(ID_DIGIT_5_UI, ft_strdup(UI_5_TXT_PATH), data);
	add_texture_node(ID_DIGIT_6_UI, ft_strdup(UI_6_TXT_PATH), data);
	add_texture_node(ID_DIGIT_7_UI, ft_strdup(UI_7_TXT_PATH), data);
	add_texture_node(ID_DIGIT_8_UI, ft_strdup(UI_8_TXT_PATH), data);
	add_texture_node(ID_DIGIT_9_UI, ft_strdup(UI_9_TXT_PATH), data);
	add_texture_node(ID_BAR_UI, ft_strdup(UI_BAR_TXT_PATH), data);
}

int	get_ui_txt_color(int x, int y, int sprite_size, t_texture *texture)
{
	int			color;
	double		txt[2];

	color = 0x000000;
	if (!texture)
		return (color);
	txt[X] = x / (double)sprite_size * texture->width;
	txt[Y] = y / (double)sprite_size * texture->height;
	txt[X] = fmod(txt[X], texture->width);
	txt[Y] = fmod(txt[Y], texture->height);
	color = get_texture_pxl(texture, txt[X], txt[Y]);
	return (color);
}

void	print_ui_sprite(int pos[2], int txt_id, t_data *data)
{
	int			i[2];
	int			sprite_size;
	int			color;
	t_texture	*texture;

	sprite_size = WIDTH * 0.03;
	texture = get_texture(txt_id, data);
	i[Y] = pos[Y];
	while (i[Y] < pos[Y] + sprite_size)
	{
		i[X] = pos[X];
		while (i[X] < pos[X] + sprite_size)
		{
			color = get_ui_txt_color(i[X] - pos[X], i[Y] - pos[Y],
				sprite_size, texture);
			print_gui_pixel(i[X], i[Y], color, data->mlx_data);
			i[X]++;
		}
		i[Y]++;
	}
	pos[X] = pos[X] + sprite_size;
}

void	print_num_sprite(int pos[2], int num, t_data *data)
{
	if (num >= 9)
	{
		print_num_sprite(pos, num / 10, data);
		num = num % 10;
	}
	if (num == 0)
		print_ui_sprite(pos, ID_DIGIT_0_UI, data);
	else if (num == 1)
		print_ui_sprite(pos, ID_DIGIT_1_UI, data);
	else if (num == 2)
		print_ui_sprite(pos, ID_DIGIT_2_UI, data);
	else if (num == 3)
		print_ui_sprite(pos, ID_DIGIT_3_UI, data);
	else if (num == 4)
		print_ui_sprite(pos, ID_DIGIT_4_UI, data);
	else if (num == 5)
		print_ui_sprite(pos, ID_DIGIT_5_UI, data);
	else if (num == 6)
		print_ui_sprite(pos, ID_DIGIT_6_UI, data);
	else if (num == 7)
		print_ui_sprite(pos, ID_DIGIT_7_UI, data);
	else if (num == 8)
		print_ui_sprite(pos, ID_DIGIT_8_UI, data);
	else if (num == 9)
		print_ui_sprite(pos, ID_DIGIT_9_UI, data);	
	pos[X] -= (WIDTH * 0.03) / 3;
}

void	print_ui(t_data *data)
{
	int	pos[2];

	pos[X] = WIDTH * MINIMAP_MARGIN;
	pos[Y] = HEIGHT * MINIMAP_MARGIN;
	//TODO print chest found
	print_ui_sprite(pos, ID_CHEST_UI, data);
	print_num_sprite(pos, data->map_data->chest_found, data); //CHESTS FOUND
	print_ui_sprite(pos, ID_BAR_UI, data); //TODO BAR
	pos[X] -= (WIDTH * 0.03) / 3;
	print_num_sprite(pos, data->map_data->chest_qt, data); //TOTAL CHEST
	pos[X] += WIDTH * 0.03;
	//TODO Print coin found
	print_ui_sprite(pos, ID_COIN_UI, data);
	print_num_sprite(pos, data->map_data->coin_found, data); //CHESTS FOUND
	print_ui_sprite(pos, ID_BAR_UI, data); //TODO BAR
	pos[X] -= (WIDTH * 0.03) / 3;
	print_num_sprite(pos, data->map_data->coin_qt, data); //TOTAL CHEST
	pos[X] += WIDTH * 0.03 * 2;
	//TODO print KEY
	if (data->map_data->key_qt == 1 && data->map_data->key_found)
		print_ui_sprite(pos, ID_KEY_UI, data);
	else if (data->map_data->key_qt == 1 && !data->map_data->key_found)
		print_ui_sprite(pos, ID_KEY_SHADOW_UI, data);
}
