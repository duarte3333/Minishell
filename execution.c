#include "minishell.h"

void redirection(t_list *lst)
{
	int	i;
	int	j;

	i = 0;
	while (lst->content[i])
	{
		if (!strcmp(lst->content[i], "<<"))
		{
			lst->fd[0] = open(".temp", O_RDWR | O_TRUNC | O_CREAT, 0644);
			//delete_one in linked list
		}
		else if(!strcmp(lst->content[i], ">>"))
			lst->fd[1] = open(lst->content[i + 1], O_WRONLY | O_TRUNC | O_APPEND | O_CREAT, 0644);
		else if(!strcmp(lst->content[i], "<"))
			lst->fd[0] = open(lst->content[i + 1], O_RDWR | O_TRUNC, 0644);
		else if(!strcmp(lst->content[i], ">"))
			lst->fd[1] = open(lst->content[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);	
		if (lst->fd[1] == -1 || lst->fd[0] == -1)
		{
			perror("");
			exit(0);
		}
		i++;
	}
}

void command_execution(t_list *lst, char **env)
{
	int		pid;
	char	*path;

	path = get_cmd_path(env, lst->content);
	pid = fork();
	if (pid == 0)
	{
		printf("cmd: %s\n", lst->content[0]);
		if (lst->prev)
		{
			printf("STDIN replaced by %d\n", lst->fd[0]);
			dup2(lst->fd[0], 0);
		}
		if (lst->next)
		{
			printf("STDOUT replaced by %d\n", lst->next->fd[1]);
			dup2(lst->next->fd[1], 1);
		}
		close(lst->fd[0]);
		close(lst->fd[1]);
		if (execve(path, lst->content, env) == -1)
		{
			perror("");
			exit(1);
		}
	}
	close(lst->fd[0]);
	close(lst->fd[1]);
	free(path);
}

void execution(t_list *lst, char **env)
{
	t_list	*temp;

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
	lst = temp;
	while (lst)
	{
		command_execution(lst, env);
		lst = lst->next;
	}
	lst = temp;
	while (lst)
	{
		waitpid(-1, NULL, 0);
		lst = lst->next;
	}
}
