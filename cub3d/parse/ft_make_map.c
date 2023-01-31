/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:01:33 by joowpark          #+#    #+#             */
/*   Updated: 2023/02/01 04:28:45 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse.h"

static void	char_to_int(int *dst, char *src, char sp)
{
	while (*src)
	{
		if (*src == sp)
			*dst = 1;
		else if (ft_isdigit(*src))
			*dst = (int)(*src - '0');
		src ++;
		dst ++;
	}
}

int	**make_map(struct s_map *m)
{
	int		**ret;
	int		idx;

	idx = 0;
	ret = (int **)malloc(sizeof(int *) * m->height);
	if (!ret)
		return (ret);
	ft_bzero(ret, sizeof(int *) * (m->height));
	while (idx < m->height)
	{
		ret[idx] = (int *)malloc(sizeof(int) * m->width);
		if (!ret[idx])
			break ;
		ft_memset(ret[idx], -1, sizeof(int) * m->width);
		char_to_int(ret[idx], m->cmap[idx], m->dir_ch);
		idx ++;
	}
	return (ret);
}
