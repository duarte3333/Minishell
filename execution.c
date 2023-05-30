/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:09:50 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/05/29 19:41:38 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//printf("cmd: %s\n", lst->content[0]);
//printf("STDIN replaced by %d\n", lsGLOBALt->fd[0]);
//printf("STDOUT replaced by %d\n", lst->next->fd[1]);
//Esta funcao calcula o tamanho de uma linked list
int	ft_lstsize(t_list *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	is_built_in(t_list *lst)
{
	if (!ft_strcmp(lst->content[0], "pwd")   || \
		!ft_strcmp(lst->content[0], "cd")    || \
		!ft_strcmp(lst->content[0], "exit")  || \
		!ft_strcmp(lst->content[0], "env")   || \
		!ft_strcmp(lst->content[0], "export")   || \
		!ft_strcmp(lst->content[0], "unset"))
		return (1);
	else
		return (0);
}

/* Esta funcao vai definir a funcao de execucao para cada node */
void	define_exec(t_list *lst)
{
	if (!ft_strcmp(lst->content[0], "pwd"))
		lst->ft_exec = __exec_pwd;
	else if (!ft_strcmp(lst->content[0], "cd"))
		lst->ft_exec = __exec_cd;
	else if (!ft_strcmp(lst->content[0], "echo"))
		lst->ft_exec = __exec_echo;
	else if (!ft_strcmp(lst->content[0], "env"))
		lst->ft_exec = __exec_env;
	else if (!ft_strcmp(lst->content[0], "exit"))
		lst->ft_exec = __exec_exit;
	else if (!ft_strcmp(lst->content[0], "export"))
		lst->ft_exec = __exec_export;
	else if (!ft_strcmp(lst->content[0], "unset"))
		lst->ft_exec = __exec_unset;
	else
		lst->ft_exec = __exec_default;
}

void	command_execution(t_list *lst, char **env)
{
	if (is_built_in(lst) && (ft_lstsize(lst) == 1))
	{
		lst->ft_exec(env, &lst);
		return ;
	}
	if (fork() == 0)
	{
		if (lst->prev && lst->fd_master[0] < 3)
			dup2(lst->fd[0], 0);
		else if (lst->fd_master[0] > 2)
			dup2(lst->fd_master[0], 0);
		if (lst->next && lst->fd_master[1] < 3)
			dup2(lst->next->fd[1], 1);
		else if (lst->fd_master[1] > 2)
			dup2(lst->fd_master[1], 1);
		lst->ft_exec(env, &lst);
		ft_free_list(&lst);
		ft_free_env(&g_data.env);
		exit(0);
	}
	close_fds(&lst, 0);

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
		{
			waitpid(-1, &g_data.status, 0);
			if (WIFEXITED(g_data.status))
				g_data.status = WEXITSTATUS(g_data.status);
		}

		lst = lst->next;
	}
}
