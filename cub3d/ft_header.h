/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:29:32 by tjo               #+#    #+#             */
/*   Updated: 2023/01/31 17:16:36 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEADER_H
# define FT_HEADER_H

# include"raycasting/ft_raycasting_header.h"
# include"parse/ft_parse.h"

/* ft_keyhook.c */
int	check_collision(t_map *m, double next_x, double next_y);
int	move_player(int key, t_param *t);
int	close_game(t_param *t);
int	key_hook(int key, t_param *t);

#endif
