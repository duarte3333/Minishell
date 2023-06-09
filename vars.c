/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:59:21 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/06/06 21:25:53 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_vars(void)
{
	if (g_data.vars)
	{
		if (g_data.vars->head)
		{
			go_head(&g_data.vars->head);
			ft_free_list(&g_data.vars->head);
		}
		if (g_data.vars->str)
			free(g_data.vars->str);
		if (g_data.vars->env)
			ft_free_matrix(&g_data.vars->env);
		if (g_data.vars->division)
			ft_free_matrix(&g_data.vars->division);
		free(g_data.vars);
	}
	return (1);
}

t_vars	*init_vars(void)
{
	t_vars	*vars;

	vars = ft_calloc(1, sizeof(t_vars));
	vars->head = NULL;
	vars->str = NULL;
	vars->env = NULL;
	vars->division = NULL;
	return (vars);
}
