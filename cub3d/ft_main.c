/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:29:09 by tjo               #+#    #+#             */
/*   Updated: 2023/01/31 17:12:14 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_header.h"

int	error_handling(const char *s)
{
	ft_printf("%s\n", s);
	exit(1);
}

static int	get_wall_texture(t_mlx *mlx, t_map *map)
{
	int	i;

	(void)map;
	i = -1;
	while (++i < 4)
	{
		mlx->img[i + ASSET_CNT + 2] = mlx_xpm_file_to_image(mlx->m, \
		map->info[i], &mlx->img_w, &mlx->img_h);
		if (!mlx->img[i + ASSET_CNT + 2])
			return (error_handling("Wall texture file error"));
		mlx->data[i + ASSET_CNT + 2] = (int *)mlx_get_data_addr(\
			mlx->img[i + ASSET_CNT + 2], \
			&mlx->bpp, &mlx->size_line, &mlx->endian);
		mlx->wall[i] = malloc(sizeof(int) * (mlx->img_h * mlx->img_w));
		if (!mlx->wall[i])
			return (error_handling("Wall texture malloc error"));
		ft_memcpy(mlx->wall[i], mlx->data[i + ASSET_CNT + 2], \
			mlx->img_h * mlx->img_w * 4);
	}
	return (0);
}

static int	get_assets(t_mlx *mlx, t_map *map)
{
	int		i;
	char	*assets[ASSET_CNT];

	assets[0] = "assets/door.xpm";
	assets[1] = "assets/img1.xpm";
	assets[2] = "assets/img2.xpm";
	assets[3] = "assets/img3.xpm";
	i = -1;
	get_wall_texture(mlx, map);
	while (++i < ASSET_CNT)
	{
		mlx->img[i] = mlx_xpm_file_to_image(mlx->m, \
		assets[i], &mlx->img_w, &mlx->img_h);
		if (!mlx->img[i])
			return (error_handling("Asset file error"));
		mlx->data[i] = (int *)mlx_get_data_addr(mlx->img[i], \
			&mlx->bpp, &mlx->size_line, &mlx->endian);
		mlx->tex[i] = malloc(sizeof(int) * (mlx->img_h * mlx->img_w));
		if (!mlx->tex[i])
			return (error_handling("Asset malloc error"));
		ft_memcpy(mlx->tex[i], mlx->data[i], mlx->img_h * mlx->img_w * 4);
	}
	return (0);
}

static void	__mlx_init(t_mlx *mlx, t_map *map)
{
	t_param	param;

	param = (t_param){.map = map, .mlx = mlx};
	mlx->m = mlx_init();
	mlx->w = mlx_new_window(mlx->m, WINDOW_W, WINDOW_H, "cub3d");
	get_assets(mlx, map);
	mlx->img[ASSET_CNT + 0] = mlx_new_image(mlx->m, WINDOW_W, WINDOW_H);
	mlx->img[ASSET_CNT + 1] = mlx_new_image(mlx->m, WINDOW_W, WINDOW_H);
	mlx->buffer[0] = (int *)mlx_get_data_addr(mlx->img[ASSET_CNT + 0], \
		&mlx->bpp, &mlx->size_line, &mlx->endian);
	mlx->buffer[1] = (int *)mlx_get_data_addr(mlx->img[ASSET_CNT + 1], \
		&mlx->bpp, &mlx->size_line, &mlx->endian);
	if (!mlx->buffer[0] || !mlx->buffer[1])
		error_handling("Image buffer error");
	mlx->time = 0;
	mlx_mouse_hide();
	mlx_mouse_move(mlx->w, WINDOW_W / 2, WINDOW_H / 2);
	mlx_hook(mlx->w, 2, 0, &key_hook, &param);
	mlx_hook(mlx->w, 17, 0, &close_game, &param);
	mlx_loop_hook(mlx->m, &looooop, &param);
	mlx_loop(mlx->m);
}

int	main(int ac, char **av)
{
	int		error;
	t_map	map;
	t_mlx	mlx;

	(void)ac, (void)av;
	if (ac != 2)
	{	
		ft_printf("FEW ARG or MANY ARG\n");
		return (1);
	}
	error = init_map(&map, av[1]);
	if (error)
		map_error_handling(&map, error);
	__mlx_init(&mlx, &map);
}
