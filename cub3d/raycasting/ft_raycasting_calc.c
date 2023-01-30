/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_calc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:56:42 by tjo               #+#    #+#             */
/*   Updated: 2023/01/31 04:13:31 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_raycasting_header.h"

void	get_step(t_rc *rc, t_map *map)
{
	rc->ray_x = map->dir_x + map->plain_x * rc->camera_x;
	rc->ray_y = map->dir_y + map->plain_y * rc->camera_x;
	rc->delta_dist_x = myabs(1 / rc->ray_x);
	rc->delta_dist_y = myabs(1 / rc->ray_y);
	if (rc->ray_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (map->player_x - rc->x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->x + 1. - map->player_x) * rc->delta_dist_x;
	}
	if (rc->ray_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (map->player_y - rc->y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->y + 1. - map->player_y) * rc->delta_dist_y;
	}
}

void	dda(t_rc *rc, t_map *map)
{
	rc->hit = 0;
	while (!rc->hit)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->y += rc->step_y;
			rc->side = 1;
		}
		if (map->map[rc->y][rc->x] -1 == DOOR)
			rc->hit = !map->is_door_closed;
		else if (map->map[rc->y][rc->x])
			rc->hit = 1;
	}
	if (rc->side)
		rc->wall_d = (rc->y - map->player_y + (1 - rc->step_y) / 2) / rc->ray_y;
	else
		rc->wall_d = (rc->x - map->player_x + (1 - rc->step_x) / 2) / rc->ray_x;
}

int	get_wall_dir(t_rc *rc, t_map *map)
{
	if (!rc->side && map->player_x - rc->x > 0)
		return (WE + ASSET_CNT);
	else if (!rc->side)
		return (EA + ASSET_CNT);
	else if (rc->side && map->player_y - rc->y > 0)
		return (SO + ASSET_CNT);
	else
		return (NO + ASSET_CNT);
}

void	find_wall_hit(t_rc *rc, t_map *map, t_mlx *mlx)
{
	rc->line_h = WINDOW_H / rc->wall_d;
	rc->draw_s = ft_max(0, -rc->line_h / 2 + WINDOW_H / 2);
	rc->draw_e = ft_min(WINDOW_H - 1, rc->line_h / 2 + WINDOW_H / 2);
	if (rc->side)
		rc->wall_x = map->player_x + rc->wall_d * rc->ray_x;
	else
		rc->wall_x = map->player_y + rc->wall_d * rc->ray_y;
	rc->wall_x -= floor(rc->wall_x);
	rc->tex_x = rc->wall_x * mlx->img_w;
	if ((!rc->side && rc->ray_x > 0) || (rc->side && rc->ray_y < 0))
		rc->tex_x = mlx->img_w - rc->tex_x - 1;
	if (map->map[rc->y][rc->x] - 1 == DOOR)
		rc->tex_id = 0;
	else if (map->map[rc->y][rc->x] - 1 == ANIMATED)
		rc->tex_id = 1 + (mlx->time / 10);
	else
		rc->tex_id = get_wall_dir(rc, map);
}

void	get_texture_and_draw(t_rc *rc, t_mlx *mlx, int i, int img)
{
	int		j;

	rc->tex_step = 1. * mlx->img_h / rc->line_h;
	rc->tex_pos = (rc->draw_s - (WINDOW_H + rc->line_h) / 2) * rc->tex_step;
	j = rc->draw_s - 1;
	while (++j < rc->draw_e)
	{
		rc->tex_y = (int)rc->tex_pos & (mlx->img_h - 1);
		if (rc->tex_id >= ASSET_CNT)
			rc->color = \
		mlx->wall[rc->tex_id - ASSET_CNT][mlx->img_h * rc->tex_y + rc->tex_x];
		else
			rc->color = \
		mlx->tex[rc->tex_id][mlx->img_h * rc->tex_y + rc->tex_x];
		if (rc->side)
			rc->color = (rc->color >> 1) & 8355711;
		rc->tex_pos += rc->tex_step;
		mlx->buffer[img][j * mlx->size_line / 4 + i] = rc->color;
	}
}
