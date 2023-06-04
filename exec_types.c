/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:02:31 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/06/04 22:00:25 by duarte33         ###   ########.fr       */
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
void	__exec_default(char **env, t_list **lst)
{
	close_fds(lst, 1);
	if (execve((*lst)->path, (*lst)->content, env) == -1)
		error_handle((*lst)->content[0]);
	go_head(lst);
	ft_free_list(lst);
	exit(g_data.status);
}
