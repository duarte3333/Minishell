#include "minishell.h"

//printf("cmd: %s\n", lst->content[0]);
//printf("STDIN replaced by %d\n", lsGLOBALt->fd[0]);
//printf("STDOUT replaced by %d\n", lst->next->fd[1]);
void	command_execution(t_list *lst, char **env)
{
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		if (lst->prev && lst->fd_master[0] < 3)
			dup2(lst->fd[0], 0);
		else if (lst->fd_master[0] > 2)
			dup2(lst->fd_master[0], 0);
		if (lst->next && lst->fd_master[1] < 3)
			dup2(lst->next->fd[1], 1);
		else if (lst->fd_master[1] > 2)
			dup2(lst->fd_master[1], 1);
		//close(lst->fd[0]);
		//close(lst->fd[1]);
		if (lst->ft_exec(env, &lst) == -1)
		{
			perror("");
			go_head(&lst);
			ft_free_list(&lst);
			exit(1);
		}
	}
	close(lst->fd[0]);
	close(lst->fd[1]);
}

void execution(t_list *lst, char **env)
{
	// go_head(&lst);
	// while (lst)
	// {
	// 	//redirection(&lst);
	// 	if (!lst->next)
	// 		break ;
	// 	lst = lst->next;
	// }
	// go_head(&lst);
	while (lst)
	{
		lst->path = get_cmd_path(env, lst->content);
		if (lst->content[0])
			command_execution(lst, env);
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	go_head(&lst);
	while (lst)
	{
		waitpid(-1, NULL, 0);
		lst = lst->next;
	}
}


// if (!lst->prev)
// 	close(lst->fd[0]); //Nao le de ninguem

// else if (!lst->next)
// 	close(lst->fd[1]); //nao escreve para ninguem