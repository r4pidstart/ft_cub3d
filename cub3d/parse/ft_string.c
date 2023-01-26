/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:59:26 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/26 16:51:31 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse.h"

int	ft_strrip(char *__line)
{
	char	*line;
	int		len;

	line = __line;
	if (!line)
		return (1);
	len = ft_strlen(line);
	if (!len)
		return (0);
	line += len - 1;
	while (line != __line)
	{
		if (ft_isspace(*line) || *line == '\n')
		{
			*line = '\0';
			line --;
		}
		else
			break ;
	}
	return (0);
}

int	ft_atoi_strict(char *line, int *error)
{
	char	*tmp;
	int		ret;

	*error = 0;
	if (!line)
	{
		*error = 1;
		return (0);
	}
	ret = 0;
	tmp = line;
	while (ft_isspace(*tmp))
		tmp ++;
	while (ft_isdigit(*tmp))
	{
		ret = ret * 10 + (*tmp - '0');
		tmp += 1;
	}
	if (*tmp != 0)
		*error = 1;
	*error |= !(0 <= ret && ret < 256);
	return (ret);
}

char	*ft_strndup(char *str, int width)
{
	char	*ret;
	char	*line;

	ret = (char *)malloc(sizeof(*ret) * (width + 1));
	if (!ret)
		return (NULL);
	line = ret;
	ft_memset(line, ' ', width);
	ft_memmove(line, str, ft_strlen(str));
	line[width] = '\0';
	return (ret);
}
