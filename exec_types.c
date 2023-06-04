/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:02:31 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/06/01 18:48:15 by mtiago-s         ###   ########.fr       */
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

void	__exec_default(char **env, t_list **lst)
{
	close_fds(lst, 1);
	if (execve((*lst)->path, (*lst)->content, env) == -1)
		error_handle((*lst)->content[0]);
	go_head(lst);
	ft_free_list(lst);
	exit(g_data.status);
}
