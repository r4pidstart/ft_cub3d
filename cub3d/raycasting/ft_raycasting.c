/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:34:30 by tjo               #+#    #+#             */
/*   Updated: 2023/01/20 14:30:46 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_raycasting_header.h"

int	draw_screen(t_map *map, t_mlx *mlx, int img)
{
	int		i;
	t_rc	rc;

	i = -1;
	while (++i < WINDOW_W)
	{
		rc.camera_x = 2 * i / (double)WINDOW_W - 1;
		rc.x = map->player_x;
		rc.y = map->player_y;
		get_step(&rc, map);
		dda(&rc, map);
		find_wall_hit(&rc, map, mlx);
		get_texture_and_draw(&rc, mlx, i, img);
	}
	ft_memset(mlx->buffer[img ^ 1], 0, 4 * WINDOW_H * WINDOW_W);
	return (0);
}

int	main_loop(t_param *t)
{
	static int	img;

	img ^= 1;
	
	// rotation
	const double rotSpeed=0.005;

	double oldDirX = t->map->dir_x;
	t->map->dir_x = t->map->dir_x * cos(-rotSpeed) - t->map->dir_y * sin(-rotSpeed);
	t->map->dir_y = oldDirX * sin(-rotSpeed) + t->map->dir_y * cos(-rotSpeed);
	double oldPlaneX = t->map->plain_x;
	t->map->plain_x = t->map->plain_x * cos(-rotSpeed) - t->map->plain_y * sin(-rotSpeed);
	t->map->plain_y = oldPlaneX * sin(-rotSpeed) + t->map->plain_y * cos(-rotSpeed);

	draw_screen(t->map, t->mlx, img);
	mlx_put_image_to_window(t->mlx->m, t->mlx->w, \
		t->mlx->img[img + ASSET_CNT], 0, 0);
	return (0);
}