/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_header.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:34:48 by tjo               #+#    #+#             */
/*   Updated: 2023/01/20 14:50:42 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RAYCASTING_HEADER_H
# define FT_RAYCASTING_HEADER_H

# include<math.h>
# include<stdlib.h>
# include"../mlx/mlx.h"
# include"../ft_mylibft/libft.h"

# define WINDOW_W 1440
# define WINDOW_H 900

typedef struct s_rc
{
	double	camera_x;
	double	ray_x;
	double	ray_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	wall_d;
	double	wall_x;
	double	tex_step;
	double	tex_pos;
	int		tex_x;
	int		tex_y;
	int		x;
	int		y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_h;
	int		draw_s;
	int		draw_e;
	int		tex_id;
	int		color;
}t_rc;

typedef struct s_map
{
	int		width;
	int		height;
	double	player_x;
	double	player_y;
	double	plain_x;
	double	plain_y;
	double	dir_x;
	double	dir_y;
	int		**map;
}t_map;

# define ASSET_CNT 10

typedef struct s_mlx
{
	void	*m;
	void	*w;
	void	*img[ASSET_CNT + 2];
	int		*data[ASSET_CNT];
	int		*buffer[2];
	int		img_w;
	int		img_h;
	int		bpp;
	int		size_line;
	int		endian;
	int		*tex[ASSET_CNT];
}t_mlx;

typedef struct s_param
{
	t_map	*map;
	t_mlx	*mlx;
}t_param;

/* ft_raycasting.c */
int		looooop(t_param *t);
int		draw_screen(t_map *map, t_mlx *mlx, int img);

/* ft_raycasting_utils.c */
double	myabs(double a);

/* ft_raycasting_calc.c */
void	get_step(t_rc *rc, t_map *map);
void	dda(t_rc *rc, t_map *map);
void	find_wall_hit(t_rc *rc, t_map *map, t_mlx *mlx);
void	get_texture_and_draw(t_rc *rc, t_mlx *mlx, int i, int img);

#endif