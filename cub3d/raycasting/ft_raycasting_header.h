/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_header.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:34:48 by tjo               #+#    #+#             */
/*   Updated: 2023/01/20 06:19:34 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RAYCASTING_HEADER_H
# define FT_RAYCASTING_HEADER_H

# include<math.h>
# include<stdlib.h>
# include"../mlx/mlx.h"
# include"../ft_mylibft/libft.h"

# define WINDOW_W 1920
# define WINDOW_H 1080

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
	int		img_w;
	int		img_h;
	int		bpp;
	int		size_line;
	int		endian;
	int		*tex[ASSET_CNT];
	int		*buffer;
}t_mlx;

typedef struct s_param
{
	t_map	*map;
	t_mlx	*mlx;
}t_param;

int	main_loop(t_param *t);
int	draw_screen(t_map *map, t_mlx *mlx);

#endif