#include "minishell.h"

void redirection(t_list *lst)
{
	int i;
	int j;
	int fd_in;
	i = 0;
	while (lst->content[i])
	{
		if (strcmp(lst->content[i], "<<"))
		{
			fd_in = open(".temp", O_WRONLY | O_CREAT, 0644);
			if (fd_in == -1)
			{
				perror("");
				exit(0);
			}
		}
		else if(strcmp(lst->content[i], "<<"))
			;
		else if(strcmp(lst->content[i], "<"))
			;
		else if(strcmp(lst->content[i], ">"))
			;
		else
		{
			if (lst->prev)
				dup2(lst->prev->fd[0], 0);	
		}
	}
}

void execution(t_list *lst)
{
	if (!lst->prev)
		close(lst->fd[0]); //Nao le de ninguem
	else if (!lst->next)
		close(lst->fd[1]); //nao escreve para ninguem
	while (lst)
	{
		redirection(lst);
		lst = lst->next;
	}
}