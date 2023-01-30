/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:24:46 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/31 04:11:33 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse.h"

static int	get_info_line(char **info, char *line)
{
	char		**tokens;
	int			idx;
	int			ret;

	ret = 0;
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (1);
	idx = ft_get_info(tokens[0]);
	if (idx == -1 || info[idx] || tokens[2] != NULL)
		return (1);
	if (tokens[2] == NULL)
	{
		ft_strrip(tokens[1]);
		info[idx] = ft_strdup(tokens[1]);
	}
	else
		ret = 1;
	free_lines(tokens);
	return (ret);
}

int	get_info(int fd, struct s_map *m)
{
	char	*line;
	int		idx;
	char	**info;

	(void)info;
	info = m->info;
	idx = 0;
	while (idx < NR_INFO)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_empty_line(line))
			continue ;
		if (get_info_line(m->info, line))
			return (1);
		free(line);
		line = NULL;
		idx += 1;
	}
	if (idx != NR_INFO)
		return (1);
	if (!line)
		free(line);
	return (0);
}

int	get_fd(char *file_name)
{
	int		fd;
	char	*base_name;

	base_name = ft_strnstr(file_name, ".cub", ft_strlen(file_name));
	if (!base_name)
		return (-1);
	if (ft_strncmp(base_name, ".cub", 5))
		return (-1);
	fd = open(file_name, O_RDONLY, 644);
	return (fd);
}

static int	__get_imap(struct s_map *m)
{
	int	x;
	int	y;

	(void)x, (void)y;
	x = 0;
	y = 0;
	if (check_lines(m))
		return (1);
	m->width = get_weight(m->cmap);
	m->map = make_map(m);
	if (!m->map)
		return (1);
	return (0);
}

int	get_imap(int fd, struct s_map *map)
{
	char			*line;
	struct s_node	*root;

	root = NULL;
	line = get_next_line(fd);
	while (line && is_empty_line(line))
		line = get_next_line(fd);
	if (!line)
		return (1);
	while (line)
	{
		if (ft_strrip(line) || append_node(&root, line))
		{
			free_node(root);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	map->height = (int)root->size;
	map->cmap = node_to_str(root);
	return (__get_imap(map));
}
