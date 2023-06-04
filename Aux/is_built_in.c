/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 22:04:14 by duarte33          #+#    #+#             */
/*   Updated: 2023/06/04 22:04:36 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_built_in(t_list *lst)
{
	if (!ft_strcmp(lst->content[0], "pwd") || \
		!ft_strcmp(lst->content[0], "cd") || \
		!ft_strcmp(lst->content[0], "exit") || \
		!ft_strcmp(lst->content[0], "env") || \
		!ft_strcmp(lst->content[0], "export") || \
		!ft_strcmp(lst->content[0], "unset"))
		return (1);
	else
		return (0);
}