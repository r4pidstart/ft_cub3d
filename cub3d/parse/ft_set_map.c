/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joowpark <joowpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:37:33 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/25 13:38:17 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse.h"

int	set_color(char *cmd)
{
	char	**tokens;
	int		ret;
	int		idx;
	int		error;

	idx = 0;
	ret = 0;
	tokens = ft_split(cmd, ',');
	if (!tokens || !tokens[0] || !tokens[1] || !tokens[2] || tokens[3])
		return (-1);
	while (idx < 3)
	{
		ret = (ret << 8) | (ft_atoi_strict(tokens[idx], &error));
		if (error)
			break ;
		idx ++;
	}
	free_lines(tokens);
	if (error)
		return (-1);
	return (ret);
}

int	set_map(struct s_map *m)
{
	m->floor = set_color(m->info[F]);
	m->ceiling = set_color(m->info[C]);
	if (m->floor == -1 || m->ceiling == -1)
		return (1);
	return (0);
}
