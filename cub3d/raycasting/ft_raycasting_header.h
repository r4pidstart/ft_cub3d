/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_header.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:34:48 by tjo               #+#    #+#             */
/*   Updated: 2023/01/20 06:42:43 by tjo              ###   ########.fr       */
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

# define PLAIN_X 0
# define PLAIN_Y 0.67

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
	double	time;
	double	old_time;
}t_rc;

typedef struct s_map
{
	int		width;
	int		height;
	double	player_x;
	double	player_y;
	double	dir_x;
	double	dir_y;
	int		**map;
}t_map;

# define ASSET_CNT 10

typedef struct s_mlx
{
	void	*m;
	void	*w;
	void	*img[ASSET_CNT + 1];
	int		*data[ASSET_CNT];
	int		*buffer;
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

int	main_loop(t_param *t);
int	draw_screen(t_map *map, t_mlx *mlx);

#endif