/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:58:02 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/18 20:58:29 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# define COIN_TXT_PATH "./assets/sprites/coin.xpm"
# define KEY_TXT_PATH "./assets/sprites/key.xpm"
# define CHEST_TXT_PATH "./assets/sprites/chest.xpm"

typedef enum e_sprite_type
{
	COLLECTABLE,
	DECORATION,
	PORTAL,
	ENEMY
}	t_sprite_type;

typedef enum e_collectable_type
{
	T_CHEST,
	T_COIN,
	T_KEY
}	t_collectable_type;

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

#endif
