/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:34:30 by tjo               #+#    #+#             */
/*   Updated: 2023/01/20 06:42:27 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_raycasting_header.h"

static double	myabs(double a)
{
	if (a < 0)
		return (-a);
	return (a);
}

static int	clear_buffer(t_mlx *mlx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < WINDOW_H)
	{
		j = -1;
		while (++j < WINDOW_W)
			mlx->buffer[i * WINDOW_W + j] = 0;
	}
	return (0);
}

int	draw_screen(t_map *map, t_mlx *mlx)
{
	int		i;
	int		j;
	t_rc	rc;

	i = -1;

	clear_buffer(mlx);
	while (++i < WINDOW_W)
	{
		rc.x = map->player_x;
		rc.y = map->player_y;
		rc.camera_x = 2 * i / (double)WINDOW_W - 1; // get raydir
		rc.ray_x = map->dir_x + PLAIN_X * rc.camera_x;
		rc.ray_y = map->dir_y + PLAIN_Y * rc.camera_x;

		rc.delta_dist_x = myabs(1 / rc.ray_x); // get delta dist
		rc.delta_dist_y = myabs(1 / rc.ray_y);
		
		if (rc.ray_x < 0) // get step
		{
			rc.step_x = -1;
			rc.side_dist_x = (map->player_x - rc.x) * rc.delta_dist_x;
		}
		else
		{
			rc.step_x = 1;
			rc.side_dist_x = (rc.x + 1. - map->player_x) * rc.delta_dist_x;
		}
		if (rc.ray_y < 0)
		{
			rc.step_y = -1;
			rc.side_dist_y = (map->player_y - rc.y) * rc.delta_dist_y;
		}
		else
		{
			rc.step_y = 1;
			rc.side_dist_y = (rc.y + 1. - map->player_y) * rc.delta_dist_y;
		}
		
		// dda
		rc.hit = 0;
		while (!rc.hit)
		{
			if (rc.side_dist_x < rc.side_dist_y)
			{
				rc.side_dist_x += rc.delta_dist_x;
				rc.x += rc.step_x;
				rc.side = 0;
			}
			else
			{
				rc.side_dist_y += rc.delta_dist_y;
				rc.y += rc.step_y;
				rc.side = 1;
			}
			if (map->map[rc.x][rc.y])
				rc.hit = 1;
		}

		// remove fisheye effect
		if (rc.side)
			rc.wall_d = (rc.y - map->player_y + (1 - rc.step_y) / 2) / rc.ray_y;
		else
			rc.wall_d = (rc.x - map->player_x + (1 - rc.step_x) / 2) / rc.ray_x;
			
		// get height
		rc.line_h = WINDOW_H / rc.wall_d;
		rc.draw_s = ft_max(0, -rc.line_h / 2 + WINDOW_H / 2);
		rc.draw_e = ft_min(WINDOW_H - 1, rc.line_h / 2 + WINDOW_H / 2);
		
		// get where exactly the wall was hit
		if (rc.side)
			rc.wall_x = rc.x + rc.wall_d * rc.ray_x;
		else
			rc.wall_x = rc.y + rc.wall_d * rc.ray_y;
		rc.wall_x -= floor(rc.wall_x);
		
		rc.tex_x = rc.wall_x * mlx->img_w;
		if ((!rc.side && rc.ray_x > 0) || (rc.side && rc.ray_y < 0))
			rc.tex_x = mlx->img_w - rc.tex_x - 1;

		// get texture and draw
		rc.tex_id = map->map[rc.x][rc.y] - 1;
		
		rc.tex_step = 1. * mlx->img_h / rc.line_h;
		rc.tex_pos = (rc.draw_s - (WINDOW_H + rc.line_h) / 2) * rc.tex_step;

		j = rc.draw_s - 1;
		while (++j < rc.draw_e)
		{
			rc.tex_y = (int)rc.tex_pos & (mlx->img_h - 1);
			rc.color = mlx->tex[rc.tex_id][mlx->img_h * rc.tex_y + rc.tex_x];
			if (rc.side)
				rc.color = (rc.color >> 1) & 8355711;
			rc.tex_pos += rc.tex_step;
			mlx->buffer[j * mlx->size_line / 4 + i] = rc.color;
		}
	}
	mlx_put_image_to_window(mlx->m, mlx->w, mlx->img[ASSET_CNT], 0, 0);
	return (0);
}

int	main_loop(t_param *t)
{
	draw_screen(t->map, t->mlx);
	return (0);
}