/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:05:35 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/03 16:42:48 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODES_H
# define NODES_H

# include "lexer.h"

typedef struct t_node	t_node;

typedef enum s_node_type
{
	_ERROR = -1;
	_CHAR = 0;
	_PAIR = 1;
}			t_node_type;

typedef struct s_pair_value
{
	struct s_node	*left;
	struct s_node	*right;
}			t_pair_value;

typedef union s_node_value
{
	struct s_pair_value	pair;
	char				single;
}	t_node_value;

typedef struct s_node
{
	enum s_node_type	type;
	union s_node_value	value;	
}	t_node;

t_node	*char_node_new(char c);
t_node	*pair_node_new(t_node *left, t_node *right);

#endif