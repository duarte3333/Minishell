#include "minishell.h"

int __exec_default(char **env, t_list **lst)
{
	close((*lst)->fd[0]);
	close((*lst)->fd[1]);
	return (execve((*lst)->path, (*lst)->content, env));
}

int __exec_here_doc(char **env, t_list **lst)
{	
	//(*lst)->fd[0] = ft_here_doc(*lst, 0);
	//printf("[path] %s\n", (*lst)->prev->path);
	//get_cmd_path(env, )
	//printf("[content] %s\n", (*lst)->content[2]);
	return (execve((*lst)->prev->path, (*lst)->prev->content, env));
}

int __exec_in(char **env, t_list **lst)
{	
	printf("[fd] %i\n", (*lst)->fd[0]);
	dup2((*lst)->fd[0], 0);
	((*lst)->content)++;
	((*lst)->content)++;
	printf("[content] %s\n", (*lst)->content[0]);
	(*lst)->path = get_cmd_path(env, (*lst)->content);
	printf("[path] %s\n", (*lst)->path);
	close((*lst)->fd[0]);
	close((*lst)->fd[1]);
	return (execve((*lst)->path, (*lst)->content, env));
}

