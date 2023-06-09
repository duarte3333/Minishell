/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:02:31 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/06/06 22:08:57 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_list **lst, int flag)
{
	t_list	*temp;

	temp = (*lst);
	if (flag)
		go_head(lst);
	while ((*lst))
	{
		close((*lst)->fd[0]);
		close((*lst)->fd[1]);
		if ((*lst)->fd_master[1] > 2)
			close((*lst)->fd_master[1]);
		if ((*lst)->fd_master[0] > 2)
			close((*lst)->fd_master[0]);
		if (!flag)
			break ;
		(*lst) = (*lst)->next;
	}
	(*lst) = temp;
}

/* Funcao de execucao default, caso nao seja um built in */
void	__exec_default(t_list **lst)
{
	char	**our_env;

	our_env = ft_env_lst_to_arr(g_data.env);
	close_fds(lst, 1);
	if (execve((*lst)->path, (*lst)->content, our_env) == -1)
		error_handle((*lst)->content[0]);
	close(0);
	close(1);
	go_head(lst);
	ft_free_matrix(&our_env);
	ft_free_env(&g_data.env);
	free_vars();
	exit(g_data.status);
}
