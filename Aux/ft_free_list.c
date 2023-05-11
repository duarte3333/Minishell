#include "../minishell.h"

void	ft_free_list(t_list **lst)
{
	t_list	*temp;
	int		i;

	while (*lst)
	{
		i = -1;
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
	if (!list)
		printf("empty list\n");
	while (list)
	{
		int	i;
		
		i = -1;
		printf("[p] %p", list);
		printf("\n[content]: ");
		while (list->content[++i])
			printf("{%s}, ", list->content[i]);
		printf("\n");
		printf("[fd in] %i\n", list->fd[0]);
		printf("[fd out] %i\n", list->fd[1]);
		printf("[path] %s\n", list->path);
		list = list->next;
	}
}