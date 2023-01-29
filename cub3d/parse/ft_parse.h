/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:25:04 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/30 05:48:27 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSE_H
# define FT_PARSE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../ft_mylibft/libft.h"
# include "../raycasting/ft_raycasting_header.h"

enum e_error{
	NUN,
	ERROR_FD,
	ERROR_CUB,
};

struct s_node
{
	char			*line;
	struct s_node	*nxt;
	size_t			size;
};

int		is_empty_space(struct s_map *m, int x, int y);
void	dfs(struct s_map *m, int prv[2], char **map);
int		check_all_map(struct s_map *m, char **map);
int		**make_map(struct s_map *m);
int		check_lines(struct s_map *m);
int		append_node(struct s_node **root, char *line);
char	**node_to_str(struct s_node *root);
void	free_node(struct s_node *root);
int		is_empty_line(char *str);
int		set_charcter_map(char **tokens, struct s_map *map);
int		get_weight(char **tokens);
int		ft_strrip(char *__line);
int		ft_atoi_strict(char *line, int *error);
int		get_info(int fd, struct s_map *m);
int		get_imap(int fd, struct s_map *map);
int		ft_get_info(char *line);
int		set_map(struct s_map *m);
int		get_fd(char *file_name);

void	free_lines(char **lines);
void	free_info(struct s_map *m);
void	free_imap(struct s_map *m);
void	free_all_map(struct s_map *m);

int		init_map(struct s_map *map, char *file_name);
void	map_error_handling(struct s_map *m, int error);
#endif
