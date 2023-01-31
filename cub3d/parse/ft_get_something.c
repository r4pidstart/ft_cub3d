/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_something.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joowpark <joowpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:36:20 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/31 14:59:58 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse.h"

int	ft_get_info(char *line)
{
	if (!line)
		return (-1);
	if (!ft_strncmp(line, "NO", 3))
		return (NO);
	else if (!ft_strncmp(line, "SO", 3))
		return (SO);
	else if (!ft_strncmp(line, "WE", 3))
		return (WE);
	else if (!ft_strncmp(line, "EA", 3))
		return (EA);
	else if (!ft_strncmp(line, "F", 2))
		return (F);
	else if (!ft_strncmp(line, "C", 2))
		return (C);
	return (-1);
}

int	is_empty_line(char *line)
{
	char	*str;

	str = line;
	while (ft_isspace(*str) || *str == '\n')
		str++;
	if (ft_strlen(str) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

int	get_weight(char **tokens)
{
	int		ret;
	char	**line;
	int		len;

	if (!tokens || !*tokens)
		return (-1);
	ret = 0;
	line = tokens;
	while (*line)
	{
		len = ft_strlen(*line);
		if (ret < len)
			ret = len;
		line ++;
	}
	return (ret);
}

static void	set_dir_ch(struct s_map *map, char *line, char **t, char **l)
{
	map->dir_ch = *line;
	*line = '0';
	map->player_x = (double)(line - *l) + 0.5;
	map->player_y = (double)(l - t) + 0.5;
}

int	set_charcter_map(char **tokens, struct s_map *map)
{
	char	**lines;
	char	*line;

	lines = tokens;
	while (*lines)
	{
		line = *lines;
		while (*line)
		{
			if (ft_strchr("WESN", *line))
			{
				if (!map->dir_ch)
					set_dir_ch(map, line, tokens, lines);
				else
					return (1);
			}
			else if (!ft_isdigit(*line) && !ft_isspace(*line))
				return (1);
			line += 1;
		}
		lines += 1;
	}
	if (!map->dir_ch)
		return (1);
	return (0);
}
