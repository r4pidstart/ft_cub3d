/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 04:20:59 by tjo               #+#    #+#             */
/*   Updated: 2023/01/30 04:22:47 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_header.h"

int	check_collision(t_param *t, double next_x, double next_y)
{
	const double	safe_dist = 0.2;

	if (t->map->map[(int)(next_x + safe_dist)][(int)(next_y + safe_dist)] \
		|| t->map->map[(int)(next_x - safe_dist)][(int)(next_y - safe_dist)] \
		|| t->map->map[(int)(next_x - safe_dist)][(int)(next_y + safe_dist)] \
		|| t->map->map[(int)(next_x + safe_dist)][(int)(next_y - safe_dist)])
		return (0);
	t->map->player_x = next_x;
	t->map->player_y = next_y;
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
		next_x = t->map->player_x - t->map->dir_x * move_speed;
		next_y = t->map->player_y + t->map->dir_y * move_speed;
	}
	else if (key == K_S)
	{
		next_x = t->map->player_x - t->map->dir_x * move_speed;
		next_y = t->map->player_y - t->map->dir_y * move_speed;
	}
	else
	{
		next_x = t->map->player_x + t->map->dir_x * move_speed;
		next_y = t->map->player_y - t->map->dir_y * move_speed;
	}
	return (check_collision(t, next_x, next_y));
}

int	close_game(void)
{
	exit(0);
}

int	key_hook(int key, t_param *t)
{
	if (key == K_LEFT || key == K_RIGHT)
		change_dir(key, t->map, 0.07);
	else if (key == K_W || key == K_A || key == K_S || key == K_D)
		move_player(key, t);
	else if (key == K_ESC)
		exit(0);
	mlx_clear_window(t->mlx->m, t->mlx->w);
	looooop(t);
	return (0);
}
