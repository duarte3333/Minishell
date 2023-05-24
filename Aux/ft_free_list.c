#include "../minishell.h"

void	ft_free_list(t_list **lst)
{
	t_list	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		ft_free_matrix(&(*lst)->content);
		free((*lst)->path);
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
}

void	print_list(t_list *list)
{
	int	i;

	if (!list)
		return ;
	while (list)
	{
		i = -1;
		printf("[p] %p", list);
		printf("\n[content]: ");
		while (list->content[++i])
			printf("{%s}, ", list->content[i]);
		printf("\n");
		printf("[fd in] %i\n", list->fd[0]);
		printf("[fd out] %i\n", list->fd[1]);
		printf("[fd OW in] %i\n", list->fd_master[0]);
		printf("[fd OW out] %i\n", list->fd_master[1]);
		//printf("[path] %s\n", list->path);
		list = list->next;
	}
}