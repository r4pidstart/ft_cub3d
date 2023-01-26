/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joowpark <joowpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:52:48 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/25 14:58:22 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse.h"

void	free_node(struct s_node *root)
{
	struct s_node	*prv;
	struct s_node	*now;

	now = root;
	while (now)
	{
		prv = now;
		now = now->nxt;
		if (prv->line)
			free(prv->line);
		free(prv);
	}
}

void	free_lines(char **lines)
{
	char	**line;

	line = lines;
	while (*line)
	{
		free(*line);
		line += 1;
	}
	free(lines);
}

void	free_info(struct s_map *m)
{
	int	idx;

	idx = 0;
	while (idx < NR_INFO)
	{
		if (m->info[idx])
			free(m->info[idx]);
		idx ++;
	}
}

void	free_imap(struct s_map *m)
{
	int		idx;

	if (!m->map)
		return ;
	idx = 0;
	while (idx < m->height)
	{
		if (m->map[idx])
			free(m->map[idx]);
		idx ++;
	}
	if (m->map)
		free(m->map);
}

void	free_all_map(struct s_map *m)
{
	free_info(m);
	free_imap(m);
}
