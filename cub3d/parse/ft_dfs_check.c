/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dfs_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:22:47 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/30 04:32:28 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse.h"

void	dfs(struct s_map *m, int prv[2], char **map)
{
	const int	dir[2][4] = {{0, 0, 1, -1}, {1, -1, 0, 0}};
	int			idx;
	int			new[2];

	idx = 0;
	while (idx < 4)
	{
		new[0] = prv[0] + dir[0][idx];
		new[1] = prv[1] + dir[1][idx];
		if (0 <= new[0] && new[0] < m->height && 0 <= new[1]
			&& new[1] < (int)ft_strlen(map[new[0]])
			&& map[new[0]][new[1]] == '1')
		{
			map[new[0]][new[1]] = m->dir_ch;
			dfs(m, new, map);
		}
		idx ++;
	}
}

int	is_empty_space(struct s_map *m, int x, int y)
{
	const int	dir[2][4] = {{0, 0, 1, -1}, {1, -1, 0, 0}};
	char		**map;
	int			check;
	int			idx;

	(void)check;
	check = 0;
	idx = 0;
	map = m->cmap;
	if (x == 0 || y == 0 || x == m->height - 1
		|| y == (int)ft_strlen(map[x]) - 1)
		return (0);
	while (idx < 4)
	{
		if (ft_isspace(map[x + dir[0][idx]][y + dir[1][idx]]))
			return (0);
		idx ++;
	}
	return (1);
}

static char	get_box(char **map, int x, int y, int idx)
{
	const int	dir[2][4] = {{0, 0, 1, -1}, {1, -1, 0, 0}};
	char		tmp;

	if (y + dir[1][idx] >= (int)ft_strlen(map[x + dir[0][idx]]))
		tmp = ' ';
	else
		tmp = map[x + dir[0][idx]][y + dir[1][idx]];
	return (tmp);
}

static int	is_surround_empty(struct s_map *m, char **map, int x, int y)
{
	char	tmp;
	int		idx;
	int		nr_empty;
	int		nr_dir_ch;

	(void)nr_empty, (void)nr_dir_ch;
	nr_empty = 0;
	nr_dir_ch = 0;
	idx = 0;
	map = m->cmap;
	if (x == 0 || y == 0 || x == m->height - 1
		|| y == ((int)ft_strlen(map[x]) - 1))
		return (map[x][y] != m->dir_ch);
	while (idx < 4)
	{
		tmp = get_box(map, x, y, idx);
		if (ft_isspace(tmp))
		{
			if (map[x][y] == m->dir_ch)
				return (0);
			return (1);
		}
		idx ++;
	}
	return (0);
}

int	check_all_map(struct s_map *m, char **map)
{
	int	x;
	int	y;
	int	len;

	x = 0;
	while (x < m->height)
	{
		y = 0;
		len = ft_strlen(map[x]);
		while (y < len)
		{
			if (ft_isspace(map[x][y]))
			{
				if (is_empty_space(m, x, y))
					return (1);
			}
			else if (is_surround_empty(m, map, x, y))
				return (1);
			y ++;
		}
		x += 1;
	}
	return (0);
}
