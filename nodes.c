/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:20:05 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/03 16:38:44 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nodes.h"

t_node	*char_node_new(char c)
{
	t_node	*res;

	res = malloc(sizeof(t_node));
	if (!res)
		return (NULL);
	res.type = _CHAR;
	res.value.single = c;
	return (res);
}

t_node	*pair_node_new(t_node *left, t_node *right)
{
	t_node	*res;

	res = malloc(sizeof(t_node));
	if (!res)
		return (NULL);
	res.type = _PAIR;
	res.value.pair.left = left;
	res.value.pair.right = right;
	return (res);
}
