#include "minishell.h"

void redirection(t_list *lst)
{
	int i;
	int j;
	i = 0;
	while (lst->content[i])
	{
		if (strcmp(lst->content[i], "<<"))
		{
			lst->fd[0] = open(".temp", O_RDWR | O_TRUNC | O_CREAT, 0644);
			//delete_one in linked list
		}
		else if(strcmp(lst->content[i], ">>"))
			lst->fd[1] = open(lst->content[i + 1], O_WRONLY | O_TRUNC | O_APPEND | O_CREAT, 0644);
		else if(strcmp(lst->content[i], "<"))
			lst->fd[0] = open(lst->content[i + 1], O_RDWR | O_TRUNC, 0644);
		else if(strcmp(lst->content[i], ">"))
			lst->fd[1] = open(lst->content[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);	
		if (lst->fd[1] == -1 || lst->fd[0] == -1)
		{
			perror("");
			exit(0);
		}
	}
}

void command_execution(t_list *lst, char *env)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		if (lst->prev)
			dup2(lst->fd[0], 0);
		if (lst->next)
			dup2(lst->next->fd[1], 1);
		close(lst->fd[0]);
		close(lst->fd[1]);
		// if (execve(//falta path, lst->content, env) == -1)
		// {
		// 	exit(1);
		// }
	}
}

void execution(t_list *lst)
{
	t_list *temp;
	if (!lst->prev)
		close(lst->fd[0]); //Nao le de ninguem
	else if (!lst->next)
		close(lst->fd[1]); //nao escreve para ninguem
	temp = lst;
	while (lst)
	{
		redirection(lst);
		lst = lst->next;
	}
	while (temp)
	{
		command_execution(temp, 0);
		temp = temp->next;
	}
}