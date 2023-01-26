/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:37:25 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/26 16:12:11 by tjo              ###   ########.fr       */
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
	return (error);
}
