/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:04:54 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/26 16:06:07 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse.h"

static int	pre_check_lines(struct s_map *m, char **map)
{
	int	x;

	x = 0;
	while (x < m->height)
	{
		if (is_empty_line(map[x++]))
			return (1);
	}
	return (set_charcter_map(map, m));
}

int	check_lines(struct s_map *m)
{
	int	y;
	int	x;

	x = 0;
	if (pre_check_lines(m, m->cmap))
		return (1);
	while (x < m->height)
	{
		y = 0;
		while (m->cmap[x][y] && m->cmap[x][y] == ' ')
			y ++;
		if (y == (int)ft_strlen(m->cmap[x]))
			return (1);
		while (y < (int)ft_strlen(m->cmap[x]))
		{
			if (m->cmap[x][y] == '1' && !is_empty_space(m, x, y))
				dfs(m, (int [2]){x, y}, m->cmap);
			y ++;
		}
		x ++;
	}
	return (check_all_map(m, m->cmap));
}
