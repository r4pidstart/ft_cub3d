/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:17:47 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/26 16:00:52 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse.h"

static struct s_node	*malloc_node(char *line)
{
	struct s_node	*node;

	node = (struct s_node *)malloc(sizeof(*node));
	if (!node)
		return (node);
	node->line = ft_strdup(line);
	node->size = 1;
	node->nxt = NULL;
	return (node);
}

int	append_node(struct s_node **root, char *line)
{
	struct s_node	*node;
	struct s_node	*tmp;

	if (!line)
		return (1);
	tmp = *root;
	node = malloc_node(line);
	if (!node)
		return (1);
	if (!tmp)
	{
		*root = node;
		return (0);
	}
	while (tmp->nxt)
		tmp = tmp->nxt;
	tmp->nxt = node;
	(*root)->size += 1;
	return (0);
}

char	**node_to_str(struct s_node *root)
{
	char			**ret;
	struct s_node	*node;
	int				idx;

	idx = 0;
	node = root;
	ret = (char **)malloc(sizeof(*ret) * (root->size + 1));
	if (!ret)
		return (ret);
	while (node)
	{
		ret[idx] = ft_strdup(node->line);
		if (!ret[idx++])
		{
			free_lines(ret);
			return (NULL);
		}
		node = node->nxt;
	}
	ret[idx] = NULL;
	free_node(root);
	return (ret);
}
