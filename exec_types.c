#include "minishell.h"

int __exec_default(char **env, t_list **lst)
{
	close((*lst)->fd[0]);
	close((*lst)->fd[1]);
	if ((*lst)->fd_master[1] > 2)
		close((*lst)->fd_master[1]);
	if ((*lst)->fd_master[0] > 2)
		close((*lst)->fd_master[0]);
	return (execve((*lst)->path, (*lst)->content, env));
}

int __exec_out(char **env, t_list **lst)
{
	close((*lst)->fd[0]);
	close((*lst)->fd[1]);
	exit(0);
}

// int __exec_here_doc(char **env, t_list **lst)
// {	
// 	//(*lst)->fd[0] = ft_here_doc(*lst, 0);
// 	if (!(*lst)->content[2])
// 	{
// 		close((*lst)->fd[0]);
// 		close((*lst)->fd[1]);
// 		exit(0);
// 	} // << oi cat ----v ||| cat << oi -----^
// 	close((*lst)->fd[0]);
// 	close((*lst)->fd[1]);
// 	free((*lst)->path);
// 	//(*lst)->fd[0] = ft_here_doc(*lst, 0);
// 	//printf("[path] %s\n", (*lst)->prev->path);
// 	//get_cmd_path(env, )
// 	//printf("[content] %s\n", (*lst)->content[2]);
// 	(*lst)->path = get_cmd_path(env, &(*lst)->content[2]);
// 	printf("%s\n", (*lst)->path);
// 	return (execve((*lst)->path, &(*lst)->content[2], env));
// }

// int __exec_in(char **env, t_list **lst)
// {	
// 	//printf("[fd] %i\n", (*lst)->fd[0]);
// 	if (!(*lst)->content[2])
// 		exit(0);
// 	dup2((*lst)->fd[0], 0);
// 	//printf(">>>>[content] %s\n", (*lst)->content[2]);
// 	(*lst)->path = get_cmd_path(env, &(*lst)->content[2]);
// 	//printf("[path] %s\n", (*lst)->path);
// 	close((*lst)->fd[0]);
// 	close((*lst)->fd[1]);
// 	return (execve((*lst)->path, &(*lst)->content[2], env));
// }
