/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:29:09 by tjo               #+#    #+#             */
/*   Updated: 2023/01/20 15:50:53 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_header.h"


int	get_assets(t_mlx *mlx)
{
	int	i;

	i = -1;
	// if (!mlx->tex)
	// 	return (error_handling());
	char	*assets[ASSET_CNT] =
	{
		"assets/chest.xpm",
		"assets/wall.xpm",
		"assets/sans.xpm",
		"assets/wall.xpm",
		"assets/wall.xpm",
		"assets/wall.xpm",
		"assets/wall.xpm",
		"assets/wall.xpm",
		"assets/wall.xpm",
		"assets/wall.xpm"
	};
	while (++i < ASSET_CNT)
	{
		mlx->img[i] = mlx_xpm_file_to_image(mlx->m, \
		assets[i], &mlx->img_w, &mlx->img_h);
		mlx->data[i] = (int *)mlx_get_data_addr(mlx->img[i], \
			&mlx->bpp, &mlx->size_line, &mlx->endian);
		mlx->tex[i] = malloc(sizeof(int) * (mlx->img_h * mlx->img_w));
		// if (!mlx->tex[i])
		// 	return (error_handling());
		ft_memcpy(mlx->tex[i], mlx->data[i], 4 *  mlx->img_h * mlx->img_w);
	}
	return (0);
}

int worldMap[24][24]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// TODO: wall collision
int	move_player(int key, t_param *t)
{
	const double	move_speed = 0.07;

	if (key == K_W)
	{
		t->map->player_x += t->map->dir_x * move_speed;
		t->map->player_y += t->map->dir_y * move_speed;
	}
	else if (key == K_A)
	{
		t->map->player_x -= t->map->dir_y * move_speed;
		t->map->player_y += t->map->dir_x * move_speed;
	}
	else if (key == K_S)
	{
		t->map->player_x -= t->map->dir_x * move_speed;
		t->map->player_y -= t->map->dir_y * move_speed;
	}
	else if (key == K_D)
	{
		t->map->player_x += t->map->dir_y * move_speed;
		t->map->player_y -= t->map->dir_x * move_speed;
	}
	return (0);
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

int	main(void)
{
	t_param	param;
	t_map	map;
	t_mlx	mlx;

	param = (t_param){.map = &map, .mlx = &mlx};
	map = (t_map){.width = 24, .height = 24, .player_x = 21, .player_y = 12, \
		.dir_x = -1, .dir_y = 0, .plain_x = 0, .plain_y = 0.67};
		
	map.map = (int **)malloc(sizeof(int *) * 24);
	for(int i=0; i<24; i++)
		map.map[i] = (int *)malloc(sizeof(int) * 24);
	
	for(int i=0; i<24; i++)
		for(int j=0; j<24; j++)
			map.map[i][j]=worldMap[i][j];
			
	mlx.m = mlx_init();
	mlx.w = mlx_new_window(mlx.m, WINDOW_W, WINDOW_H, "cub3d");

	get_assets(&mlx);
	mlx.img[ASSET_CNT + 0] = mlx_new_image(mlx.m, WINDOW_W, WINDOW_H);
	mlx.img[ASSET_CNT + 1] = mlx_new_image(mlx.m, WINDOW_W, WINDOW_H);
	mlx.buffer[0] = (int *)mlx_get_data_addr(mlx.img[ASSET_CNT + 0], \
		&mlx.bpp, &mlx.size_line, &mlx.endian);
	mlx.buffer[1] = (int *)mlx_get_data_addr(mlx.img[ASSET_CNT + 1], \
		&mlx.bpp, &mlx.size_line, &mlx.endian);
	// if (!mlx.buffer[0] || !mlx.buffer[1])
	// 	error_handling();

	mlx_mouse_hide();
	mlx_mouse_move(mlx.w, WINDOW_W / 2, WINDOW_H / 2);
	mlx_hook(mlx.w, 2, 0, &key_hook, &param);
	mlx_loop_hook(mlx.m, &looooop, &param);
	mlx_loop(mlx.m);
}