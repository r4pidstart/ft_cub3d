/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:34:30 by tjo               #+#    #+#             */
/*   Updated: 2023/01/30 05:26:09 by tjo              ###   ########.fr       */
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
	fill_background(mlx, map, img);
	return (0);
}

int	draw_minimap(t_map *map, t_mlx *mlx, int *img)
{
	const int	offset = 50;
	const int	multiplier = 12;
	int			i;
	int			j;

	i = offset - 1;
	while (++i < map->height * multiplier)
	{
		j = offset - 1;
		while (++j < map->width * multiplier)
		{
			if ((int)map->player_y == i / multiplier \
				&& (int)map->player_x == j / multiplier)
				img[i * mlx->size_line / 4 + j] = 0xAA0000;
			else if (map->map[i / multiplier][j / multiplier])
				img[i * mlx->size_line / 4 + j] = 0x888888;
			else
				img[i * mlx->size_line / 4 + j] = 0xAAAAAA;
		}
	}
	return (0);
}

int	looooop(t_param *t)
{
	static int	img;
	static int	px = WINDOW_W / 2;
	static int	x = -1;
	static int	y = -1;

	mlx_mouse_get_pos(t->mlx->w, &x, &y);
	if (px > x)
		change_dir(K_LEFT, t->map, (px - x) * 0.0008);
	else if (px < x)
		change_dir(K_RIGHT, t->map, (x - px) * 0.0008);
	if (!(0 <= x && x <= WINDOW_W))
	{
		mlx_mouse_move(t->mlx->w, WINDOW_W / 2, WINDOW_H / 2);
		x = WINDOW_W / 2;
	}
	px = x;
	img ^= 1;
	draw_screen(t->map, t->mlx, img);
	draw_minimap(t->map, t->mlx, t->mlx->buffer[img]);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, t->mlx->img[img + ASSET_CNT]);
	mlx_put_image_to_window(t->mlx->m, t->mlx->w, \
		t->mlx->img[img + ASSET_CNT], 0, 0);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, t->mlx->w);
	return (0);
}
