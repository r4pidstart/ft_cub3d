/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 04:20:59 by tjo               #+#    #+#             */
/*   Updated: 2023/01/31 17:14:56 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_header.h"

int	check_collision(t_map *m, double next_x, double next_y)
{
	const double	safe_d = 0.2;

	if ((m->map[(int)(next_y + safe_d)][(int)(next_x + safe_d)] &&
		(m->map[(int)(next_y + safe_d)][(int)(next_x + safe_d)] != 2 \
			|| !m->is_door_closed)) ||
		(m->map[(int)(next_y - safe_d)][(int)(next_x + safe_d)] &&
		(m->map[(int)(next_y - safe_d)][(int)(next_x + safe_d)] != 2 \
			|| !m->is_door_closed)) ||
		(m->map[(int)(next_y + safe_d)][(int)(next_x - safe_d)] &&
		(m->map[(int)(next_y + safe_d)][(int)(next_x - safe_d)] != 2 \
			|| !m->is_door_closed)) ||
		(m->map[(int)(next_y - safe_d)][(int)(next_x - safe_d)] &&
		(m->map[(int)(next_y - safe_d)][(int)(next_x - safe_d)] != 2 \
			|| !m->is_door_closed)))
		return (1);
	m->player_x = next_x;
	m->player_y = next_y;
	return (0);
}

int	move_player(int key, t_param *t)
{
	const double	move_speed = 0.07;
	double			next_x;
	double			next_y;

	if (key == K_W)
	{
		next_x = t->map->player_x + t->map->dir_x * move_speed;
		next_y = t->map->player_y + t->map->dir_y * move_speed;
	}
	else if (key == K_A)
	{
		next_x = t->map->player_x - t->map->dir_y * move_speed;
		next_y = t->map->player_y + t->map->dir_x * move_speed;
	}
	else if (key == K_S)
	{
		next_x = t->map->player_x - t->map->dir_x * move_speed;
		next_y = t->map->player_y - t->map->dir_y * move_speed;
	}
	else
	{
		next_x = t->map->player_x + t->map->dir_y * move_speed;
		next_y = t->map->player_y - t->map->dir_x * move_speed;
	}
	return (check_collision(t->map, next_x, next_y));
}

int	close_game(t_param *t)
{
	free_all_map(t->map);
	exit(0);
}

int	mouse_status(int toggle)
{
	static int	mouse;

	if (toggle)
		mouse ^= 1;
	return (mouse ^ toggle);
}

int	key_hook(int key, t_param *t)
{
	if (key == K_LEFT || key == K_RIGHT)
		change_dir(key, t->map, 0.07);
	else if (key == K_W || key == K_A || key == K_S || key == K_D)
		move_player(key, t);
	else if (key == K_E)
	{
		t->map->is_door_closed ^= 1;
		if (check_collision(t->map, t->map->player_x, t->map->player_y))
			t->map->is_door_closed ^= 1;
	}
	else if (key == K_Q)
	{
		if (mouse_status(1))
			mlx_mouse_hide();
		else
			mlx_mouse_show();
	}
	else if (key == K_ESC)
		close_game(t);
	mlx_clear_window(t->mlx->m, t->mlx->w);
	looooop(t);
	return (0);
}
