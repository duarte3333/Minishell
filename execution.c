#include "minishell.h"

void	define_exec(t_list **lst, char **env)
{
	int option;

	option = check_token((*lst)->content);
	if (option == 1)
		(*lst)->ft_exec = __exec_here_doc;
	else if (option == 2 || option == 4)
		(*lst)->ft_exec = __exec_out;
	else if(option == 3)
		(*lst)->ft_exec = __exec_in;
	else
		(*lst)->ft_exec = __exec_default;
}

//printf("cmd: %s\n", lst->content[0]);
//printf("STDIN replaced by %d\n", lst->fd[0]);
//printf("STDOUT replaced by %d\n", lst->next->fd[1]);
void	command_execution(t_list *lst, char **env)
{
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		if (lst->prev)
			dup2(lst->fd[0], 0);
		if (lst->next)
			dup2(lst->next->fd[1], 1);
		//close(lst->fd[0]);
		//close(lst->fd[1]);
		if (lst->ft_exec(env, &lst) == -1)
		{
			perror("");
			exit(1);
		}
	}
	close(lst->fd[0]);
	close(lst->fd[1]);
}

void execution(t_list *lst, char **env)
{
	go_head(&lst);
	while (lst)
	{
		if (redirection(&lst))
			prompt(env);
		if (!lst->next)
			break;
		lst = lst->next;
	}
	go_head(&lst);
	while (lst)
	{
		define_exec(&lst, env);
		command_execution(lst, env);
		if (!lst->next)
			break;
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