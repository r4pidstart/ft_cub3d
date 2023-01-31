/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 03:22:07 by tjo               #+#    #+#             */
/*   Updated: 2023/01/31 14:56:39 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_min(long a, long b)
{
	if (a < b)
		return (a);
	return (b);
}

long	ft_max(long a, long b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}
