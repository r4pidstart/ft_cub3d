/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:46:38 by tjo               #+#    #+#             */
/*   Updated: 2023/01/20 15:06:41 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_raycasting_header.h"

double	myabs(double a)
{
	if (a < 0)
		return (-a);
	return (a);
}

int	change_dir(int key, t_map *map, double rs)
{
	double			old_dir_x;
	double			old_plane_x;

	if (key == K_RIGHT) // right
	{
		old_dir_x = map->dir_x;
		map->dir_x = map->dir_x * cos(-rs) - map->dir_y * sin(-rs);
		map->dir_y = old_dir_x * sin(-rs) + map->dir_y * cos(-rs);
		old_plane_x = map->plain_x;
		map->plain_x = map->plain_x * cos(-rs) - map->plain_y * sin(-rs);
		map->plain_y = old_plane_x * sin(-rs) + map->plain_y * cos(-rs);
	}
	else if(key == K_LEFT) // left
	{
		old_dir_x = map->dir_x;
		map->dir_x = map->dir_x * cos(rs) - map->dir_y * sin(rs);
		map->dir_y = old_dir_x * sin(rs) + map->dir_y * cos(rs);
		old_plane_x = map->plain_x;
		map->plain_x = map->plain_x * cos(rs) - map->plain_y * sin(rs);
		map->plain_y = old_plane_x * sin(rs) + map->plain_y * cos(rs);
	}
	return (0);
}
