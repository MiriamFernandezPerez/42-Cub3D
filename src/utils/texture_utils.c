/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 00:13:32 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/03 00:31:17 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	clear_txt_list(t_texture **txt_list)
{
	if (!(*txt_list) || !txt_list)
		return ;
	clear_txt_list(&(*txt_list)->next);
	if ((*txt_list)->path)
		free((*txt_list)->path);
	free(*txt_list);
	*txt_list = NULL;
}


t_texture	*last_node(t_texture *txt_list)
{
	if (!txt_list)
		return (NULL);
	while (txt_list->next)
	{
		txt_list = txt_list->next;
	}
	return (txt_list);
}

void	add_node_back(t_texture **txt_list, t_texture *new)
{
	t_texture	*last;

	if (!txt_list)
		txt_list = &new;
	else
	{
		if (!*txt_list)
			*txt_list = new;
		else
		{
			last = last_node(*txt_list);
			last->next = new;
		}
	}
}

t_texture	*new_texture_node(char id_texture, char *path)
{
	t_texture	*new;

	new = (t_texture *)malloc(sizeof(t_texture));
	if (!new)
		return (NULL);
	new->id_txt = id_texture;
	new->path = path;
	new->next = NULL;
	return (new);
}


void	add_texture_node(char id_texture, char *path, t_data *data)
{
	t_texture *new;

	new = new_texture_node(id_texture, path);
	malloc_protection(new, data);
	add_node_back(&data->map_data->txt_list, new);
}
