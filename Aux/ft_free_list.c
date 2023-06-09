/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 19:57:30 by duarte33          #+#    #+#             */
/*   Updated: 2023/06/06 22:03:07 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Esta funcao liberta a memorai da linked list gerada
para guardar os comandos a executar */
void	ft_free_list(t_list **lst)
{
	t_list	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		close((*lst)->fd[0]);
		close((*lst)->fd[1]);
		ft_free_matrix(&(*lst)->content);
		free((*lst)->path);
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	g_data.vars->head = NULL;
}

/* Esta funcao serve para dar print da linked list
gerada para guardar o varios inputs do utilizador apos
o parser */
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
		list = list->next;
	}
}
