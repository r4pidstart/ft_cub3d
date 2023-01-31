/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:37:25 by joowpark          #+#    #+#             */
/*   Updated: 2023/02/01 04:34:48 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse.h"

void	map_error_handling(struct s_map *m, int error)
{
	if (!error)
		return ;
	if (error == ERROR_FD)
		printf("FILE NAME OR FD HAS ERROR\n");
	else if (error == ERROR_CUB)
		printf("\'.CUB\' FILE HAS ERROR\n");
	free_all_map(m);
	exit(1);
}

void	initial_player_dir(struct s_map *m)
{
	m->plain_x = 0;
	m->plain_y = 0.67;
	m->dir_x = -1;
	m->dir_y = 0;
	if (m->dir_ch == 'S')
		change_dir(K_RIGHT, m, M_PI_2);
	else if (m->dir_ch == 'W')
		change_dir(K_RIGHT, m, M_PI_2 * 2);
	else if (m->dir_ch == 'N')
		change_dir(K_RIGHT, m, M_PI_2 * 3);
}

void	mirror(struct s_map *m)
{
	int	i;
	int	j;
	int	t;

	i = -1;
	while (++i < m->height)
	{
		j = -1;
		while (++j < m->width / 2)
		{
			t = m->map[i][j];
			m->map[i][j] = m->map[i][m->width - j - 1];
			m->map[i][m->width - j - 1] = t;
		}
	}
	m->player_x = m->width - m->player_x;
}

int	init_map(struct s_map *m, char *file_name)
{
	int		fd;
	int		error;

	error = 0;
	ft_bzero(m, sizeof(*m));
	fd = get_fd(file_name);
	if (fd == -1)
		return (ERROR_FD);
	if (get_info(fd, m) || get_imap(fd, m))
		error = ERROR_CUB;
	if (!error && set_map(m))
		error = ERROR_CUB;
	close(fd);
	initial_player_dir(m);
	mirror(m);
	return (error);
}
