/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:09:50 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/06/04 23:22:59 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		exit(g_data.status);
	}
	close_fds(&lst, 0);
}

int	check_fds(t_list *lst)
{
	int	res;

	res = 0;
	while (lst)
	{
		if (lst->fd_master[0] == -1 || lst->fd_master[1] == -1 \
			|| lst->master_error[0] || lst->master_error[1])
			res++;
		lst = lst->next;
	}
	return (res);
}

void	core_execution(t_list *lst, char **env)
{
	while (lst)
	{	
		if (lst->content[0] && !lst->master_error[0] && !lst->master_error[1])
		{
			lst->path = get_cmd_path(env, lst->content);
			define_exec(lst);
			command_execution(lst, env);
		}
		if (!lst->next)
			break ;
		lst = lst->next;
	}
}

void	execution(t_list *lst, char **env)
{
	int	status;

	core_execution(lst, env);
	go_head(&lst);
	while (lst)
	{
		if (lst->content[0])
		{
			waitpid(-1, &status, 0);
			if (WIFEXITED(status))
				g_data.status = WEXITSTATUS(status);
		}
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	if (check_fds(lst))
		g_data.status = 1;
}

//printf("cmd: %s\n", lst->content[0]);
//printf("STDIN replaced by %d\n", lsGLOBALt->fd[0]);
//printf("STDOUT replaced by %d\n", lst->next->fd[1]);