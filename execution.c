/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:09:50 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/05/23 16:31:21 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//printf("cmd: %s\n", lst->content[0]);
//printf("STDIN replaced by %d\n", lsGLOBALt->fd[0]);
//printf("STDOUT replaced by %d\n", lst->next->fd[1]);

/* Esta funcao vai definir a funcao de execucao para cada node */
void	define_exec(t_list *lst)
{
	if (!ft_strcmp(lst->content[0], "pwd"))
		lst->ft_exec = __exec_pwd;
	else if (!ft_strcmp(lst->content[0], "cd"))
		lst->ft_exec = __exec_cd;
	else
		lst->ft_exec = __exec_default;
}

void	command_execution(t_list *lst, char **env)
{
	lst->ft_exec(env, &lst);
	close(lst->fd[0]);
	close(lst->fd[1]);
	if (lst->fd_master[1] > 2)
		close(lst->fd_master[1]);
	if (lst->fd_master[0] > 2)
		close(lst->fd_master[0]);
}

void	execution(t_list *lst, char **env)
{
	while (lst)
	{	
		if (lst->content[0])
		{
			lst->path = get_cmd_path(env, lst->content);
			define_exec(lst);
			command_execution(lst, env);
		}
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	go_head(&lst);
	while (lst)
	{
		if (lst->content[0])
			waitpid(-1, NULL, 0);
		lst = lst->next;
	}
}
